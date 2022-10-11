# -*-coding:UTF-8-*-
import re
import time
import datetime
import random
import serial  # 導入serial庫
# Reference: https://www.twblogs.net/a/5f04ab112f43ae5e2bb6d720?fbclid=IwAR2vjcQhtJKwRMsgHVXhXKf-3J-knV75XqKnrHqp0uwZPnNFFehbhoaHdpE
# ls /dev/tty*
port_name = '/dev/tty.usbserial-D307TEN6'  # Mac
baud_rate = 9600
# port_name = '/dev/ttyUSB0'  # Pi 4B
ser = serial.Serial(port_name, baud_rate, timeout=0.3)  # 打開端口，每一秒返回一個消息

x = 0
y = 0
try:
    is_response_get = True
    # last_time = time.time()
    while True:
        now = time.time()
        dx = round(random.uniform(-180, 180), 2)
        dy = round(random.uniform(-180, 180), 2)
        # x = (x + int(dx) + 360) % 180
        # y = (y + int(dy) + 360) % 180
        # print(f"x:{x}, y:{y}")
        # print(f"dx:{dx}, dy:{dy}")

        if is_response_get:
            data_in_string = f"{dx},{dy},".strip()
            data_to_be_send = data_in_string.encode(encoding='ASCII')
            print(
                f"[{datetime.datetime.now()}] Write:{data_to_be_send}")
            ser.write(data_to_be_send)
            ser.flush()
            time.sleep(0.1)
            last_time = time.time()
            is_response_get = False
        response = ser.readall()  # 用response讀取端口的返回值
        if response:
            is_response_get = True
            # 進行打印
            print(
                f"[{datetime.datetime.now()}] Response:{response.decode('UTF8')}")
except Exception as e:
    print("Stop Serial Transmittion, beacause of: ", e)
    ser.close()  # 拋出異常後關閉端口py
