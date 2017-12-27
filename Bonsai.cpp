/*
  Bonsai.cpp - Library for watering the Bonsai trees code.
  Created by Danko & Rob, December 22, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Bonsai.h"

#define ONESECOND 1000UL
#define FIVESECONDS long (5 * ONESECOND)
#define ONEMINUTE long (60 * ONESECOND)
#define FIVEMINUTES long (5 * ONEMINUTE)
#define FIFTEENMINUTES long (15 * ONEMINUTE)

long watering_duration_ms = 1200;

long check_invertval = FIVESECONDS; // Default to FIFTEENMINUTES
long water_soak_wait_time = FIVEMINUTES; // Default to FIVEMINUTES

Bonsai::Bonsai(String name, int pump_pin, int sensor_power_pin, int sensor_pin, int desired_moisture)
{
  pinMode(pump_pin, OUTPUT);
  pinMode(sensor_power_pin, OUTPUT);
  _name = name;
  _pump_pin = pump_pin;
  _sensor_power_pin = sensor_power_pin;
  _sensor_pin = sensor_pin;
  _last_moisture_level = 0;
  _desired_moisture = desired_moisture;
  _next_check_at = 0; // initialize such that a reading is due the first time
  _pump_wait_until = 0;
}

void Bonsai::check()
{
  long now = millis();
  long ms_to_wait = _next_check_at - now;
  
  if (ms_to_wait > 0){
    // Serial.println("We are still waiting so do nothing.");
    return;
  }
  
  // Wait before check again
  _next_check_at = now + check_invertval;

  int new_moisture_level = measureMoisture();

  // Only continue when the moisture level differs more then 2%
  if(abs(_last_moisture_level - new_moisture_level) < 2){
    // Serial.println("There is not much changed");
    return;
  }

  Serial.print(now / ONESECOND);
  Serial.print("\t");
  Serial.print(_name);
  Serial.print("\t");
  Serial.print(new_moisture_level);
  Serial.print("/");
  Serial.print(_desired_moisture);

  _last_moisture_level = new_moisture_level;

  if(new_moisture_level < _desired_moisture){

    giveWater();
  }

  Serial.println();  
}

void Bonsai::giveWater()
{
  long now = millis();
  long ms_to_wait = _pump_wait_until - now;
  
  if (ms_to_wait > 0){
    Serial.print("\t");
    Serial.print("Wait ");
    Serial.print(ms_to_wait / ONESECOND);
    Serial.print(" seconds so the water can soak into the ground...");
    return;
  }

  // Give the soil some time to soak into the ground
  _pump_wait_until = now + water_soak_wait_time;  
  Serial.print("\t");
  Serial.print("Thursty!");

  // digitalWrite(_pump_pin, HIGH);
  delay(watering_duration_ms);
  digitalWrite(_pump_pin, LOW);
  
  Serial.print(" (Gave some water)");
}

int Bonsai::measureMoisture()
{
  // Only switch on the sensor during measuring to prevent a lot of corrosion.
  digitalWrite(_sensor_power_pin, HIGH);

  // Wat a bit so the sensor can get an accurate reading
  delay(50);

  int value = analogRead(_sensor_pin);
  // Serial.print("\nValue sensor " + _name + ": ");  
  // Serial.print(value);
  // Serial.print("\n");

  // Map value to 0-100%
  value = map(value,1000,0,0,100);

  // Shut down the sensor.
  digitalWrite(_sensor_power_pin, LOW);

  return value;
}