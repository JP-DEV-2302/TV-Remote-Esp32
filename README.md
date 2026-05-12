TV Remote — ESP32 📺⚡

Control your TV using an ESP32 through a responsive web interface accessible from your smartphone.
The project uses IR (infrared) transmission and an embedded web server running on the ESP32.

🚀 Features
Browser-based remote control
Modern and responsive interface
Control for:
Power
Volume
Channels
Navigation
Smart Hub
Netflix
Prime Video
Automatic Wi-Fi reconnection
Visual feedback for commands
Compatible with IR-enabled TVs
🛠️ Technologies Used
ESP32-S3
PlatformIO
Arduino Framework
ESPAsyncWebServer
IRremoteESP8266
AsyncTCP
📦 Libraries
lib_deps =
    crankyoldgit/IRremoteESP8266
    https://github.com/mathieucarbou/AsyncTCP.git
    https://github.com/mathieucarbou/ESPAsyncWebServer.git
    https://github.com/JP-DEV-2302/Biblioteca-LED.git
🔐 Wi-Fi Configuration

Create a secrets.cpp file:

#include "secrets.h"

const char* WIFI_SSID = "YOUR_WIFI";
const char* WIFI_PASS = "YOUR_PASSWORD";
🔌 Hardware Used
ESP32-S3 DevKit
Infrared IR LED
220Ω resistor
USB power supply
🌐 How to Use

Clone the project:

git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git

Then:

Open the project in PlatformIO
Configure your Wi-Fi credentials
Compile and upload to the ESP32
Open the Serial Monitor
Access the displayed IP address:
http://192.168.x.x
📱 Interface

The interface includes:

Modern design
Mobile compatibility
Visual feedback
Vibration when pressing buttons
Smooth animations
🔒 Security

The secrets.cpp file should remain in .gitignore to prevent Wi-Fi password leaks.

🧠 Future Improvements
Voice control
Alexa/Google Assistant integration
Support for additional TV brands
Installable PWA
MQTT/Home Assistant integration
👨‍💻 Author
Developed by João Pedro
