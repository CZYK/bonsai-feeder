/*
  Bonsai.h - Library for watering the Bonsai trees code.
  Created by Danko & Rob, December 22, 2017.
  Released into the public domain.
*/

#ifndef Bonsai_h
#define Bonsai_h

#include "Arduino.h"

class Bonsai
{
  public:
    Bonsai(String name, int pump_pin, int sensor_power_pin, int sensor_pin, int desired_moisture);
    void check();
	void giveWater();
    int measureMoisture();
  private:
    String _name;
    int _pump_pin;
    int _sensor_power_pin;
    int _sensor_pin;
    int _last_moisture_level;
    int _desired_moisture;
    long _next_check_at;
};

#endif