# -*-coding:UTF-8-*-
import time
import serial  # 導入serial庫
# ls /dev/tty*
port_name = '/dev/tty.usbserial-D307TEN6'  # Mac
# port_name = '/dev/ttyUSB0'  # Pi 4B
ser = serial.Serial(port_name, 115200, timeout=0.3)  # 打開端口，每一秒返回一個消息
data_in_string = '100,-250'
data_to_be_send = str.encode(data_in_string)
print("data_to_be_send: ", data_to_be_send)
try:
    while True:
        ser.write(data_to_be_send)  # 寫s字符
        response = ser.readall()  # 用response讀取端口的返回值
        print("Response:", response)  # 進行打印
        time.sleep(1)
except Exception as e:
    print("Stop Serial Transmittion, beacause of: ", e)
    ser.close()  # 拋出異常後關閉端口py
