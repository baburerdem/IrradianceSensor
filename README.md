# Irradiance Sensor
This project involves creating an irradiance sensor using Arduino and Python to measure and log irradiance, humidity, and temperature. The sensor readings are saved to a text file for further analysis.

## Contents
- `IrradienceMeasurer.ino`: Arduino code for the sensor
- `SensorWriter.py`: Python script to read data from the Arduino and save it to a text file
- `SensorCircuitDiagram.pdf`: Circuit diagram for the project

## Requirements
### Hardware
- Arduino Uno (or compatible board)
- ML8511 UV Sensor
- TSL2561 Luminosity Sensor
- DHT22 Temperature and Humidity Sensor
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
