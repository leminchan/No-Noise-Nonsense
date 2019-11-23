/*
No Noise Nonsense

Created by Chase Carnaroli and Mit Chan
For Computer Science 141 - Taught by Sergio Gago-Masague
*/

#define SOUND_SENSOR 1 
#define BUZZER 6
#define THRESHOLD_VALUE 100 
#define ON HIGH
#define OFF LOW

#define ONE_SECOND 1000 
#define FIFTEEN_SECONDS 15000

unsigned long one_second_timer;
unsigned long fifteen_second_timer;

long sound_level_per_sec_avg = 0;
unsigned long sound_level_per_sec_count = 0;
long sound_level_per_fifteen_sec_avg = 0;
unsigned long sound_level_per_fifteen_sec_count = 0;

void setup() 
{
  /* Initialize led pin */
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, OFF);
  Serial.begin(9600);

  one_second_timer = millis() + ONE_SECOND;
  fifteen_second_timer = millis() + FIFTEEN_SECONDS;
}

long addToAvg(long value, long avg, long count) 
{
  //Serial.print(value);Serial.print(" avg: ");Serial.print(avg);Serial.print(" count: ");Serial.print(count);Serial.print(" result: ");Serial.println(avg + (value-avg) / count);
  return avg + (value-avg) / count;
}

void loop() {
  if (one_second_timer < millis())
  {
    Serial.print(millis()/1000);
    Serial.print(": ");
    Serial.println(sound_level_per_sec_avg);

    sound_level_per_fifteen_sec_count++;
    sound_level_per_fifteen_sec_avg = addToAvg(sound_level_per_sec_avg, sound_level_per_fifteen_sec_avg, sound_level_per_fifteen_sec_count);
    
    sound_level_per_sec_avg = 0;
    sound_level_per_sec_count = 0;
   
    one_second_timer = millis() + ONE_SECOND;
  }

  if (fifteen_second_timer < millis())
  {
    Serial.println("-------------------------------");
    Serial.print("15 Second Avg: ");
    Serial.println(sound_level_per_fifteen_sec_avg);
    Serial.println("-------------------------------");

    //If the noise level exceeds the threshold, trigger the buzzer
    if (sound_level_per_fifteen_sec_avg > THRESHOLD_VALUE)
    {
      digitalWrite(BUZZER, ON);
      delay(1000);
      digitalWrite(BUZZER, OFF);
      delay(200);
    }

    sound_level_per_fifteen_sec_avg = 0;
    sound_level_per_fifteen_sec_count = 0;

    fifteen_second_timer = millis() + FIFTEEN_SECONDS;
  }
  
  // Read sound level, add it to sound_level_per_sec_avg
  sound_level_per_sec_count++;
  sound_level_per_sec_avg = addToAvg(analogRead(SOUND_SENSOR), sound_level_per_sec_avg, sound_level_per_sec_count);
  
}
