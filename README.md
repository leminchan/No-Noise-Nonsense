# No-Noise-Nonsense

Created by Mit Chan and Chase Carnaroli
Comp Sci 147 - IoT Software and Systems

## Project Description
The device constantly monitors the noise level of the room, sending that information to the cloud
where we would be able to see the noise data throughout the day. If the noise level exceeds a certain
threshold during specific hours (eg. quiet hours), it will trigger a flashing light and a noise indicating
that the room is too loud.
If the noise level continues to be exceeded, then we are notified as a result.
This device has the Architecture 2 (Sensor-Cloud) from the notes. The Sound Sensor constantly
logs the noise level data while the on-board wifi chip communicates data to the cloud.


## Project Motivation
As Resident Advisors in the 1st year dorms, we constantly struggle with quiet hours. Residents love
making noise in their suites and the common room all throughout the night. Having to remind
residents of quiet hours every night can get frustrating.  
This device is able to indidate to residents that the noise level is too high for quiet hours 
and it also tracks the noise level of the room throughout the day, giving us solid data to help
us better understand when residents are being loud.
