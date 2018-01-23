# bonsai-feeder
System to automatically water our bonsais

![Setup bonsai water feeder](/assets/assembly.jpg)

## How to install?

First you will need to add this library into your Arduino Library folder.
```sh
git clone git@github.com:CZYK/bonsai-feeder.git ~/Documents/Arduino/libraries/Bonsai
```
Now you can write your own module which uses this library. You can find an example below.

```Arduino
#include <Bonsai.h>

// Danko tree
// This tree's sensor measures 40% when the bottom touches the water.
Bonsai danko("Danko", 12, 8, A0, 20, 6000);

// Rob's tree
// This tree's sensor measures 25% when the bottom touches the water.
Bonsai rob("Rob", 4, 2, A1, 25, 4000);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting bonsai feeder...\n");
  Serial.println("Runs\tName\tMoisture");
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  danko.check();
  delay(250);
  rob.check();
  digitalWrite(13, LOW);
  
  delay(250);
}
```

These are the analogue output values of the new sensors. An average of 250-1000 has been mapped to 0-100%. It would be nice to calibrate this per sensor but the code (at the moment) does not allow that. That is also the reason why Danko's tree is set to 40% while Rob's is set to 25%. Both equal the same level of moist (the bottom of the sensor in the water).

| Reading | Danko | Rob | Comment |
| :--------- | -------: | ----: | :--- |
| Open Air  | 1000  | 1002 | Sensor in dry air |
| Feet wet  | 770 | 850 | Bottom of sensor touching the water, not so accurate |
| Completely wet  | 296 | 250 | Sensor completely soaked in a cup of water |
