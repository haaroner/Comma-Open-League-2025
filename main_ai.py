# Edge Impulse - OpenMV FOMO Object Detection with Filtering, Merging & UART
import csi
import time, image
import ml
from ml.postprocessing.edgeimpulse import Fomo
import math
from machine import UART

# --- НАСТРОЙКИ ФИЛЬТРАЦИИ И УПРАВЛЕНИЯ ---
CONFIDENCE_THRESHOLD = 0.05  # 1) Минимальный порог уверенности (отсечка)
MIN_BALL_SIZE = 4            # 2) Минимальный размер мяча (ширина/высота в пикселях)
MAX_BALL_SIZE = 120          # 2) Максимальный размер мяча (чтобы отсечь ложные срабатывания вблизи)

# 3) Параметры слияния объектов (аналог merge и margin в find_blobs)
ENABLE_MERGE = True
MERGE_MARGIN = 15            # Дополнительные пиксели вокруг объекта для объединения соседей

# Настройка UART (выберите нужный порт, например, UART(3) или UART(1), скорость 115200)
uart = UART(5, 115200)

MODEL_FROM_ROMFS = True

csi0 = csi.CSI()
csi0.reset()
#csi0.transpose(True)

csi0.pixformat(csi.RGB565)
csi0.framesize(csi.QVGA)  # 320x240
#csi0.window((240,240))
csi0.auto_exposure(False, exposure_us=8000)

#csi0.vflip(True)
#csi0.transpose(True)
csi0.snapshot(time=2000)
csi0.auto_whitebal(False, rgb_gain_db=(5.0, 0, 5.0))

if MODEL_FROM_ROMFS:
    # Базовый threshold модели ставим ниже, а жесткую фильтрацию делаем в коде выше (CONFIDENCE_THRESHOLD)
    model = ml.Model("/rom/ei-model-2.tflite", postprocess=Fomo(threshold=0.3))
    labels = model.labels
else:
    model = ml.Model('ei-model-2.tflite', load_to_fb=True, postprocess=Fomo(threshold=0.3))
    labels = [line.rstrip('\n') for line in open("ei-model.txt")]

colors = [
    (255, 0, 0),
    (0, 255, 0),
    (255, 255, 0),
    (0, 0, 255),
    (255, 0, 255),
    (0, 255, 255),
    (255, 255, 255),
]

def boxes_overlap(b1, b2, margin):
    """Проверка пересечения двух боксов с учетом отступа (margin)"""
    x1, y1, w1, h1 = b1
    x2, y2, w2, h2 = b2
    return not (x1 - margin > x2 + w2 + margin or
                x1 + w1 + margin < x2 - margin or
                y1 - margin > y2 + h2 + margin or
                y1 + h1 + margin < y2 - margin)

def merge_detections(detections, margin):
    """Слияние близлежащих объектов (аналог merge=True в find_blobs)"""
    if not detections:
        return []

    # Сортируем по уверенности
    dets = sorted(detections, key=lambda d: d[1], reverse=True)
    merged = []

    while dets:
        current_box, current_score = dets.pop(0)
        cx, cy, cw, ch = current_box

        i = 0
        while i < len(dets):
            other_box, other_score = dets[i]
            if boxes_overlap((cx, cy, cw, ch), other_box, margin):
                # Объединяем боксы (находим минимальный охватывающий прямоугольник)
                ox, oy, ow, oh = other_box
                nx = min(cx, ox)
                ny = min(cy, oy)
                nw = max(cx + cw, ox + ow) - nx
                nh = max(cy + ch, oy + oh) - ny

                cx, cy, cw, ch = nx, ny, nw, nh
                # Уверенность берем максимальную из объединяемых
                current_score = max(current_score, other_score)
                dets.pop(i)
            else:
                i += 1

        merged.append(((cx, cy, cw, ch), current_score))
    return merged

clock = time.clock()
while True:
    clock.tick()
    img = csi0.snapshot()
    img.scale(hint = image.ROTATE_90)
    img.draw_rectangle((0, 0, img.width(), 60), color = (0, 0, 0), fill = True)
    #img.replace(image = img, transpose = True, vflip = True)
    #img = img.copy(hint = img.ROTATE_90, copy_to_fb = True)
    all_valid_detections = []

    for i, detection_list in enumerate(model.predict([img])):
        if i == 0:
            continue  # фоновый класс
        if len(detection_list) == 0:
            continue

        for (x, y, w, h), score in detection_list:
            # 1) Фильтрация по степени уверенности
            if score < CONFIDENCE_THRESHOLD:
                continue

            # 2) Фильтрация по размеру мяча на изображении
            if w < MIN_BALL_SIZE or h < MIN_BALL_SIZE or w > MAX_BALL_SIZE or h > MAX_BALL_SIZE:
                continue

            all_valid_detections.append(((x, y, w, h), score, i))

    # 3) Слияние близких объектов, если включено
    if ENABLE_MERGE and len(all_valid_detections) > 1:
        # Группируем по классам (на случай если классов несколько)
        class_groups = {}
        for box, score, cls_id in all_valid_detections:
            class_groups.setdefault(cls_id, []).append((box, score))

        all_valid_detections = []
        for cls_id, dets in class_groups.items():
            merged = merge_detections(dets, MERGE_MARGIN)
            for box, score in merged:
                all_valid_detections.append((box, score, cls_id))

    # 1) Сортировка всех найденных объектов по степени уверенности (от наивысшей к низкой)
    all_valid_detections = sorted(all_valid_detections, key=lambda x: x[1], reverse=True)

    best_target = None

    if len(all_valid_detections) > 0:
        # Берем объект с самой высокой уверенностью (первый после сортировки)
        best_box, best_score, best_cls = all_valid_detections[0]
        x, y, w, h = best_box
        center_x = math.floor(x + (w / 2))
        center_y = math.floor(y + (h / 2))

        best_target = (center_x, center_y, best_score)

        # Отрисовка лучшего объекта
        img.draw_circle((center_x, center_y, max(6, int(w/2))), color=colors[best_cls], thickness=2)
        #img.draw_string(x, max(0, y - 10], f"Scr:{best_score:.2f}", color=colors[best_cls])

        # Отрисовка остальных отфильтрованных объектов менее заметно
        for box, score, cls_id in all_valid_detections[1:]:
            bx, by, bw, bh = box
            bcx = math.floor(bx + (bw / 2))
            bcy = math.floor(by + (bh / 2))
            img.draw_circle((bcx, bcy, 6), color=(100, 100, 100))

    # 4) Отправка координат объекта с самой высокой уверенностью по UART
    #uart.write(bytes([255]))
    if best_target:
        cx, cy, score = best_target
        # Диапазон X (0-320) делим на 2, получаем 0-160 — помещается в 1 байт
        x_byte = int(cx // 2)
        uart.write(bytes([x_byte]))
    else:
        # Отправляем маркер отсутствия мяча (например, 255, так как валидные значения 0-160)
        uart.write(bytes([255]))

    print(clock.fps(), "fps")
