
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include "DHT.h"

// -------- DHT22 CONFIGURATION --------
#define DHTPIN 15
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// -------- WIFI CONFIGURATION --------
const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

// -------- THINGSPEAK CONFIGURATION --------
const char* WRITE_API_KEY = "#############"; // Replace with your ThingSpeak Write API Key

const char* SERVER_URL = "https://api.thingspeak.com/update";

// Upload interval: 20 seconds
const unsigned long UPLOAD_INTERVAL = 20000;

unsigned long lastUploadTime = 0;

void connectWiFi() {

  Serial.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void uploadToThingSpeak(float temperature, float humidity) {

  WiFiClientSecure client;

  client.setInsecure();

  HTTPClient http;

  Serial.println("Uploading data to ThingSpeak...");

  if (http.begin(client, SERVER_URL)) {

    http.addHeader("Content-Type",
                   "application/x-www-form-urlencoded");

    String postData = "api_key=" + String(WRITE_API_KEY);
    postData += "&field1=" + String(temperature, 2);
    postData += "&field2=" + String(humidity, 2);

    int httpResponseCode = http.POST(postData);

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);

      Serial.print("ThingSpeak Entry ID: ");
      Serial.println(response);

      if (response.toInt() > 0) {
        Serial.println("SUCCESS: Data uploaded!");
      } else {
        Serial.println("Upload not accepted. Check API key and channel.");
      }

    } else {

      Serial.print("Upload Error: ");
      Serial.println(httpResponseCode);

    }

    http.end();

  } else {

    Serial.println("Unable to connect to ThingSpeak!");

  }
}

// -------- SETUP --------
void setup() {

  Serial.begin(115200);

  Serial.println();
  Serial.println("================================");
  Serial.println("    IoT WEATHER STATION");
  Serial.println("================================");

  dht.begin();

  Serial.println("DHT22 Sensor Initialized!");

  connectWiFi();

  Serial.println("System Ready!");
}

// -------- MAIN LOOP --------
void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (millis() - lastUploadTime >= UPLOAD_INTERVAL ||
      lastUploadTime == 0) {

    lastUploadTime = millis();

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {

      Serial.println("ERROR: Sensor reading failed!");

      return;
    }

    Serial.println();
    Serial.println("--------------------------------");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    Serial.println("--------------------------------");

    uploadToThingSpeak(temperature, humidity);
  }

  delay(100);
}
