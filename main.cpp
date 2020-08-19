#include <Arduino.h>
#define LED_TIMER1 9
#define LED_TIMER2 9
#define LED_TIMER3 9
#define LED_TIMER4 9
#define LED_TIMER5 9
#define LED_TIMER6 9
#define LED_MODE_CURE 9
#define LED_MODE_WASH 9
#define LED_BACKLIGHT 9
#define BUTTON_MODE 3
#define BUTTON_CONTROL 3
#define BUTTON_TIMER 3
#define OUTPUT_CURE 9
#define OUTPUT_WASH 9
#define OUTPUT_BUZZER 9

// Состояния  ========+++++++++++++================================================
boolean mode = false;   //false - WASH, true - CURE
boolean status = false; //false - free, true - occupied
int timer = 0;          // 0 - 6

// Иннициаллизация функций ========================================================
void interrupt();
void switchMode();
void pollTimerButton();
void pollModeButton();
void incrementTimer();
void setTimer(int inputTimer);
void run();
void forceKill();
void countdown();
void megalovania();

void setup()
{
  delay(100);
  Serial.begin(9600);
  pinMode(BUTTON_CONTROL, INPUT_PULLUP); // defaul HIGH
  pinMode(BUTTON_MODE, INPUT_PULLUP);    // defaul HIGH
  pinMode(BUTTON_TIMER, INPUT_PULLUP);   // defaul HIGH
  pinMode(LED_TIMER1, OUTPUT);
  pinMode(LED_TIMER2, OUTPUT);
  pinMode(LED_TIMER3, OUTPUT);
  pinMode(LED_TIMER4, OUTPUT);
  pinMode(LED_TIMER5, OUTPUT);
  pinMode(LED_TIMER6, OUTPUT);
  pinMode(LED_MODE_CURE, OUTPUT);
  pinMode(LED_MODE_WASH, OUTPUT);
  pinMode(LED_BACKLIGHT, OUTPUT);
  digitalWrite(LED_BACKLIGHT, 255);
  pinMode(OUTPUT_CURE, OUTPUT);
  pinMode(OUTPUT_WASH, OUTPUT);
  pinMode(OUTPUT_BUZZER, OUTPUT);
  switchMode();
  attachInterrupt(digitalPinToInterrupt(BUTTON_CONTROL), interrupt, CHANGE); // triggers when LOW
}

void loop()
{
  pollTimerButton();
  pollModeButton();
}

void switchMode()
{
  if (mode)
  {
    digitalWrite(LED_MODE_CURE, 255);
    digitalWrite(LED_MODE_WASH, 0);
  }
  else
  {
    digitalWrite(LED_MODE_CURE, 0);
    digitalWrite(LED_MODE_WASH, 255);
  }
  mode = !mode;
}

void pollTimerButton()
{
  while (digitalRead(BUTTON_TIMER) != HIGH)
  {
    beep();
    incrementTimer();
    delay(500);
  }
}

void pollModeButton()
{
  while (digitalRead(BUTTON_MODE) != HIGH)
  {
    beep();
    switchMode();
    delay(500);
  }
}

void incrementTimer()
{
  timer++;
  if (timer > 6)
  {
    timer = 0;
  }
  switch (timer)
  {
  case 0:
    digitalWrite(LED_TIMER6, 0);
    digitalWrite(LED_TIMER5, 0);
    digitalWrite(LED_TIMER4, 0);
    digitalWrite(LED_TIMER3, 0);
    digitalWrite(LED_TIMER2, 0);
    digitalWrite(LED_TIMER1, 0);
    break;
  case 6:
    digitalWrite(LED_TIMER6, 255);
  case 5:
    digitalWrite(LED_TIMER5, 255);
  case 4:
    digitalWrite(LED_TIMER4, 255);
  case 3:
    digitalWrite(LED_TIMER3, 255);
  case 2:
    digitalWrite(LED_TIMER2, 255);
  case 1:
    digitalWrite(LED_TIMER1, 255);
  }
}

void setTimer(int inputTimer)
{
  timer = inputTimer;
  if (timer > 6)
  {
    timer = 0;
  }
  switch (timer)
  {
  case 0:
    digitalWrite(LED_TIMER6, 0);
    digitalWrite(LED_TIMER5, 0);
    digitalWrite(LED_TIMER4, 0);
    digitalWrite(LED_TIMER3, 0);
    digitalWrite(LED_TIMER2, 0);
    digitalWrite(LED_TIMER1, 0);
    break;
  case 6:
    digitalWrite(LED_TIMER6, 255);
  case 5:
    digitalWrite(LED_TIMER5, 255);
  case 4:
    digitalWrite(LED_TIMER4, 255);
  case 3:
    digitalWrite(LED_TIMER3, 255);
  case 2:
    digitalWrite(LED_TIMER2, 255);
  case 1:
    digitalWrite(LED_TIMER1, 255);
  }
}

