#pragma once
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <Arduino.h>
 
// ================================================================
//  TVRemote.h — códigos IR Samsung Crystal + envio
// ================================================================
 
namespace Samsung {
  constexpr uint32_t POWER    = 0xE0E040BF;
  constexpr uint32_t VOL_UP   = 0xE0E0E01F;
  constexpr uint32_t VOL_DOWN = 0xE0E0D02F;
  constexpr uint32_t MUTE     = 0xE0E0F00F;
  constexpr uint32_t CH_UP    = 0xE0E048B7;
  constexpr uint32_t CH_DOWN  = 0xE0E008F7;
  constexpr uint32_t UP       = 0xE0E006F9;
  constexpr uint32_t DOWN     = 0xE0E08679;
  constexpr uint32_t LEFT     = 0xE0E0A659;
  constexpr uint32_t RIGHT    = 0xE0E046B9;
  constexpr uint32_t OK       = 0xE0E016E9;
  constexpr uint32_t BACK     = 0xE0E01DE2;
  constexpr uint32_t HOME     = 0xE0E0D22D;
  constexpr uint32_t NETFLIX  = 0xE0E0F20D;
  constexpr uint32_t PRIME    = 0xE0E042BD;
}
 
class TVRemote {
public:
  TVRemote(uint16_t pino);
 
  void begin();
  bool enviar(const String& comando);
 
private:
  IRsend _irsend;
 
  // repeticoes: quantas vezes o sinal é enviado
  // power/apps usam 1, volume/navegação usam 3
  void _send(const char* nome, uint32_t codigo, uint8_t repeticoes = 1);
};