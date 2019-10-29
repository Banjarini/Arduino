
#include <Servo.h>

Servo servo1;

void setup()
{
  servo1.attach(9);
    servo1.write(90);
  delay(5000);
  servo1.write(115);
  delay(200);
    servo1.write(80);
  delay(650);

}

void loop()
{
  servo1.write(115);  //1
  delay(200);
    servo1.write(80);
  delay(600);

}
