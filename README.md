# IoT-Based Weather Station Using ESP32 and Cloud Dashboard

An IoT-based weather monitoring project that measures temperature and relative humidity using an ESP32 and DHT22 sensor. Sensor readings are uploaded to ThingSpeak over Wi-Fi, visualized on a cloud dashboard, and used for email alerts when configured thresholds are exceeded.

> **Note:** This project was developed and tested using the Wokwi ESP32 simulator. Physical hardware testing is not claimed.

## Features

- Measures temperature (°C) and relative humidity (%).
- Connects ESP32 to Wi-Fi.
- Uploads sensor readings to ThingSpeak every 20 seconds.
- Displays temperature and humidity graphs.
- Uses MATLAB Analysis and ThingSpeak Alerts API for email notifications.
- Demonstrated alert thresholds:
  - Temperature greater than 35°C.
  - Humidity greater than 70%.

## System Architecture

1. DHT22 measures temperature and humidity.
2. ESP32 reads the sensor data.
3. ESP32 connects to Wi-Fi and uploads readings to ThingSpeak.
4. ThingSpeak stores and visualizes the readings.
5. MATLAB Analysis checks configured thresholds and uses the ThingSpeak Alerts API to send email notifications.

## Components

| Component | Purpose |
|---|---|
| ESP32 DevKit V1 | Microcontroller and Wi-Fi communication |
| DHT22 | Temperature and humidity measurement |
| Wokwi | ESP32 simulation platform |
| ThingSpeak | Cloud storage and dashboard |

## Circuit Connections

| DHT22 Pin | ESP32 Pin |
|---|---|
| VCC | 3V3 |
| DATA | GPIO 15 |
| NC | Not connected |
| GND | GND |

## Technologies Used

- Arduino C++
- ESP32
- DHT22
- Wokwi
- ThingSpeak IoT Cloud
- MATLAB Analysis
- ThingSpeak Alerts API

### Required Libraries

- Adafruit DHT Sensor Library
- Adafruit Unified Sensor

ESP32 libraries used:
- WiFi.h
- WiFiClientSecure.h
- HTTPClient.h

## ThingSpeak Configuration

Create a ThingSpeak channel with these fields:

| Field | Description |
|---|---|
| Field 1 | Temperature |
| Field 2 | Humidity |

**Channel ID:** 3559677

[Open ThingSpeak Channel](https://thingspeak.com/channels/3559677)

## How to Run

1. Open `IOT_BASED_WEATHER_STATION.ino` in Arduino IDE or use it in Wokwi.
2. Select ESP32 DevKit V1.
3. Connect the DHT22 sensor according to the connection table.
4. Install the required Adafruit libraries.
5. Configure your Wi-Fi credentials and ThingSpeak Write API key.
6. For Wokwi, use `Wokwi-GUEST` as the Wi-Fi SSID and an empty password.
7. Run the simulation.
8. Open Serial Monitor at 115200 baud.
9. Verify sensor readings and ThingSpeak uploads.
10. Configure MATLAB Analysis and ThingSpeak Alerts API separately to reproduce email notifications.

## Email Alert Configuration

The demonstrated alert conditions are:

- Temperature > 35°C
- Humidity > 70%

MATLAB Analysis checks the configured conditions and sends alert requests through the ThingSpeak Alerts API.

**Note:** Email alerts are handled by the cloud-side MATLAB and Alerts API workflow, not directly by the ESP32 firmware.

## ThingSpeak MATLAB Analysis

The project includes MATLAB scripts for sending email notifications through the ThingSpeak Alerts API.

### MATLAB Alert Scripts

| File | Description | Alert Threshold |
|---|---|---|
| `temperature_alert.m` | Sends a high-temperature email notification | Temperature > 35°C |
| `humidity_alert.m` | Sends a high-humidity email notification | Humidity > 70% |

### Alert Workflow

1. ESP32 uploads temperature and humidity readings to ThingSpeak.
2. ThingSpeak React triggers the configured cloud-side analysis when the relevant conditions are met.
3. MATLAB scripts send email notification requests through the ThingSpeak Alerts API.
4. The user receives an email notification when an alert is triggered.

### Configuration

- ThingSpeak Alerts API endpoint: `https://api.thingspeak.com/alerts/send`
- Configure your own Alerts API key in the MATLAB scripts.
- Replace the placeholder `YOUR_ALERTS_API_KEY` with your private key locally.
- Never upload actual API keys to GitHub.

### Source Files

- `thingspeak/matlab_analysis/temperature_alert.m`
- `thingspeak/matlab_analysis/humidity_alert.m`

**Note:** The MATLAB scripts send notifications when executed. Threshold detection and triggering are configured separately in the ThingSpeak workflow.

## Repository Structure

```text
IoT-Based-Weather-Station/
├── README.md
├── .gitignore
├── IOT_BASED_WEATHER_STATION.ino
├── thingspeak/
│   └── matlab_analysis/
│       ├── temperature_alert.m
│       └── humidity_alert.m
├── documentation/
└── screenshots/
```

The reference PDF `4844301-IOT_Mini_Project.pdf` is intentionally excluded.

## Security Notes

- Never upload real ThingSpeak API keys to GitHub.
- Keep Write, Read, and Alerts API keys private.
- Regenerate any API key that has been exposed.
- The demonstration firmware uses `client.setInsecure()` for HTTPS, which disables certificate verification. Use proper certificate validation in production.

## Future Improvements

- Test the system on physical ESP32 hardware.
- Add more environmental sensors.
- Implement offline data buffering.
- Improve HTTPS certificate validation.
- Add configurable alert thresholds.

## Author

**Shubham Dattatray Asole**
