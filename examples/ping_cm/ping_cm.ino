
#include <SGBotic_I2CPing.h>


SGBotic_I2CPing sonar;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("distance : ");
  Serial.println(sonar.ping_cm());
}
