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
  private:
	  void _giveWater(int watering_time);
    int _measureMoisture();
<<<<<<< HEAD
=======
    bool _amIThirsty();
>>>>>>> acf2512f1fbe0658681d55ee21d6a26f327229e4
    String _name;
    int _pump_pin;
    int _sensor_power_pin;
    int _sensor_pin;

    int _desired_moisture_level;
    int _current_moisture_level;
    int _watering_duration_ms;

    long _interval;
    unsigned long _previousMillis;
<<<<<<< HEAD
    bool _first_run;
=======
>>>>>>> acf2512f1fbe0658681d55ee21d6a26f327229e4
};

#endif