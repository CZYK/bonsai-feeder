/*
  Bonsai.cpp - Library for watering the Bonsai trees code.
  Created by Danko & Rob, December 22, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Bonsai.h"

#define ONESECOND 1000UL
#define ONEMINUTE long (60 * ONESECOND)
#define FIVEMINUTES long (5 * ONEMINUTE)
#define FIFTEENMINUTES long (15 * ONEMINUTE)

int watering_duration_ms = 1500;
int time_to_wait_between_checks = ONEMINUTE;

Bonsai::Bonsai(String name, int pump_pin, int sensor_pin, int desired_moisture)
{
  pinMode(pump_pin, OUTPUT);
  _name = name;
  _pump_pin = pump_pin;
  _sensor_pin = sensor_pin;
  _last_moisture_level = 0;
  _desired_moisture = desired_moisture;
  _next_check_at = 0; // initialize such that a reading is due the first time
}

void Bonsai::check()
{
  long now = millis();

  if (now - _next_check_at <= 0){
    // Serial.println("We are still waiting so do nothing.");
    return;
  }

  int new_moisture_level = measureMoisture();

  // Only continue when the moisture level differs more then 2%
  if(abs(_last_moisture_level - new_moisture_level) < 2){
    // Serial.println("There is not much changed");
    return;
  }

  Serial.print(now / ONEMINUTE);
  Serial.print("\t");
  Serial.print(_name + "\tMoisture level: " + new_moisture_level + "/" + _desired_moisture);
  _last_moisture_level = new_moisture_level;

  if(new_moisture_level < _desired_moisture){

    giveWater();
    // Give the soil some time to soak into the ground
    _next_check_at = millis() + FIVEMINUTES;
    Serial.print("\tGave some water, will pause for 5 minutes so the water can soak into the ground");
  }
  else{

    // Wait `time_to_wait_between_checks` before check again
    _next_check_at = now + time_to_wait_between_checks;
  }

  Serial.println();  
}

void Bonsai::giveWater()
{
    digitalWrite(_pump_pin, HIGH);
    delay(watering_duration_ms);
    digitalWrite(_pump_pin, LOW);
}

int Bonsai::measureMoisture()
{
  int value = analogRead(_sensor_pin);
  value = map(value,1020,310,0,100);    
  return value;
}