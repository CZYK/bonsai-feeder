/*
  Bonsai.cpp - Library for watering the Bonsai trees code.
  Created by Danko & Rob, December 22, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Bonsai.h"

#define ONESECOND 1000UL
#define ONEMINUTE ONESECOND * 60UL
#define ONEHOUR ONEMINUTE * 60UL

Bonsai::Bonsai(String name, int pump_pin, int sensor_power_pin, int sensor_pin, int desired_moisture)
{
  _name = name;
  _pump_pin = pump_pin;
  _sensor_power_pin = sensor_power_pin;
  _sensor_pin = sensor_pin;
  _desired_moisture_level = desired_moisture;

  _watering_duration_ms = 1500;
  _interval = ONEMINUTE * 15UL;
  _previousMillis = _interval; // Instantiate in such a way that the check start immediately.

  pinMode(_pump_pin, OUTPUT);
  pinMode(_sensor_pin, OUTPUT);
}

void Bonsai::check()
{
  unsigned long currentMillis = millis();
  
  if (currentMillis - _previousMillis < _interval) {
    // Serial.println("We are still waiting so do nothing.");
    return;
  }

  _previousMillis = currentMillis;
  
  _current_moisture_level = _measureMoisture();
  
  Serial.print(currentMillis / ONEMINUTE);
  Serial.print("\t");
  Serial.print(_name);
  Serial.print("\t");
  Serial.print(_current_moisture_level);
  Serial.print("/");
  Serial.print(_desired_moisture_level);

  if(_amIThirsty()){

    Serial.print("\t");
    Serial.print("Thirsty!");

    _giveWater(_watering_duration_ms);
    
    Serial.print(" (Gave some water)");
  }

  Serial.println();  
}

bool Bonsai::_amIThirsty()
{
  return _current_moisture_level < _desired_moisture_level;
}

void Bonsai::_giveWater(int watering_time)
{
  digitalWrite(_pump_pin, HIGH);
  delay(watering_time);
  digitalWrite(_pump_pin, LOW);
}

int Bonsai::_measureMoisture()
{
  // Only switch on the sensor during measuring to prevent a lot of corrosion.
  digitalWrite(_sensor_power_pin, HIGH);

  // Wat a bit so the sensor can get an accurate reading
  delay(10);

  int value = analogRead(_sensor_pin);

  // Map value to 0-100%
  value = map(value,1000,250,0,100);

  // Shut down the sensor.
  digitalWrite(_sensor_power_pin, LOW);

  return value;
}