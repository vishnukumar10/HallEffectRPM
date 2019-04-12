# HallEffectRPM

ABSTRACT 
 
As Engineers we always rely upon the data collected to design or improve a system. Recording data and analyzing them is a common practice in most of the industries, here we are building a Racecar Dashboard for which we will be using a Hall Effect Sensor. A Hall Effect Sensor Analyses the intensity of magnetic field near it. The same principle is applied in a car. If the Magnet is placed in the wheel which is in motion and if the Hall Effect Sensor is placed on a stationery position near the wheel, every time the magnet attached on the wheel passes through the sensor, a reading is obtained based on the speed with which the magnet passes through the sensor. So, every time the wheel rotates, we get a reading. With the help of RPM, depending upon the size of the wheel we can calculate the speed with which the wheel is rotating, ie., the velocity of the car. Thus, giving us a comprehensive idea of the motion speed and RPM of the car. We use ESP8266 to record and send the data to Adafruit.(If Arduino is alone used, the remaining can be ignored) The main reason for using Adafruit is so that the details of the car can be viewed from the Racetrack Pit by the rest of the team on the same feed that is used by the car. The data recorded in the Adafruit feed can be downloaded and analyzed to improve the future performances.  
 
 
SOFTWARE REQUIRED: • Arduino IDE. • ESP8266 library. 

REQUIREMENTS:
• HallEffect Sensor
• Arduino Uno or ESP8266 and Arduino software on PC 
• A few Jumper Cables (Male to Female) 
   or Male to Male with Breadboard
   
Steps and Connection Specification:
The Hall Effect sensor uses the magnitude of a magnetic field to measure proximity sensing, positioning, speed detection, and current sensing applications.  It is placed at a stationary point in the wheel of the car and the magnet is placed on one of the spokes of the wheel on the inner side which rotates. 
Make the required connections. Every time the magnetic sensor comes near the sensor, the sensor takes in the input by measuring the magnitude and sends it to ESP8266 board. 
The board which is connected to the Wi-Fi with the help of the User name and AIO key sends the data to the specific feed that is mentioned in the code. That is, it publishes the data onto the dashboard and the feed. 
This data can be viewed real time on the dashboard and the feed. 
[Pin 1] The GND connects to the GND on the board.  
[Pin 2] The Source pin (S) connects to the Voltage supply in the board.  
[Pin 3] And the V.out is connected to the D2 on board. 

DETAILED EXPLANATION AT:
https://youtu.be/9_FRK3s-XQQ

CHANGES:
The velocity specified in the above code can be changed according to your convenience, but the RPM will remain the same.
