TV Remote — ESP32 📺⚡

Controle sua TV  utilizando um ESP32 via interface web responsiva acessível pelo celular.
O projeto utiliza emissão IR (infravermelho) e servidor web embarcado no ESP32.

🚀 Funcionalidades
Controle remoto via navegador
Interface moderna e responsiva
Controle de:
Power
Volume
Canais
Navegação
Smart Hub
Netflix
Prime Video
Reconexão automática ao Wi-Fi
Feedback visual dos comandos
Compatível com TVs  via IR
🛠️ Tecnologias Utilizadas
ESP32-S3
PlatformIO
Arduino Framework
ESPAsyncWebServer
IRremoteESP8266
AsyncTCP
📦 Bibliotecas
lib_deps =
    crankyoldgit/IRremoteESP8266
    https://github.com/mathieucarbou/AsyncTCP.git
    https://github.com/mathieucarbou/ESPAsyncWebServer.git
   https://github.com/JP-DEV-2302/Biblioteca-LED.git


Crie um arquivo secrets.cpp:

#include "secrets.h"

const char* WIFI_SSID = "SEU_WIFI";
const char* WIFI_PASS = "SUA_SENHA";
🔌 Hardware Utilizado
ESP32-S3 DevKit
LED infravermelho IR
Resistor 220Ω
Fonte USB
🌐 Como Usar
Clone o projeto:
git clone https://github.com/SEU-USUARIO/SEU-REPOSITORIO.git
Abra no PlatformIO
Configure o Wi-Fi
Compile e envie para o ESP32
Abra o Monitor Serial
Acesse o IP mostrado:
http://192.168.x.x
📱 Interface

A interface possui:

Design moderno
Compatibilidade mobile
Feedback visual
Vibração ao clicar nos botões
Animações suaves


O arquivo secrets.cpp deve permanecer no .gitignore para evitar vazamento da senha Wi-Fi.

🧠 Futuras Melhorias
Controle por voz
Integração com Alexa/Google Assistant
Suporte para outras TVs
PWA instalável
MQTT/Home Assistant
👨‍💻 Autor

Desenvolvido por João Pedro 🚀
