/*
  Bonsai.cpp - Library for watering the Bonsai trees code.
  Created by Danko & Rob, December 22, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Bonsai.h"
#include <EEPROM.h>
#include <Time.h>

int watering_duration_ms = 2000;
int watering_absorption_wait_samples = 6;

int eeprom_address = 0;

struct WateringMoment {
  byte userId;
  uint32_t timestamp;
};

Bonsai::Bonsai(byte userId, String name, int pump_pin, int sensor_pin, int desired_moisture)
{
  pinMode(pump_pin, OUTPUT);
  _userId = userId;
  _name = name;
  _pump_pin = pump_pin;
  _sensor_pin = sensor_pin;
  _desired_moisture = desired_moisture;
  _watering_ago = 1000; // Dirty hack so it starts the first time immediately
}

void Bonsai::check()
{

  if(measureMoisture() < _desired_moisture){

    giveWater();
  }
}

void Bonsai::giveWater()
{
  if(_watering_ago < watering_absorption_wait_samples){

	_watering_ago++;
	return;
  }

	Serial.println();
	Serial.println("Watering " + _name + "'s plant, will wait " + watering_absorption_wait_samples + " sample to let water absorb into the soil");

	storeWateringMoment();

	digitalWrite(_pump_pin, HIGH);
	delay(watering_duration_ms);
	digitalWrite(_pump_pin, LOW);

	_watering_ago = 0;
}

int Bonsai::measureMoisture()
{
  int value = analogRead(_sensor_pin);
  value = map(value,1020,310,0,100);

  Serial.print(_name + "'s moisture level is ");
  Serial.print(value);
  return value;
}

void Bonsai::storeWateringMoment()
{
  uint32_t timeStamp = now();

  WateringMoment moment = {
    _userId
    timeStamp
  };

  EEPROM.put(eeprom_address, moment);

  Serial.println("Stored " + _name + "'s watering moment into memory");

  eeprom_address++;
  if (eeprom_address == EEPROM.length()) {
    eeprom_address = 0;
  }
}
