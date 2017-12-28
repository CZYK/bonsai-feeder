# bonsai-feeder
System to automatically water our bonsais


## How to install?

First you will need to add this library into your Arduino Library folder.
```sh
git clone git@github.com:CZYK/bonsai-feeder.git ~/Documents/Arduino/libraries/Bonsai
```
Now you can write your own module which uses this library. You can find an example below.

````Arduino
#include <Bonsai.h>

// Danko tree
// This tree's sensor measures 40% when the bottom touches the water.
Bonsai danko("Danko", 12, 8, A0, 40);

// Rob's tree
// This tree's sensor measures 25% when the bottom touches the water.
Bonsai rob("Rob", 4, 2, A1, 25);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting bonsai feeder...\n");
  Serial.println("Seconds\tName\tMoisture");
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