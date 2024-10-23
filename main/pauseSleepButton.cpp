/**
 * @file hapticMotor.cpp
 * @brief Pause/Sleep button ISR's and functions
 * @version 3.1
 * @date 2023-11-16
 */

#include "pauseSleepButton.hpp"
#include <Arduino.h>

/**
 * @brief Returns status of pause button
 * @param none
 * @return pauseStatus
 */
bool readPauseStatus()
{
  return pauseStatus;
}

/**
 * @brief Returns status of sleep button
 * @param none
 * @return sleepStatus
 */
bool readSleepStatus()
{
  return sleepStatus;
}

/**
 * @brief Pause Button ISR
 * This will trigger on both rising and falling edges
 *
 * @return None
 */
void IRAM_ATTR pauseButton()
{
  Serial.println("Pressed");
  if (digitalRead(pause_button) == LOW)
  {
    buttonPressed = true;
    buttonPressedTimeMS = millis();
  }
  else if (digitalRead(pause_button) == HIGH)
  {
    if (buttonPressed)
    {
      buttonPressed = false;
      int buttonHeldTimeMs = millis() - buttonPressedTimeMS;
      if (buttonHeldTimeMs > buttonSleepTimeMS)
      {
        // Sleep (Long press)
        // sleepStatus = ~sleepStatus; // Toggle sleep status (Wake up if already sleeping, else sleep)

        switch (sleepStatus)
        {
        case true:
          sleepStatus = false;
          break;
        case false:
          sleepStatus = true;
          goToSleep();
        }
      }
      else if (buttonHeldTimeMs > buttonDebounceTimeMS)
      {
        // Pause (Short press)
        // pauseStatus = ~pauseStatus; // Toggle pause status
        switch (pauseStatus)
        {
        case true:
          pauseStatus = false;
          break;
        case false:
          pauseStatus = true;
        }
      }
    }
  }
}

/**
 * @brief Pause Button Setup
 *
 * @return None
 */
void setupPauseSleepButton()
{
#if DEBUG_PAUSE_BUTTON
  Serial.println("Pause/Sleep Button Setup");
#endif

  sleepStatus = false;
  pauseStatus = false;

  pinMode(pause_button, INPUT);
  attachInterrupt(pause_button, pauseButton, CHANGE);
}

/**
 * @brief Sleep Handler
 *
 * @return None
 */
void goToSleep()
{
#if DEBUG_PAUSE_BUTTON
  Serial.println("Sleep/Wakeup");

  //   Serial.print(sleepStatus);
  // Serial.print(", ");
  //   Serial.print(pauseStatus);
  //   Serial.print(", ");
  //   Serial.println(songReady);
#endif
  /**
  * // Turn all motors OFF
    digitalWrite(drv_1_en, LOW);
    digitalWrite(drv_2_en, LOW);
    digitalWrite(drv_3_en, LOW);
    digitalWrite(drv_4_en, LOW);
    digitalWrite(drv_5_en, LOW);

  */

  delay(PAUSEWAIT);

  esp_deep_sleep_enable_gpio_wakeup(0b1ULL, ESP_GPIO_WAKEUP_GPIO_LOW); // 1 = High, 0 = Low

  esp_deep_sleep_start();
}

/**
 * @brief Pause Handler
 *
 * @return None
 */
void pausehandler()
{
#if DEBUG_PAUSE_BUTTON
  Serial.println("Pause/Play");
#endif

  /**
  *
  // Turn all motors OFF
  digitalWrite(drv_1_en, LOW);
  digitalWrite(drv_2_en, LOW);
  digitalWrite(drv_3_en, LOW);
  digitalWrite(drv_4_en, LOW);
  digitalWrite(drv_5_en, LOW);
  *
  */

  detachInterrupt(pause_button);

  delay(PAUSEWAIT);

  esp_deep_sleep_enable_gpio_wakeup(GPIO_NUM_0, ESP_GPIO_WAKEUP_GPIO_LOW); // 1 = High, 0 = Low

  esp_light_sleep_start();

  pauseStatus = false;
  sleepStatus = false;

  attachInterrupt(pause_button, pauseButton, CHANGE);

  // while (pauseStatus); // Block till user presses pause/play again (Short press on pause button)
}