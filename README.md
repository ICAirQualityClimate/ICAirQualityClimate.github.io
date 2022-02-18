ICAirQualityClimate.github.io

sensor_code.ino
	This code is for an Arduino Uno using the I2C shield wired to a SHT25 temperature humidity sensor
	Open Arduino IDE and move this file into the sketchbook.
	Compile and upload code to the arduino.

sensor_script.py
	Required Imports:
		serial
		time
		numpy
		matplotlib.pyplot as plt
		from datetime import datetime
		matplotlib.dates as mdates
		os.path

	First time set-up:
		Using the conda prompt, use the following command to create an arduino virtual environment
		"conda create -y -n arduino python=3.8"

		use the following command to activate the virtual environment 
		"conda activate arduino"

		In the arduino virtual environment install pyserial using the following command
		"conda install pyserial"
		
		
		Once completed you should be able to run sensor_script.py in conda prompt by navigating to 
		the directory that contains sensor_script.py and using the following commands
		"conda activate arduino"
		"python sensor_script.py"

		Or in powershell by navigating to the directory that contains sensor_script.py and using the following command
		"python sensor_script.py"

		If powershell doesn't work make sure try pip installing pyserial using
		"pip install pyserial"

	Running sensor_script.py
		While arduino is running and wired to the computer run sensor_script.py. The script will output a text file in the same
		folder it is contained in.		

		When you run the script, if there is an error make sure the com port # is correct by openining device manager
		and editing the code so that it is using the correct port.
		
		If the errors are caused by the imports, make sure to pip instal all required imports.

graph_script.py
	Once you have sensor_script.py outputting the text file "sensor_data.txt"
	Run autoGraph.bat
	This will output a graph!
		