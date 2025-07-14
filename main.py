import sensor, utime, image, time, pyb, math #import librares

EXPOSURE_TIME_SCALE = 0.9


callibrate_center = False

blue_x_test = 0
blue_y_test = 0

center1 = [163, 112]#[176, 130]
center2 = [163, 116]#[162, 118]

robot = 2
if robot == 1 or robot == 3:#attacker

    yellow_threshold = [(0, 100, -128, 34, 30, 127)]
    blue_threshold = [(0, 100, -128, 127, -128, -33)]
    red_threshold = [(0, 100, 43, 127, -2, 127)]#(62, 100, 46, 127, -128, 40)

    white = (-5, -6, -2)

    center = center1
    EXPOSURE_TIME_SCALE = 0.8
    img_radius = 140
    robot_radius = 18
    my_gain = 5
else:
    yellow_threshold = [(0, 50, -4, 27, 16, 127)]
    blue_threshold = [(0, 100, -128, 127, -128, -13)]
    red_threshold = [(0, 100, 12, 127, -128, 127)]

    white = (62, 60, 62)

    center = center2
    EXPOSURE_TIME_SCALE = 0.8
    img_radius = 135
    robot_radius = 15
    my_gain = 20
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
sensor.set_auto_exposure(True, \
    exposure_us = int(current_exposure_time_in_microseconds* EXPOSURE_TIME_SCALE))
clock = time.clock()
sensor.skip_frames(time = 500)


sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_auto_gain(False, gain_db = my_gain)
print(sensor.get_rgb_gain_db())
sensor.set_auto_whitebal(False, rgb_gain_db = white)#(-2.5, -7, -1.47639)
sensor.set_auto_exposure(False)
current_exposure_time_in_microseconds =  sensor.get_exposure_us()
sensor.set_auto_exposure(False, \
    exposure_us = int(current_exposure_time_in_microseconds* EXPOSURE_TIME_SCALE))
clock = time.clock()
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

data = bytearray(7)

