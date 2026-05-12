#pragma once
#include <WiFi.h>

// ================================================================
//  WifiManager.h
// ================================================================

class WifiController {
public:
  WifiController(const char* ssid, const char* pass);

  void   conectar();
  void   verificarReconexao();
  bool   estaConectado();
  String ipLocal();

private:
  const char*   _ssid;
  const char*   _pass;
  unsigned long _ultimaTentativa = 0;

  static const unsigned long INTERVALO_MS = 15000UL;
};
