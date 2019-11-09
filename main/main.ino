/*
//LED anode (long leg) attached to RED_LED
//LED cathode (short leg) attached to ground
//Note:
This example code is in the public domain.
http://www.seeedstudio.com/depot/Grove-Sound-Sensor-p-752.html?cPath=25_128
*/
#define SOUND_SENSOR 1 /* sound sensor pin */
#define LED 12 /* LED pin */
#define THRESHOLD_VALUE 600 /* Depending on your LaunchPad’s ADC resolution you may
have to adjust the threshold */
#define ON HIGH /* led on */
#define OFF LOW /* led off */
#define _handle_led(x) digitalWrite(LED, x) /* handle led */
/* Global Variables */
unsigned long sound_value = 0;
unsigned long count = 0;
unsigned long sound_value_sum = 0;
unsigned long average_sound_value;
unsigned long timer = millis() + 7000; // 10 = measure every 10 seconds

void setup() {

 /* Initialize led pin */
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  Serial.begin(9600);
}
void loop() {

  if (timer < millis())
  {
    average_sound_value = sound_value_sum / count;
    Serial.print("avg sound value: ");
    Serial.println(average_sound_value);
    delay(2000);
    timer = millis() + 7000;
    count = 0;
  }
  
  /* read the sound value */
  sound_value = analogRead(SOUND_SENSOR);
  Serial.println(sound_value);

  sound_value_sum += sound_value;
  
  /* if the value is larger than threshold, turn on led */
  if(sound_value > THRESHOLD_VALUE) {
    _handle_led(ON);
    //delay(1000);
 }
  _handle_led(OFF);
  count++;
}
