import sensor, utime, image, time, pyb, math #import librares

EXPOSURE_TIME_SCALE = 0.9


callibrate_center = False

blue_x_test = 0
blue_y_test = 0

center1 = [164, 119]#[81, 59]#[163, 116]
center2 = [165, 117]#[83,58]#[160, 120]

robot = 1
if robot == 1 or robot == 3:#attacker

    yellow_threshold = [(0, 100, -1, 127, 13, 127)]
    blue_threshold = [(0, 100, -128, 127, -128, -19)]
    red_threshold = [(0, 100, 25, 127, -128, 127)]#( 62, 100, 46, 127, -128, 40)

    white = (63, 60, 64)

    center = center1
    EXPOSURE_TIME_SCALE = 0.8
    img_radius = 140#65#140
    robot_radius = 19#9#18
    my_gain = 25
    exposure = 80_000
else:
    yellow_threshold = [(0, 100, -6, 127, 28, 127)]
    blue_threshold = [(0, 38, -128, 127, -128, -15)]
    red_threshold = [(0, 100, 44, 127, -128, 127)]

    white = (-3.5, -6, -0.3)

    center = center2
    EXPOSURE_TIME_SCALE = 0.8
    img_radius = 130#70#130
    robot_radius = 20#10#15
    my_gain = 7
    exposure = 5_000
uart = pyb.UART(3, 230400, timeout = 100, timeout_char = 100)
uart.init(230400, bits=8, parity=False, stop=1, timeout_char=100) #initialize UART



led3 = pyb.LED(2)

################################### setup camera
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(True)
sensor.set_auto_whitebal(True)
sensor.set_auto_exposure(True)
current_exposure_time_in_microseconds =  sensor.get_exposure_us()
sensor.skip_frames(time = 2000)

sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False, gain_db = my_gain)
print(sensor.get_rgb_gain_db())
sensor.set_auto_whitebal(False, rgb_gain_db = white)#(-2.5, -7, -1.47639)
sensor.set_auto_exposure(False)
current_exposure_time_in_microseconds =  sensor.get_exposure_us()
sensor.set_auto_exposure(False,exposure_us = exposure)
clock = time.clock()
print(float(current_exposure_time_in_microseconds))
sensor.skip_frames(time = 1000) #delay

image_height = sensor.height() #get image framesize
image_width = sensor.width()

yellow_x = 0
yellow_y = 0
blue_x = 0
blue_y = 0

yellow = [0]*9
blue = [0]*9
ball = [0] * 8
old_area = 0

old_i = 0

ball_roundness = 0

my_blob_x = 0
my_blob_y = 0

ball_angle = 0
ball_distance = 50
yellow_smth = 0
yellow_angle = 0
yellow_distance = 100
blue_angle = 180
blue_distance = 80

yellow_is_see = False
blue_is_see = False
            #sm   pxl
distance = [
            [210, 144],
            [140, 128],
            [130, 126],
            [120, 123],
            [110, 120],
            [100, 117],
            [90, 114],
            [80, 109],
            [75, 107],
            [70, 106],
            [65, 103],
            [60, 99],
            [55, 93],
            [50, 89],
            [45, 78],
            [40, 77],
            [35, 70],
            [30, 65],
            [25, 57],
            [20, 52],
            [15, 39],
            [10, 27],
            [5, 23]
                    ]

clock = time.clock()

a = 0

def my_line(dX1, dY1, dX2, dY2, size):
    img.draw_line(center[0] + dX1, center[1] + dY1, center[0] + dX2, center[1] + dY2, (0, 0, 0), size)

def back():
    if yellow[5] > center[1] :
       return 'y'
    else:
       return 'b'

# function that calculates distance to the gates
def get_distance(x, y):
    number = math.sqrt(math.pow(x, 2) + math.pow(y, 2))
    return number

