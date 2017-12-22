#include <Bonsai.h>

int sample_time = 10;
int sample_time_ms = sample_time * 1000;

Bonsai danko("Danko",12, A0, 60);
Bonsai rob("Rob",8, A1, 60);

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
