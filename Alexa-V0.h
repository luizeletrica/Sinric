/** CÓDIGO SINRIC PRO CONTROLE ESP32

BY Gustavo Nery
BY EDITON Luiz Filipe

Necessário as bibliotecas:
*SinricPro 
*ArduinoJson by Benoit Blanchon (minimum Version 6.12.0)
*WebSockets by Markus Sattler (minimum Version 2.1.4)


**/

#include "SinricPro.h"
#include "SinricProSwitch.h"

 #include <WiFi.h> 

 
#define WIFI_SSID         "my_Router"    //Nome da Rede
#define WIFI_PASS         "Pin"     //Senha da Rede
#define APP_KEY           "my_key"      // O seu App Key é algo como "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "App"   // O seu App Secret é algo como "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
 

#define Lampada_ID       "Lamp_ID"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Lampada_Pin 25  // O pino fisico onde está ligado

#define Exaust_ID       "Exaust_ID"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Exaust_Pin 26  // O pino fisico onde está ligado
#define Vent_ID       "Vent_ID"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Vent_Pin 27  // O pino fisico onde está ligado
 
#define BAUD_RATE         9600                // Se precisar, pode trocar o baud rate
 
 
void setupWiFi();
void setupSinricPro();

bool LampadaState(const String &deviceId, bool &state);
bool ExaustState(const String &deviceId, bool &state);
bool VentState(const String &deviceId, bool &state);

 
 
// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro(); 
  pinMode(Lampada_Pin, OUTPUT);
  digitalWrite(Lampada_Pin, HIGH);

pinMode(Vent_Pin, OUTPUT);
  digitalWrite(Vent_Pin, HIGH);

  pinMode(Exaust_Pin, OUTPUT);
  digitalWrite(Exaust_Pin, HIGH);

}
 
void loop() {
  SinricPro.handle();
}
 
 

 
bool LampadaState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Lampada_Pin, !state);
  return true; // request handled properly
}
 
bool ExaustState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Exaust_Pin, !state);
  return true; // request handled properly
}

bool VentState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Vent_Pin, !state);
  return true; // request handled properly
}
 
// setup das conexões Wifi
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
 
  Serial.printf("Conectado!\r\n[WiFi]: Endereço de IP e %s\r\n", WiFi.localIP().toString().c_str());
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro
  SinricProSwitch &mySwitch1 = SinricPro[Lampada_ID];
  mySwitch1.onPowerState(LampadaState);

   SinricProSwitch &mySwitch2 = SinricPro[Vent_ID];
  mySwitch2.onPowerState(VentState);
 
  SinricProSwitch &mySwitch3 = SinricPro[Exaust_ID];
  mySwitch3.onPowerState(ExaustState);
   
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Conectado a nuvem SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}