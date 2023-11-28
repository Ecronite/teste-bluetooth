#include <BLEDevice.h>
#include <BLEScan.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
BLEScan* pBLEScan;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  Serial.begin(115200);
  BLEDevice::init("ESP32");
  pBLEScan = BLEDevice::getScan();

}

void loop() {
  BLEScanResults foundDevices = pBLEScan->start(15);

  Serial.println("Dispositivos encontrados:");
  for (int i = 0; i < foundDevices.getCount(); i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    Serial.printf("[%d] Endereço: %s\n", i, device.getAddress().toString().c_str());

    // Tenta obter o nome do dispositivo
    if (device.haveName()) {
      Serial.printf("    Nome: %s\n", device.getName().c_str());
      lcd.setCursor(1,0);
      lcd.print(device.getName().c_str());
    }

    // Tenta obter informações adicionais
    if (device.haveServiceData()) {
      Serial.println("    Informações adicionais:");
      for (int i = 0; i < device.getServiceDataCount(); i++) {
        Serial.printf("        UUID: %s, Dados: %s\n", device.getServiceDataUUID(i).toString().c_str(), device.getServiceData(i).c_str());
      }
    }
  }
  lcd.setCursor(1,1);
  int dado = foundDevices.getCount(); // Seu dado do tipo int
  Serial.write((uint8_t*)&dado, sizeof(dado));
  lcd.print(foundDevices.getCount());
  delay(2000);
}