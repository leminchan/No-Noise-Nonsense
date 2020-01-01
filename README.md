# No-Noise-Nonsense

Created by [Mit Chan](https://github.com/leminchan) and [Chase Carnaroli](https://github.com/ChaseC99)  
Comp Sci 147 - IoT Software and Systems  
Final Project Grade: 100% (A+)

## Project Demo
Video Demonstration:
https://drive.google.com/file/d/1aC80UNEgAXVEkogtBMRAdjCkAqvJHCW1/view?usp=sharing  

Noise Data Image  
![Noise Data Image](https://github.com/leminchan/No-Noise-Nonsense/blob/master/noise_data_example.png?raw=true)

## Project Description
The No Noise Nonsense device constantly monitors the noise level of the room, 
sending that information to the cloud where we are able to see the noise data throughout the day. 
If the noise level exceeds a certain threshold it will trigger an alert with the Grove Buzzer, 
indicating that the room is too loud. 
At the same time, it will also send a notification via email to the person in charge of the room using Microsoft Azure services.
Our Arduino Uno uses the Grove Shield and Sound Sensor to monitor the noise level of the room.
Every 50 milliseconds, the amplitude of the sound (highest value - lowest value) is calculated. 
Every 3 seconds, the average amplitude is sent to a SparkFun ESP8266 Thing via Serial Communication. 
The SparkFun then transmits this information via WiFi to our Microsoft Azure Cloud Server. 
If the SparkFun notices that 3 of the previous 5 average amplitudes exceeds the noise level threshold, 
it sends an email notification using Azure services to the room owners and activates the Grove Buzzer until the noise level returns to an appropriate level. 
For our web application, we created the website with HTML, CSS, and Javascript. 
We then visualized the noise data in a chart using jQuery and Chart.js.


## Project Motivation
As Resident Advisors in the 1st year dorms, we constantly struggle with quiet hours. 
Residents love making noise in their suites and the common room all throughout the night. 
Having to remind residents of quiet hours every night can get frustrating.  
This device is able to indidate to residents that the noise level is too high for quiet hours and it also tracks the noise level of the room throughout the day, 
giving us solid data to help us better understand when residents are being loud.
