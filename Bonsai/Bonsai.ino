#include <Bonsai.h>

int sample_time = 10;
int sample_time_ms = sample_time * 1000;

<<<<<<< HEAD
Bonsai danko(1,"Danko",12, A0, 60);
Bonsai rob(2,"Rob",8, A1, 60);
=======
Bonsai danko("Danko",12, A0, 45);
Bonsai rob("Rob",8, A1, 40);
>>>>>>> aa0ae03ff50e124b9c097e9af046dc20abac7e04

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
