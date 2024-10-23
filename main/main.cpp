#include <APA102.h>
#include "pauseSleepButton.hpp"

#define PIN_BUTTON 0
#define PIN_CHRG_STAT 1
#define PIN_BATT_V 3
#define PIN_BOOT 9
#define PIN_LED_DATA 6
#define PIN_M1_PWM 2 // left glove thumb
#define PIN_M2_PWM 4 // left glove pinky
#define PIN_M3_PWM 5 // left glove ring
#define PIN_M4_PWM 7 // left glove middle
#define PIN_M5_PWM 8 // left glove pointer
#define PIN_LED_CLCK 10
#define PIN_D_MINUS 18
#define PIN_D_PLUS 19

#define PWM_FREQ 10
#define PWM_DUTY 250
#define PWM_RESO 10

#define DEV_LED_COUNT 4

APA102<PIN_LED_DATA, PIN_LED_CLCK> ledStrip;
rgb_color colors[DEV_LED_COUNT];

void writeBlues()
{
  for (uint16_t i = 0; i < DEV_LED_COUNT; i++)
  {
    colors[i].red = 30;
    colors[i].green = ;
    colors[i].blue = ;
  }
  ledStrip.write(colors, DEV_LED_COUNT, 5);
}

void initPWMs()
{
  pinMode(PIN_M1_PWM, OUTPUT);
  pinMode(PIN_M2_PWM, OUTPUT);
  pinMode(PIN_M3_PWM, OUTPUT);
  pinMode(PIN_M4_PWM, OUTPUT);
  pinMode(PIN_M5_PWM, OUTPUT);
  analogWrite(PIN_M1_PWM, 0);
  analogWrite(PIN_M2_PWM, 0);
  analogWrite(PIN_M3_PWM, 0);
  analogWrite(PIN_M4_PWM, 0);
  analogWrite(PIN_M5_PWM, 0);
}

void setup()
{
  initPWMs();
  writeBlues();
  Serial.begin(9600);
  setupPauseSleepButton();
}

void burstPulse(int pin)
{
  analogWrite(pin, PWM_DUTY);
  delay(250);
  analogWrite(pin, 0);
  delay(600);
}

int pins[5] = {PIN_M1_PWM, PIN_M2_PWM, PIN_M3_PWM, PIN_M4_PWM, PIN_M5_PWM};
int currMotor = 0;

void loop()
{
  burstPulse(pins[currMotor]);
  currMotor = (currMotor + 1) % 5;
  // Serial.println(CONFIG_ESP_SLEEP_GPIO_ENABLE_INTERNAL_RESISTORS);
  Serial.println(10);
}