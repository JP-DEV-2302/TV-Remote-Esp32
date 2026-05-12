#include "WifiManager.h"
#include <Arduino.h>

// ================================================================
//  WifiManager.cpp
// ================================================================

WifiController::WifiController(const char* ssid, const char* pass)
  : _ssid(ssid), _pass(pass) {}

void WifiController::conectar() {
  Serial.printf("\n[WiFi] Conectando a '%s'", _ssid);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(_ssid, _pass);

  uint8_t tentativas = 0;
  while (WiFi.status() != WL_CONNECTED && tentativas < 24) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\n[WiFi] Conectado! IP: %s\n", WiFi.localIP().toString().c_str());
  } else {
    Serial.println("\n[WiFi] Falha — tentará novamente em 15s.");
  }
}

void WifiController::verificarReconexao() {
  if (WiFi.status() == WL_CONNECTED) return;

  unsigned long agora = millis();
  if (agora - _ultimaTentativa < INTERVALO_MS) return;

  _ultimaTentativa = agora;
  Serial.println("[WiFi] Conexão perdida. Reconectando...");
  WiFi.disconnect();
  WiFi.begin(_ssid, _pass);
}

bool WifiController::estaConectado() {
  return WiFi.status() == WL_CONNECTED;
}

String WifiController::ipLocal() {
  return WiFi.localIP().toString();
}
