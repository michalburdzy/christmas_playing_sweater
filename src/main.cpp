#include <Arduino.h>

#include "pitches.h"

#define LED_1_PIN 0
#define MELODY_BUZZER_PIN 1
#define LED_2_PIN 2
#define LED_3_PIN 3
#define LED_4_PIN 4
#define LED_5_PIN 5
#define BUILTIN_LED_PIN 13

int currentSong = 0;

int jingle_bells_melody[] = {
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
    NOTE_E5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
    NOTE_D5, NOTE_G5,

    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
    NOTE_E5,
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
    NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
    NOTE_G5, NOTE_G5, NOTE_F5, NOTE_E5,
    NOTE_C5};

int jingle_bells_tempo[] = {
    8, 8, 4,
    8, 8, 4,
    8, 8, 6, 10,
    2,
    8, 8, 8, 8,
    8, 8, 8, 16, 16,
    8, 8, 8, 8,
    4, 4,

    8, 8, 4,
    8, 8, 4,
    8, 8, 6, 10,
    2,
    8, 8, 8, 8,
    8, 8, 8, 16, 16,
    8, 8, 8, 8,
    2};

// We wish you a merry Christmas

int wish_melody[] = {
    NOTE_C5,
    NOTE_F5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5,
    NOTE_D5, NOTE_AS3, NOTE_AS3,
    NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5,
    NOTE_E5, NOTE_C5, NOTE_C5,
    NOTE_A5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_G5,
    NOTE_F5, NOTE_D5, NOTE_C5, NOTE_C5,
    NOTE_D5, NOTE_G5, NOTE_E5,
    NOTE_F5};

int wish_tempo[] = {
    4,
    4, 8, 8, 8, 8,
    4, 4, 4,
    4, 8, 8, 8, 8,
    4, 4, 4,
    4, 8, 8, 8, 8,
    4, 4, 8, 8,
    4, 4, 4,
    2};
int melodyButton = 0;
int switchTwo = 0;
int switchThree = 0;

void lightLeds(bool on)
{
  if (on)
  {
    digitalWrite(BUILTIN_LED_PIN, HIGH);
    digitalWrite(LED_1_PIN, HIGH);
    digitalWrite(LED_2_PIN, HIGH);
    digitalWrite(LED_3_PIN, HIGH);
    digitalWrite(LED_4_PIN, HIGH);
    digitalWrite(LED_5_PIN, HIGH);
  }
  else
  {
    digitalWrite(BUILTIN_LED_PIN, LOW);
    digitalWrite(LED_1_PIN, LOW);
    digitalWrite(LED_2_PIN, LOW);
    digitalWrite(LED_3_PIN, LOW);
    digitalWrite(LED_4_PIN, LOW);
    digitalWrite(LED_5_PIN, LOW);
  }
}

void buzz(int targetPin, long frequency, long length)
{
  lightLeds(true);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++)
  {                                // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW);  // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  lightLeds(false);
}

void sing(int s)
{
  currentSong = s;
  if (currentSong == 1)
  {
    Serial.println(" 'We wish you a Merry Christmas'");
    int size = sizeof(wish_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++)
    {
      int noteDuration = 1000 / wish_tempo[thisNote];

      buzz(MELODY_BUZZER_PIN, wish_melody[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;

      delay(pauseBetweenNotes);

      buzz(MELODY_BUZZER_PIN, 0, noteDuration);
    }
  }
  else
  {

    Serial.println(" 'Jingle Bells'");
    int size = sizeof(jingle_bells_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++)
    {
      int noteDuration = 2000 / jingle_bells_tempo[thisNote];

      buzz(MELODY_BUZZER_PIN, jingle_bells_melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      buzz(MELODY_BUZZER_PIN, 0, noteDuration);
    }
  }
}

void setup(void)
{
  pinMode(MELODY_BUZZER_PIN, OUTPUT);
  pinMode(BUILTIN_LED_PIN, OUTPUT);
  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(LED_5_PIN, OUTPUT);
}

void loop()
{
  sing(1);
  delay(1000);
  sing(2);
  delay(1000);
}
