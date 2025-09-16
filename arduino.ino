#include <WiFi.h>
#include <WebServer.h>
#include <BluetoothSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ================== WiFi Config ==================
const char* ssid     = "ESP32_Soil";      // WiFi SSID (ESP32 Access Point)
const char* password = "12345678";        // WiFi password

WebServer server(80);
BluetoothSerial SerialBT;

// ================= Sensor Pins =================
#define SOIL_MOISTURE_PIN 34
#define ONE_WIRE_BUS 32
#define PH_SENSOR_PIN     35
#define EC_SENSOR_PIN     33

// ================ pH Calibration =================
float calibration_value = 17.42; // pH calibration constant

// ================ Setup DS18B20 =================
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Global sensor values
float soilMoisture, temperature, phValue, ecValue;

// =================================================
void readSensors() {
  // ----------- Soil Moisture -----------
  int soilRaw = analogRead(SOIL_MOISTURE_PIN);
  soilMoisture = map(soilRaw, 0, 4095, 0, 100);

  // ----------- Temperature (DS18B20) -----------
  sensors.requestTemperatures(); 
  temperature = sensors.getTempCByIndex(0);

  // ----------- pH Sensor -----------
  int phRaw = analogRead(PH_SENSOR_PIN);
  float voltagePH = (phRaw * 3.3) / 4095.0;
  phValue = -5.70 * voltagePH + calibration_value;

  // ----------- EC Sensor (approximate) -----------
  int ecRaw = analogRead(EC_SENSOR_PIN);
  ecValue = (ecRaw / 4095.0) * 10.0;
}

// =================================================
String generateHTML() {
  String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='2'>";
  html += "<title>ESP32 Smart Soil Analyzer</title></head><body>";
  html += "<h1>Smart Soil Analyzer</h1>";
  html += "<p><b>Soil Moisture:</b> " + String(soilMoisture) + " %</p>";
  html += "<p><b>Temperature :</b> " + String(temperature) + " °C</p>";
  html += "<p><b>pH Value    :</b> " + String(phValue) + "</p>";
  html += "<p><b>EC Value    :</b> " + String(ecValue) + " mS/cm</p>";
  html += "<hr><p>Page auto-refreshes every 2 seconds.</p>";
  html += "</body></html>";
  return html;
}

// =================================================
void handleRoot() {
  readSensors();
  server.send(200, "text/html", generateHTML());
}

// =================================================
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Soil_BT");  // Bluetooth device name

  pinMode(SOIL_MOISTURE_PIN, INPUT);
  pinMode(PH_SENSOR_PIN, INPUT);
  pinMode(EC_SENSOR_PIN, INPUT);

  sensors.begin();

  // Start WiFi AP
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP Started. Connect to: " + String(ssid));
  Serial.println("Open http://192.168.4.1 in browser");

  // WebServer
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  // Read sensors
  readSensors();

  // Print to Serial Monitor
  Serial.print("Soil Moisture: "); Serial.print(soilMoisture); Serial.println("%");
  Serial.print("Temperature : "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("pH Value    : "); Serial.println(phValue);
  Serial.print("EC Value    : "); Serial.print(ecValue); Serial.println(" mS/cm");
  Serial.println("--------------------------");

  // Send over Bluetooth
  SerialBT.print("Soil Moisture: "); SerialBT.print(soilMoisture); SerialBT.println("%");
  SerialBT.print("Temperature : "); SerialBT.print(temperature); SerialBT.println(" °C");
  SerialBT.print("pH Value    : "); SerialBT.println(phValue);
  SerialBT.print("EC Value    : "); SerialBT.print(ecValue); SerialBT.println(" mS/cm");
  SerialBT.println("--------------------------");

  delay(2000);
}
