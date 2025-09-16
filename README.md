# 🌱 ESP32 Smart Soil Analyzer

An IoT-based **Smart Soil Analyzer** using ESP32.  
It reads multiple soil parameters and displays them via **Bluetooth** and a built-in **Web Server** (auto-refreshing webpage).  

---

## 📌 Features
- 🌡️ **Temperature** measurement (DS18B20 sensor)  
- 💧 **Soil Moisture** measurement (analog sensor)  
- ⚡ **Electrical Conductivity (EC)** (approximate)  
- 🧪 **pH level** monitoring  
- 📶 **WiFi Access Point** mode with built-in web server  
- 🔄 Web page auto-refreshes every 2 seconds  
- 📲 **Bluetooth Serial** output for mobile/PC apps  

---

## 🛠️ Hardware Required
- **ESP32 Dev Board** (WROOM or WROVER recommended)  
- **DS18B20 Temperature Sensor**  
- **Soil Moisture Sensor** (analog)  
- **pH Sensor** (analog)  
- **EC Sensor** (analog)  
- Jumper wires & breadboard  

---

## 🔌 Wiring
| Sensor         | ESP32 Pin |
|----------------|-----------|
| Soil Moisture  | GPIO 34   |
| DS18B20 Data   | GPIO 32   |
| pH Sensor      | GPIO 35   |
| EC Sensor      | GPIO 33   |

---

## 📦 Required Libraries
Install these from Arduino IDE Library Manager:

- [OneWire](https://github.com/PaulStoffregen/OneWire)  
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)  

Already included with **ESP32 Arduino Core**:
- `WiFi.h`  
- `WebServer.h`  
- `BluetoothSerial.h`  

---

## ⚙️ Arduino IDE Setup
1. Install [ESP32 Arduino Core](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).  
2. Go to **Tools → Board** → Select **ESP32 Dev Module**.  
3. Go to **Tools → Partition Scheme** → Select **Huge APP (3MB No OTA/1MB SPIFFS)**.  
4. Upload the code.  

---

## 🌐 Usage
- **WiFi AP Mode**  
  - Connect to WiFi SSID: `ESP32_Soil`  
  - Password: `12345678`  
  - Open browser: [http://192.168.4.1](http://192.168.4.1)  
  - Sensor data auto-refreshes every 2s  

- **Bluetooth Serial**  
  - Pair device `ESP32_Soil_BT`  
  - Open any Bluetooth Serial terminal app  
  - Live sensor data displayed  

---

## 📸 Demo (optional)
*(Add screenshots of web interface and serial output here)*

---

## 📜 License
MIT License – feel free to use, modify, and share.  

---
