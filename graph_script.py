import time
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
fig,(ax1,ax2) =  plt.subplots(2,1, sharex=True, figsize=(8,8))

ax1.plot(TMinds, RHinds, 'y')
ax2.plot(TMinds, TCinds, 'b')
#ax2.set_title('Temperature (Celsius)')
#ax1.set_title('Relative Humidity')
plt.setp(ax2, ylabel='Temperature (C)',xlabel='Date')
plt.setp(ax1, ylabel='Relative Humidity')
plt.savefig('Sensor_plot')