import serial
import time
import matplotlib.pyplot as plt
from datetime import datetime
import os.path

# make sure the 'COM#' is set according the Windows Device Manager
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)


if True != os.path.exists('sensor_data.txt'):
    f = open("sensor_data.txt", "a+")
    f.write("Time, RH, TC\n")  #Write the header if no header is found
    f.close()

try:
    while True:
        line = ser.readline()   # read a byte string
        if line:
            f = open("sensor_data.txt", "a")
            date = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            f.write(date) #Write the date and time
            f.write(", ")
            string = line.decode()  # convert the byte string to a unicode string
            split_s = string.split(',') #Split the unicode string into an array of the data
            #print(split_s)
            f.write(split_s[0])
            f.write(", ")
            f.write(split_s[1])
            f.close()
except KeyboardInterrupt:
        print('interrupted!')
ser.close()
