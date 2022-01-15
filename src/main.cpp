//
//   SDL_Arduino_INA3221 Library Test Code
//   SDL_Arduino_INA3221.cpp Arduino code - runs in continuous mode
//   Version 1.2
//   SwitchDoc Labs   September 2019
//
//
// This was designed for SunAirPlus - Solar Power Controller - www.switchdoc.com
//


#include <Arduino.h>
#include <Wire.h>
//#include "SDL_Arduino_INA3221.h"
#include <SDL_Arduino_INA3221.h>


#define I2C_SDA 33
#define I2C_SCL 32

SDL_Arduino_INA3221 ina3221;

// the three channels of the INA3221 named for SunAirPlus Solar Power Controller channels (www.switchdoc.com)
#define LIPO_BATTERY_CHANNEL 1
#define SOLAR_CELL_CHANNEL 2
#define OUTPUT_CHANNEL 3

void setup(void) 
{
    
  Serial.begin(115200);
  Serial.println("SDA_Arduino_INA3221_Test");
  
  Serial.println("Measuring voltage and current with ina3221 ...");
  ina3221.begin();

  Serial.print("Manufactures ID=0x");
  int MID;
  MID = ina3221.getManufID();
  Serial.println(MID,HEX);
}

void loop(void) 
{
  
  Serial.println("------------------------------");
  float shuntvoltage1 = 0;
  float busvoltage1 = 0;
  float current_mA1 = 0;
  float loadvoltage1 = 0;


  busvoltage1 = ina3221.getBusVoltage_V(LIPO_BATTERY_CHANNEL);
  shuntvoltage1 = ina3221.getShuntVoltage_mV(LIPO_BATTERY_CHANNEL);
  current_mA1 = -ina3221.getCurrent_mA(LIPO_BATTERY_CHANNEL);  // minus is to get the "sense" right.   - means the battery is charging, + that it is discharging
  loadvoltage1 = busvoltage1 + (shuntvoltage1 / 1000);
  
  Serial.print("LIPO_Battery Bus Voltage:   "); Serial.print(busvoltage1); Serial.println(" V");
  Serial.print("LIPO_Battery Shunt Voltage: "); Serial.print(shuntvoltage1); Serial.println(" mV");
  Serial.print("LIPO_Battery Load Voltage:  "); Serial.print(loadvoltage1); Serial.println(" V");
  Serial.print("LIPO_Battery Current 1:       "); Serial.print(current_mA1); Serial.println(" mA");
  Serial.println("");

  float shuntvoltage2 = 0;
  float busvoltage2 = 0;
  float current_mA2 = 0;
  float loadvoltage2 = 0;

  busvoltage2 = ina3221.getBusVoltage_V(SOLAR_CELL_CHANNEL);
  shuntvoltage2 = ina3221.getShuntVoltage_mV(SOLAR_CELL_CHANNEL);
  current_mA2 = -ina3221.getCurrent_mA(SOLAR_CELL_CHANNEL);
  loadvoltage2 = busvoltage2 + (shuntvoltage2 / 1000);
  
  Serial.print("Solar Cell Bus Voltage 2:   "); Serial.print(busvoltage2); Serial.println(" V");
  Serial.print("Solar Cell Shunt Voltage 2: "); Serial.print(shuntvoltage2); Serial.println(" mV");
  Serial.print("Solar Cell Load Voltage 2:  "); Serial.print(loadvoltage2); Serial.println(" V");
  Serial.print("Solar Cell Current 2:       "); Serial.print(current_mA2); Serial.println(" mA");
  Serial.println("");

  float shuntvoltage3 = 0;
  float busvoltage3 = 0;
  float current_mA3 = 0;
  float loadvoltage3 = 0;

  busvoltage3 = ina3221.getBusVoltage_V(OUTPUT_CHANNEL);
  shuntvoltage3 = ina3221.getShuntVoltage_mV(OUTPUT_CHANNEL);
  current_mA3 = ina3221.getCurrent_mA(OUTPUT_CHANNEL);
  loadvoltage3 = busvoltage3 + (shuntvoltage3 / 1000);
  
  Serial.print("Output Bus Voltage 3:   "); Serial.print(busvoltage3); Serial.println(" V");
  Serial.print("Output Shunt Voltage 3: "); Serial.print(shuntvoltage3); Serial.println(" mV");
  Serial.print("Output Load Voltage 3:  "); Serial.print(loadvoltage3); Serial.println(" V");
  Serial.print("Output Current 3:       "); Serial.print(current_mA3); Serial.println(" mA");
  Serial.println("");

  delay(2000);
}






// #include <Arduino.h>
// #include <ina3221.h>


// #define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
// #define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */

// const int GPIOPIN = 12; 
// const int delay_Switch_ON=1000*60*10; //sec

// RTC_DATA_ATTR int bootCount = 0;

// /*
// Method to print the reason by which ESP32
// has been awaken from sleep
// */
// void print_wakeup_reason(){
//   esp_sleep_wakeup_cause_t wakeup_reason;

//   wakeup_reason = esp_sleep_get_wakeup_cause();

//   switch(wakeup_reason)
//   {
//     case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
//     case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
//     case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
//     case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
//     case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
//     default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
//   }
// }

// void setup(){
//   Serial.begin(115200);
//   delay(1000); //Take some time to open up the Serial Monitor

//   //Increment boot number and print it every reboot
//   ++bootCount;
//   Serial.println("Boot number: " + String(bootCount));

//   //Print the wakeup reason for ESP32
//   print_wakeup_reason();
//   pinMode(GPIOPIN, OUTPUT);
//   digitalWrite(GPIOPIN, HIGH);
//   delay(delay_Switch_ON);
//   /*
//   First we configure the wake up source
//   We set our ESP32 to wake up every 5 seconds
//   */
//   esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
//   Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
//   " Seconds");

//   /*
//   Next we decide what all peripherals to shut down/keep on
//   By default, ESP32 will automatically power down the peripherals
//   not needed by the wakeup source, but if you want to be a poweruser
//   this is for you. Read in detail at the API docs
//   http://esp-idf.readthedocs.io/en/latest/api-reference/system/deep_sleep.html
//   Left the line commented as an example of how to configure peripherals.
//   The line below turns off all RTC peripherals in deep sleep.
//   */
//   //esp_deep_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
//   //Serial.println("Configured all RTC Peripherals to be powered down in sleep");

//   /*
//   Now that we have setup a wake cause and if needed setup the
//   peripherals state in deep sleep, we can now start going to
//   deep sleep.
//   In the case that no wake up sources were provided but deep
//   sleep was started, it will sleep forever unless hardware
//   reset occurs.
//   */
//   Serial.println("Going to sleep now");
//   delay(1000);
//   Serial.flush(); 
//   esp_deep_sleep_start();
//   //Serial.println("This will never be printed");
// }

// void loop(){
//   //This is not going to be called
// }