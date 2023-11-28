#include <Arduino.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() >= sizeof(int)) {
    int dado;
    Serial.readBytes((char*)&dado, sizeof(dado));
    // implementar o código com a variável dado sendo a quantidade de pessoas.
    Serial.println(dado);
  }
}