# Irradiance Sensor
This project involves creating an irradiance sensor using Arduino and Python to measure and log irradiance, humidity, and temperature. The sensor readings are saved to a text file for further analysis.

## Contents
- `IrradienceMeasurer.ino`: Arduino code for the sensor
- `SensorWriter.py`: Python script to read data from the Arduino and save it to a text file
- `SensorCircuitDiagram.pdf`: Circuit diagram for the project

## Requirements
### Hardware
- Arduino Uno (or compatible board)
- ML8511 UV Sensor Module
- TSL2561 Luminosity Sensor Module
- DHT22 Temperature and Humidity Sensor Module
- Breadboard and connecting wires

### Software
- Arduino IDE
- Python 3.x

#### Libraries for Arduino Ide
- Adafruit_Sensor
- Adafruit_TSL2561_U
- Adafruit_MLX90614
- DHT
#### Libraries for Python
- pyserial
- time

## Usage
- Connect the sensors to the Arduino as per the circuit diagram.
- Upload the Arduino code (IrradienceMeasurer.ino) to the Arduino.
- Run the Python script (SensorWriter.py) to start logging data.

## Notes
- According to the datasheet of the TSL2561 sensor ( http://www.adafruit.com/datasheets/TSL2561.pdf ), operating characteristics are defined as High Gain (16x), VDD = 3V. Because of that reason, the sensor is connected to 3.3V, and the gain is set to 16x to amplify low light signals, making the sensor more sensitive. The integration time is set to 101 ms, providing a balance between signal accuracy and response time. Given coefficients are used to convert the raw output of the module to µW/cm². The sensor has two channels; one is fit to measure VIS (Ch0), and the other is fit to IR spectrum (Ch1). The conversion coefficients are defined as 27.5 (in test condition λp = 640 nm) for Ch0 and 6.9 for (in test condition λp = 940 nm) Ch1. 
- Modules on the market can carry either sensor TSL2561T or sensor TSL2561CS. The coefficients we use are for sensor TSL2561T. If the module carries sensor TSL2561CS, the coefficients should be 24.4 for Ch0 and 6.3 for Ch1. Therefore, check which sensor is on the module.

