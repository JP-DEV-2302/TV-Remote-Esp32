#include "TVRemote.h"
 
// ================================================================
//  TVRemote.cpp
//
//  Repetições por tipo de comando:
//    1x → power, apps, home, back  (um disparo limpo)
//    3x → volume, canal, navegação (garante que a TV registre)
//
//  Delay de 40ms entre repetições é o intervalo padrão do protocolo
//  NEC — igual ao que o controle original faz ao segurar o botão.
// ================================================================
 
TVRemote::TVRemote(uint16_t pino) : _irsend(pino) {}
 
void TVRemote::begin() {
  _irsend.begin();
  Serial.println("[IR] Transmissor iniciado.");
}
 
void TVRemote::_send(const char* nome, uint32_t codigo, uint8_t repeticoes) {
  Serial.printf("[IR] → %s (0x%08X) x%d\n", nome, codigo, repeticoes);
  for (uint8_t i = 0; i < repeticoes; i++) {
    _irsend.sendNEC(codigo, 32);
    if (i < repeticoes - 1) delay(40);
  }
}
 
bool TVRemote::enviar(const String& cmd) {
  // --- 1 repetição: disparo único ---
  if      (cmd == "power")    { _send("POWER",    Samsung::POWER,    3); }
  else if (cmd == "mute")     { _send("MUTE",     Samsung::MUTE,     1); }
  else if (cmd == "ok")       { _send("OK",       Samsung::OK,       1); }
  else if (cmd == "back")     { _send("BACK",     Samsung::BACK,     1); }
  else if (cmd == "home")     { _send("HOME",     Samsung::HOME,     1); }
  else if (cmd == "netflix")  { _send("NETFLIX",  Samsung::NETFLIX,  1); }
  else if (cmd == "prime")    { _send("PRIME",    Samsung::PRIME,    1); }
 
  // --- 3 repetições: garante registro na TV ---
  else if (cmd == "vol_up")   { _send("VOL+",     Samsung::VOL_UP,   3); }
  else if (cmd == "vol_down") { _send("VOL-",     Samsung::VOL_DOWN, 3); }
  else if (cmd == "ch_up")    { _send("CH+",      Samsung::CH_UP,    3); }
  else if (cmd == "ch_down")  { _send("CH-",      Samsung::CH_DOWN,  3); }
  else if (cmd == "up")       { _send("UP",       Samsung::UP,       1); }
  else if (cmd == "down")     { _send("DOWN",     Samsung::DOWN,     1); }
  else if (cmd == "left")     { _send("LEFT",     Samsung::LEFT,     1); }
  else if (cmd == "right")    { _send("RIGHT",    Samsung::RIGHT,    1); }
 
  else {
    Serial.printf("[IR] Comando desconhecido: %s\n", cmd.c_str());
    return false;
  }
  return true;
}