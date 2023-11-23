#include "IPv6Address.h"
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiSTA.h>
#include <WiFi.h>

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <BLEDevice.h>
#include <BLEScan.h>

#include "EscreveSQL.h"


BLEScan* pBLEScan;

const char *ssid = "";
const char *passwordWiFi = "";

IPAddress host(192,168,0,223);
const int port = 3306;  
char *user = "root";
char *password = "root";
char *db = "teste";

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() 
{
  Serial.begin(115200);
  //bluetooth
    BLEDevice::init("ESP32");
    pBLEScan = BLEDevice::getScan();
  
  //wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, passwordWiFi);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  //mysql
  Serial.println("Conectando ao servidor MySQL...");
  while (!conn.connect(host, port, user, password, db)) 
  {
    Serial.println("Falha ao conectar ao servidor MySQL");
    delay(500);
    Serial.println("Tentando conectar-se novamente ao servidor MySQL");
    delay(1000);
  }
    Serial.println("Conectado ao servidor MySQL");
}

void loop() 
{
  BLEScanResults foundDevices = pBLEScan->start(15);

  EscreveSQL m(&conn);

  Serial.println("Dispositivos encontrados:");
  for (int i = 0; i < foundDevices.getCount(); i++) 
  {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    Serial.printf("[%d] Endereço: %s\n", i, device.getAddress().toString().c_str());
  }
  
   char cas[100];
   sprintf(cas, "Quant_pessoas = %d", foundDevices.getCount() );
   char sac[] = "ID = 1";
   m.atualizar(cas, sac);
  // Aguardar por um curto período antes de verificar novamente
  delay(10000);
}
