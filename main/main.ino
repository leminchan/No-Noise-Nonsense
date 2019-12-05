/*
No Noise Nonsense

Created by Chase Carnaroli and Mit Chan
For Computer Science 141 - Taught by Sergio Gago-Masague
*/

#define SOUND_SENSOR 1 
#define BUZZER 6
#define THRESHOLD_VALUE 200 
#define ON HIGH
#define OFF LOW

#define AVG_TIMER 3000
#define FIFTY_MS 50 
#define FIFTEEN_SECONDS 15000

int max_level = 0;

unsigned long avg_timer;
unsigned long fifty_ms_timer;
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
  Serial.begin(115200);

  avg_timer = millis() + AVG_TIMER;
  fifteen_second_timer = millis() + FIFTEEN_SECONDS;
}

long addToAvg(long value, long avg, long count) 
{
  //Serial.print(value);Serial.print(" avg: ");Serial.print(avg);Serial.print(" count: ");Serial.print(count);Serial.print(" result: ");Serial.println(avg + (value-avg) / count);
  return avg + (value-avg) / count;
}

void sendLong(long value) 
{
  Serial.write(int(value) >> 8);    // send the high byte
  Serial.write(int(value) & 0xFF);  // send the low byte
}

long minSound = 10000;
long maxSound = 0;
long room_average = 0;
long temp_average = 0;
long temp_count = 0;

void loop() {
  if (fifty_ms_timer < millis())
  {
    int amplitude = maxSound - minSound;
    //Serial.print(amplitude);
    //Serial.print("\t");
    //Serial.println(room_average);

    minSound = 10000;
    maxSound = 0;

    temp_count++;
    temp_average = addToAvg(amplitude, temp_average, temp_count);
    fifty_ms_timer = millis() + FIFTY_MS;
  }

  if (avg_timer < millis())
  {
    
    room_average = temp_average;

    sendLong(room_average);

    temp_average = 0;
    temp_count = 0;
    avg_timer = millis() + AVG_TIMER;
  }

  long soundLevel = analogRead(SOUND_SENSOR);

  if (soundLevel < minSound) { minSound = soundLevel; }
  if (soundLevel > maxSound) { maxSound = soundLevel; }
  
  /*
  if (one_second_timer < millis())
  {
    //Serial.print(millis()/1000);
    //Serial.print(": ");
    Serial.println(sound_level_per_sec_avg);

    sendLong(sound_level_per_sec_avg);

    sound_level_per_fifteen_sec_count++;
    sound_level_per_fifteen_sec_avg = addToAvg(sound_level_per_sec_avg, sound_level_per_fifteen_sec_avg, sound_level_per_fifteen_sec_count);
    
    sound_level_per_sec_avg = 0;
    sound_level_per_sec_count = 0;

    one_second_timer = millis() + ONE_SECOND;
  }
  
  if (fifteen_second_timer < millis())
  {
    //Serial.println("-------------------------------");
    //Serial.print("15 Second Avg: ");
    //Serial.println(sound_level_per_fifteen_sec_avg);
    //Serial.println("-------------------------------");

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
  long sound_level = analogRead(SOUND_SENSOR);
  sound_level_per_sec_avg = addToAvg(sound_level, sound_level_per_sec_avg, sound_level_per_sec_count);
  delay(10);
  */
  
}
