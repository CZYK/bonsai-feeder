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

int sample_time = 10;
int sample_time_ms = sample_time * 1000;

Bonsai danko("Danko",12, A0, 45);
Bonsai rob("Rob",8, A1, 40);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  danko.check();
  Serial.print("  /  ");
  rob.check();
  Serial.println();
  delay(sample_time_ms);
}

```