def linearize(num):
    num = abs(num)
    old_i = 0
    i = 0
    old_err = 1000
    for mas in distance: #getting data from mass
        err = abs(num) - abs(mas[1]) #calculating error from input data and the second element of arr
        if abs(old_err) > abs(err): #finding the nearest element to the input data
            i += 1
        else:
            break
        old_err = err
        old_i = i
    result = 0
    dist1 = 0
    dist2 = 0
    if i > 1 and i < len(distance) and (num != distance[i - 1][1]):
        if abs(num) > abs(distance[i - 1][1]):
            dist1 = distance[i - 1][1] - num
            dist2 = distance[i][1] - num
            result = distance[i - 1][0] + (distance[i - 1][0] - distance[i][0]) / (dist1 + dist2) * dist1
        else:
            dist1 = num - distance[i][1]
            dist2 = 1
            result = distance[i][0] + (distance[i - 1][0] - distance[i][0]) / (dist1 + dist2) * dist1
    else:
        result = distance[i - 1][0]
    return result

def crc8(data, len): #function that calculates check sum
    crc = 0xFF
    j = 0
    for i in range(0, len):
        crc = crc ^ data[i];
        for j in range(0, 8):
            if (crc & 0x80):
                crc = (crc << 1) ^ 0x31
            else:
             crc = crc << 1
    return crc

data = bytearray(9)

def send_data(num1, num2, num3, num4, num5, num6, num7, num8):
    uart.writechar(255)
    num1 = int((num1) / 3)
    num2 = int((num2) / 3)
    num3 = int((num3) / 3)
    num4 = int((num4) / 3)
    num5 = int((num5) / 3)
    num6 = int((num6) / 3)
    num7 = int((num7) / 3)
    num8 = int((num8) / 3)

    if num1 + 127 > 253:
       data[0] = 253
    elif num1 + 127 < 0:
       data[0] = 0
    else:
       data[0] = num1

    if num2 + 127 > 253:
       data[1] = 253
    elif num2 + 127 < 0:
       data[1] = 0
    else:
       data[1] = num2

    if num3 + 127 > 253:
       data[2] = 253
    elif num3 + 127 < 0:
       data[2] = 0
    else:
       data[2] = num3

    if num4 + 127 > 253:
       data[3] = 253
    elif num4 + 127 < 0:
       data[3] = 0
    else:
       data[3] = num4

    if num5 + 127 > 253:
       data[4] = 253
    elif num5 + 127 < 0:
       data[4] = 0
    else:
       data[4] = num5

    if num6 + 127 > 253:
       data[5] = 253
    elif num6 + 127 < 0:
       data[5] = 0
    else:
       data[5] = num6

    if num7 + 127 > 253:
       data[6] = 253
    elif num7 + 127 < 0:
       data[6] = 0
    else:
       data[6] = num7

    if num8 + 127 > 253:
       data[7] = 253
    elif num8 + 127 < 0:
       data[7] = 0
    else:
       data[7] = num8
    if(yellow_piece_distance == 0):
       data[7] = 250
    if(blue_piece_distance == 0):
       data[6] = 250
#    data[0] = num1
#    data[1] = num2
#    data[2] = num3
#    data[3] = num4
#    data[4] = num5
#    data[5] = num6
    data[8] = crc8(data, 8)

    uart.writechar(int(data[0]))
    uart.writechar(int(data[1]))
    uart.writechar(int(data[2]))
    uart.writechar(int(data[3]))
    uart.writechar(int(data[4]))
    uart.writechar(int(data[5]))
    uart.writechar(int(data[6]))
    uart.writechar(int(data[7]))
    uart.writechar(int(data[8]))


