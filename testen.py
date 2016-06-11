#!/usr/bin/python3.4
import serial

while True:
        test = int(input("Test fuer: "))

ser = serial.Serial('/dev/ttyUSB0')
print(ser.name)
ser.write(test.encode())
ser.close()
