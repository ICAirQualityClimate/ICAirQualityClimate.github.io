import time
import numpy as np
import matplotlib.pyplot as plt
import datetime
import matplotlib.dates as mdates

TM = []
TC = []
RH = []

f = open("sensor_data.txt", "r")
line = f.readline()
line = f.readline()
while (line):
    split = line.split(",")
    string = split[0].strip()
    TM.append(datetime.datetime.strptime(string, '%Y-%m-%d %H:%M:%S'))
    RH.append(float(split[1].strip()))
    TC.append(float(split[2].strip()))
    line = f.readline()
minDate = max(TM)-datetime.timedelta(5)
TMinds=[Tnum for Tnum in TM if Tnum >= minDate]
length = len(TMinds)
RHinds = RH[-length:]
TCinds = TC[-length:]
plt.gca().xaxis.set_major_formatter(mdates.DateFormatter('%Y/%m/%d %H:%M:%S'))
plt.gca().xaxis.set_major_locator(mdates.DayLocator())
plt.gcf().autofmt_xdate()
fig,(ax1)=  plt.subplots(figsize=(8,8))

ax2 = ax1.twinx()
ax2.plot(TMinds, RHinds, 'r')
ax1.plot(TMinds, TCinds, 'b')
ax1.set_title('Conditions in CNS 273')
plt.setp(ax1, ylabel='Temperature (C)',xlabel='Date')
plt.setp(ax2, ylabel='Relative Humidity')
ax1.yaxis.label.set_color('blue')
ax2.yaxis.label.set_color('red')
plt.savefig('Sensor_plot')