def send_data(num1, num2, num3, num4, num5, num6):
    uart.writechar(255)
    num1 = int((num1) / 3)
    num2 = int((num2) / 3)
    num3 = int((num3) / 3)
    num4 = int((num4) / 3)
    num5 = int((num5) / 3)
    num6 = int((num6) / 3)

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
#    data[0] = num1
#    data[1] = num2
#    data[2] = num3
#    data[3] = num4
#    data[4] = num5
#    data[5] = num6
    data[6] = crc8(data, 6)

    uart.writechar(int(data[0]))
    uart.writechar(int(data[1]))
    uart.writechar(int(data[2]))
    uart.writechar(int(data[3]))
    uart.writechar(int(data[4]))
    uart.writechar(int(data[5]))
    uart.writechar(int(data[6]))



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

       #detecting yellow gate
       for blob in img.find_blobs(yellow_threshold, pixels_threshold=50, area_threshold=600, merge=True, margin = 20):#finding gates
           if(blob[2] * blob[3] > old_area):
               old_area = blob[2] * blob[3]
               #print(blob)
               yellow = [blob[0], blob[1], blob[0] + blob[2], blob[1] + blob[3],(blob[0] + int(blob[2] / 2)), (blob[1] + int(blob[3] / 2)), blob[2], blob[3]]
               yellow_x = -(blob.cx() - center[0])
               yellow_y = -(blob.cy() - center[1])
               yellow_distance = linearize(get_distance(yellow_x, yellow_y))
               yellow_angle = math.floor(math.atan2(yellow_x, yellow_y) * 57.3)
               yellow_smth = blob.solidity()
               if yellow_angle == 0:
                   yellow_angle += 1

       if(yellow_angle > 360):
           yellow_angle -= 360
       elif(yellow_angle < 0):
           yellow_angle += 360

       if(old_area < 50):
           yellow_distance = 0
       old_area = 0



       #detecting blue gate
       for blob in img.find_blobs(blue_threshold, pixels_threshold=50, area_threshold=50, merge=True, margin = 10): #finding gates
           if(blob[2] * blob[3] > old_area and blob[2] * blob[3] > 60):
               old_area = blob[2] * blob[3]
               #img.draw_rectangle(blob[0], blob[1], blob[2], blob[3], (0, 0, 200), 2)
               #blue = [blob[0], blob[1], blob[0] + blob[2], blob[1] + blob[3], blob.cx(), blob.cy()]
               blue = [blob[0], blob[1], blob[0] + blob[2], blob[1] + blob[3],(blob[0] + int(blob[2] / 2)), (blob[1] + int(blob[3] / 2)), blob[2], blob[3]]
               #blue_x = -(blue[4] - center[0])
               #blue_y = -(blue[5] - center[1])
               blue_x = -(blob.cx() - center[0])
               blue_y = -(blob.cy() - center[1])
               blue_x_test = blob.cx()
               blue_y_test = blob.cy()
               blue_distance = linearize(get_distance(blue_x, blue_y))
               blue_angle = math.floor(math.atan2(blue_x, blue_y) * 57.3)
               if(blue_angle > 360):
                   blue_angle -= 360
               elif(blue_angle < 0):
                   blue_angle += 360
       if(old_area < 50):
           blue_distance = 0
       old_area = 0
       my_blobs = []
       old_roundness = 0
       max_area = 0
       ball_data = [center[0], center[1]]
       ball_distance = 0
       for blob in img.find_blobs(red_threshold, pixels_threshold=25, area_threshold=25 , merge=True, margin = 10):
           if blob.area() >= 3:
               if blob.compactness() > old_roundness:
                  #red = [blob[0], blob[1], blob[0] + blob[2], blob[1] +      blob[3],(blob[0] + int(blob[2] / 2)), (blob[1] + int(blob[3] / 2)), blob[2], blob[3]]
                   old_roundness = blob.compactness()
                   my_blob = blob
                   max_area = blob.area()
                   my_blob_x = blob.cx()
                   my_blob_y = blob.cy()
                   ball_data = [blob.cx(), blob.cy()]
                   ball_x = -(my_blob_x - center[0])
                   ball_y = -(my_blob_y - center[1])
                   ball_distance = linearize(get_distance(ball_x, ball_y))
                   ball_angle = math.floor(math.atan2(ball_x, ball_y) * 57.3)
                   if(ball_angle > 360):
                       ball_angle -= 360
                   elif(ball_angle < 0):
                       ball_angle += 360
       #print(max_area)


       #img.draw_line(yellow[4], yellow[5], blue[4], blue[5], (255, 255, 255), 2) #line between centers of gates

       img.draw_circle(ball_data[0], ball_data[1], 25, (255, 255, 255), 2)

       if yellow_angle > 359:
           yellow_angle -= 360
       if blue_angle > 359:
           blue_angle -= 360
       if ball_angle > 359:
           ball_angle -= 360
       #print(ball_distance)#start from yellow gate
       #send_data(10, 20, 30, 40, 50, 60)
       #print(ball_angle)
       send_data(yellow_angle, yellow_distance, blue_angle, blue_distance, ball_angle, ball_distance)
       #img.draw_circle(blue_x_test, blue_y_test, 3, (255, 255, 255))
       #img.draw_circle(yellow[4], yellow[5], 3, (255, 255, 255))
       img.draw_rectangle(blue[0], blue[1], blue[6], blue[7], (0, 0, 200), 2)
       img.draw_rectangle(yellow[0], yellow[1], yellow[6], yellow[7], (200, 200, 0), 2)
       #if callibrate_center == False:
           #img.draw_circle(ball[4], ball[5], 3, (255, 255, 255))
       img.draw_circle(center[0], center[1], 3, (255, 255, 255))
    except Exception:
       pass
