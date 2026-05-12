#pragma once
#include <ESPAsyncWebServer.h>
#include "TVRemote.h"

// ================================================================
//  WebInterface.h — servidor HTTP com controle remoto no browser
// ================================================================

class WebInterface {
public:
  WebInterface(TVRemote& remote, uint16_t porta = 80);

  void begin();

private:
  AsyncWebServer _server;
  TVRemote&      _remote;

  void _rotasSetup();
  void _responderOk(AsyncWebServerRequest* req);
  void _responderErro(AsyncWebServerRequest* req, const String& msg);
};
