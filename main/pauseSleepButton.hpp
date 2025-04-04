/**
 * @file pauseSleepButton.hpp
 * @brief pause/sleep button setup and control functionality
 * @version 3.1
 * @date 2023-11-16
 */
// #include "NimBLEDevice.h"
// #include "SPIFFS.h"
// #include "Adafruit_DRV2605.h"
#include <Wire.h>
#include <sstream>
#include <string>
#define PAUSEWAIT 1000

#ifndef pauseSleepButton_hpp
#define pauseSleepButton_hpp

// #include "common.hpp"
// #include "hapticMotor.hpp"
//Change this to 1 to enable debug output printing for pause/sleep button functionality
#define DEBUG_PAUSE_BUTTON 0

//Constants
const int buttonDebounceTimeMS = 15;
const int buttonSleepTimeMS = 2000;

const int pause_button = 0;

//Variables
static volatile bool buttonPressed = false;
static volatile int buttonPressedTimeMS = 0;

static volatile bool pauseStatus = false;
static volatile bool sleepStatus = false;

//Access functions
bool readPauseStatus();
bool readSleepStatus();

//Setup Functions
void setupPauseSleepButton();

//Pause/Sleep Functions
void goToSleep();
void pausehandler();

#endif