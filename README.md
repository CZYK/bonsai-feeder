# bonsai-feeder
System to automatically water our bonsais


## How to install?

First you will need to add this library into your Arduino Library folder.
```sh
git clone git@github.com:CZYK/bonsai-feeder.git ~/Documents/Arduino/libraries/Bonsai
```
Now you can write your own module which uses this library. You can find an example below.

````Arduino
# Bonsai.ino
#include <Bonsai.h>

Bonsai danko("Danko",12, A0, 50);
Bonsai rob("Rob",8, A1, 50);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting bonsai feeder...\n");
  Serial.println("Minutes\tName\tMoisture");
}

void loop()
{
  danko.check();
  rob.check();
  delay(100);
}
```