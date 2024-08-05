"""
title: "Code for Irradience Sensor to txt File"
date: "08/05/2024"
author: "Babur Erdem"
update date: "08/05/2024"
"""

import serial
import time

ser = serial.Serial('COM6', 9600, timeout=1)  # Change 'COM6' to your Arduino's serial port
time.sleep(2)  


with open('sensor_data.txt', 'w') as file:
    file.write("Date\tTime\tML8511_IrrUV\tTSL2561_IrrBroad\tTSL2561_IrrIR\tHumidity\tTemperature\n")

    while True:
        try:
            line = ser.readline().decode('utf-8').strip()
            if line:
                print(line)  
                if "TSL2561 - Broadband" in line:
                    tsl_data = line.split('|')
                    irr_broad = tsl_data[2].split(':')[1].strip().split()[0]
                    irr_ir = tsl_data[3].split(':')[1].strip().split()[0]

                if "ML8511 - Reference" in line:
                    ml_data = line.split('|')
                    uv_irr = ml_data[3].split(':')[1].strip().split()[0]

                if "DHT22 - Humidity" in line:
                    dht_data = line.split('|')
                    humidity = dht_data[0].split(':')[1].strip().split()[0]
                    temperature = dht_data[1].split(':')[1].strip().split()[0]

                    date = time.strftime("%Y/%m/%d")
                    current_time = time.strftime("%H:%M:%S")

                    file.write(f"{date}\t{current_time}\t{uv_irr}\t{irr_broad}\t{irr_ir}\t{humidity}\t{temperature}\n")
                    file.flush()  

                    print(f"{date}\t{current_time}\t{uv_irr}\t{irr_broad}\t{irr_ir}\t{humidity}\t{temperature}")

        except KeyboardInterrupt:
            break

ser.close()