void beep()
{
  int beepDuration = 20;
  digitalWrite(OUTPUT_BUZZER, 255);
  delay(beepDuration);
  digitalWrite(OUTPUT_BUZZER, 0);
}

void run()
{
  status = true;
  for (size_t i = 0; i < 256; i++)
  {
    if (mode)
    {
      digitalWrite(OUTPUT_WASH, i);
    }
    else
    {
      digitalWrite(OUTPUT_CURE, i);
    }
    delay(20);
  }
  countdown();
  for (size_t i = 255; i >= 0; i--)
  {
    if (mode)
    {
      digitalWrite(OUTPUT_WASH, i);
    }
    else
    {
      digitalWrite(OUTPUT_CURE, i);
    }
    delay(20);
  }
  if (mode)
  {
    digitalWrite(OUTPUT_WASH, 0);
  }
  else
  {
    digitalWrite(OUTPUT_CURE, 0);
  }
  // beep();
  // delay(500);
  // beep();
  // delay(500);
  // beep();
  // delay(100);
  // beep();
  megalovania();
  status = false;
}

void countdown()
{
  int time = timer * 60 * 1000;
  int integerPart = time / 6;
  switch (integerPart)
  {
  case 6:
    for (size_t i = 60 * 1000; i >= 0; i--)
    {
      digitalWrite(LED_TIMER6, map(i, 60 * 1000, 0, 255, 0));
      delay(1);
    }
  case 5:
    for (size_t i = 60 * 1000; i >= 0; i--)
    {
      digitalWrite(LED_TIMER5, map(i, 60 * 1000, 0, 255, 0));
      delay(1);
    }
  case 4:
    for (size_t i = 60 * 1000; i >= 0; i--)
    {
      digitalWrite(LED_TIMER4, map(i, 60 * 1000, 0, 255, 0));
      delay(1);
    }
  case 3:
    for (size_t i = 60 * 1000; i >= 0; i--)
    {
      digitalWrite(LED_TIMER3, map(i, 60 * 1000, 0, 255, 0));
      delay(1);
    }
  case 2:
    for (size_t i = 60 * 1000; i >= 0; i--)
    {
      digitalWrite(LED_TIMER2, map(i, 60 * 1000, 0, 255, 0));
      delay(1);
    }
  case 1:
    for (size_t i = 60 * 1000; i >= 0; i--)
    {
      digitalWrite(LED_TIMER1, map(i, 60 * 1000, 0, 255, 0));
      delay(1);
    }
  }
}

void interrupt()
{
  beep();
  if (status)
  {
    forceKill();
  }
  else
  {
    run();
  }
}

void forceKill()
{
  for (size_t i = 255; i >= 0; i--)
  {
    if (mode)
    {
      digitalWrite(OUTPUT_WASH, i);
    }
    else
    {
      digitalWrite(OUTPUT_CURE, i);
    }
    delay(20);
  }
  if (mode)
  {
    digitalWrite(OUTPUT_WASH, 0);
  }
  else
  {
    digitalWrite(OUTPUT_CURE, 0);
  }
  status = false;
  setTimer(0);
  asm volatile("  jmp 0");
}

void megalovania()
{
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 250); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 247, 125); //B3
  delay(125);
  tone(OUTPUT_BUZZER, 247, 125); //B3
  delay(125);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 261, 125); //C4(middle)
  delay(62);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 247, 125); //B3
  delay(125);
  tone(OUTPUT_BUZZER, 247, 125); //B3
  delay(125);
  tone(OUTPUT_BUZZER, 587, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 233, 62); //Bb3
  delay(62);
  tone(OUTPUT_BUZZER, 588, 250); //D5
  delay(250);
  tone(OUTPUT_BUZZER, 440, 375); //A4
  delay(375);
  tone(OUTPUT_BUZZER, 415, 125); //Ab4
  delay(250);
  tone(OUTPUT_BUZZER, 392, 250); //G4
  delay(250);
  tone(OUTPUT_BUZZER, 349, 250); //F4
  delay(250);
  tone(OUTPUT_BUZZER, 294, 125); //D4
  delay(125);
  tone(OUTPUT_BUZZER, 349, 125); //F4
  delay(125);
  tone(OUTPUT_BUZZER, 392, 125); //G4
  delay(125);
}
