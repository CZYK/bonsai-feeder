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
Bonsai danko("Danko", 12, 8, A0, 20, 10000);

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

## Ingredients:
- [Arduino UNO](https://www.tinytronics.nl/shop/nl/arduino/main-boards/arduino-uno-r3?search=arduino%20uno) (€ 23)
- [Moist sensor](https://www.tinytronics.nl/shop/nl/sensoren/temperatuur-lucht-vochtigheid/bodemvocht-sensor-module) (€ 3)
- [Relais](https://www.tinytronics.nl/shop/nl/diversen/relais/5v-relais-1-channel-hoog-actief) (€ 2,50)
- [Water pump](https://www.tinytronics.nl/shop/nl/robotica/motoren/motor/onderwaterpomp-verticaal-3-6v) (€ 4)
- [Water hose](https://www.tinytronics.nl/shop/nl/robotica/toebehoren/waterslang-voor-onderwaterpomp-verticaal-horizontaal-3-6v-transparant-1-meter?search=water)
- [One-way-valve](https://www.vijvertopper.nl/product/8249/pp-terugslagklep-6mm.html) (€ 3,15)
- [PP T-stuk 6,4mm](https://www.vijvertopper.nl/product/8303/pp-t-stuk-6-4mm.html) (€ 1,70)
