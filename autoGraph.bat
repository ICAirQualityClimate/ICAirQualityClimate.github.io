@echo off
cd C:\Users\icairqualityclimate\Desktop\ICAirQualityClimate.github.io
python "graph_script.py"

git add Sensor_plot.png
git add sensor_data.txt
git commit -m "Updated graph and data"
git push