def find_object(treshold, pixels_t, area_t, _merge, _margin):
   data = img.find_blobs(treshold, pixels_threshold=pixels_t, area_threshold=area_t, merge=_merge, margin = _margin)
   if(len(data) > 0):
      blob = sorted(data, key = lambda b:b.area(), reverse = True)[0]
      blob_x = -(blob.cx() - center[0])
      blob_y = -(blob.cy() - center[1])
      blob_x_test = blob.cx()
      blob_y_test = blob.cy()
      blob_distance = linearize(get_distance(blob_x*1, blob_y*1))
      blob_angle = math.floor(math.atan2(blob_x, blob_y) * 57.3)
      if(blob_angle > 360):
          blob_angle -= 360
      elif(blob_angle < 0):
          blob_angle += 360
      if(blob.area() < area_t):
          blob_distance = 0
      return [blob.cx(), blob.cy(), blob_angle, blob_distance, blob.x(), blob.y(), blob.w(),blob.h(), get_distance(blob_x, blob_y)]
   else:
      return [0,0,0,0,0,0,0,0]

while(True):
    try:
       clock.tick()
       #print(utime.ticks_ms())
       if callibrate_center == False:
           img = sensor.snapshot().mask_circle(center[0], center[1], img_radius)#.binary(green_threshold, zero=True)#.binary(black_threshold, zero=True) #get corrected image

           #img_masked = img
           if False:
               img.draw_circle(center[0], center[1], robot_radius, (0, 0, 0), fill = True)
               my_line(-26, -17, -10, -25, 9)#top lines
               my_line(-10, -25, 10, -25, 8)
               my_line(-26, -17, -27, -8, 7)

               my_line(-24, 17, -10, 25, 9)#bottom lines
               my_line(-10, 25, 10, 25, 9)
               my_line(-27, 9, -24, 17, 7)
           else:
               img.draw_circle(center[0], center[1], robot_radius, (0, 0, 0), fill = True)
               #my_line(-5, 17, 12, 17, 5)
       else:
           img = sensor.snapshot()
       old_area = 0

       yellow_is_see = False
       blue_is_see = False

       #detecting blue gate
       blue_gates = find_object(blue_threshold, 50, 450, True, 30)
       blue_angle, blue_distance = blue_gates[2], blue_gates[3]
       blue_piece = find_object(blue_threshold, 20, 50, False, 0)
       blue_piece_angle, blue_piece_distance = blue_piece[2], blue_piece[3]

       yellow_gates = find_object(yellow_threshold, 50, 500, True, 30)
       yellow_angle, yellow_distance = yellow_gates[2], yellow_gates[3]
       yellow_piece = find_object(yellow_threshold, 20, 100, False, 0)
       yellow_piece_angle, yellow_piece_distance = yellow_piece[2], yellow_piece[3]
       red_ball = find_object(red_threshold, 3, 7, True, 5)
       ball_angle, ball_distance = red_ball[2], red_ball[3]


       img.draw_circle(red_ball[0], red_ball[1], 15, (255, 255, 255), 2)
       #print(blue_gates)

       #print(ball_distance)#start from yellow gate
       #send_data(10, 20, 30, 40, 50, 60)
       #print(ball_angle)
       #print(red_ball, red_ball[3], linearize(red_ball[-1]))
       send_data(yellow_angle, yellow_distance, blue_angle, blue_distance, ball_angle, ball_distance, blue_piece_angle, yellow_piece_angle)
       #img.draw_circle(blue_x_test, blue_y_test, 3, (255, 255, 255))
       #img.draw_circle(yellow[4], yellow[5], 3, (255, 255, 255))
       img.draw_rectangle(blue_gates[4], blue_gates[5], blue_gates[6], blue_gates[7], (0, 0, 200), 2)
       img.draw_rectangle(yellow_gates[4], yellow_gates[5], yellow_gates[6], yellow_gates[7], (200, 200, 0), 2)
       #if callibrate_center == False:
           #img.draw_circle(ball[4], ball[5], 3, (255, 255, 255))
       img.draw_circle(center[0], center[1], 20, (255, 255, 255))
       img.draw_circle(center[0], center[1], 5, (255, 255, 255))
    except Exception:
       print(1)
