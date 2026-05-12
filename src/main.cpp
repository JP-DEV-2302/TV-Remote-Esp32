#include <Arduino.h>
#include "secrets.h"
#include "WifiManager.h"
#include "TVRemote.h"
#include "WebInterface.h"
#include <LED.h>

// ================================================================
//  main.cpp — ponto de entrada PlatformIO
// ================================================================

const uint16_t IR_PIN = 45; // ajuste se necessário

WifiController wifi(WIFI_SSID, WIFI_PASS);
TVRemote       tv(IR_PIN);
WebInterface   web(tv);

// ================================================================
void setup() {
  Serial.begin(115200);
  delay(200);

  Serial.println("\n=============================");
  Serial.println("   Samsung TV Remote — ESP32  ");
  Serial.println("=============================\n");

  tv.begin();
  wifi.conectar();

  if (wifi.estaConectado()) {
    web.begin();
    Serial.printf("\n✅ Acesse no celular: http://%s\n\n", wifi.ipLocal().c_str());
  } else {
    Serial.println("⚠️  Sem WiFi — servidor web não iniciado.");
  }
}

// ================================================================
void loop() {
  wifi.verificarReconexao();

  // Se o WiFi caiu no boot e voltou depois, reinicia para subir o servidor
  static bool servidorIniciado = wifi.estaConectado();
  if (!servidorIniciado && wifi.estaConectado()) {
    Serial.println("[Sistema] WiFi recuperado — reiniciando...");
    delay(1000);
    ESP.restart();
  }

  delay(500);
}
