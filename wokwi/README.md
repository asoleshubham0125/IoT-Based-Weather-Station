# Wokwi Simulation

This directory contains the circuit configuration used for the IoT-Based Weather Station simulation.

## Components

- ESP32 DevKit C V4
- DHT22 Temperature and Humidity Sensor

## Connections

| ESP32 | DHT22 |
|---|---|
| 3V3 | VCC |
| GPIO 15 | SDA / DATA |
| GND | GND |

## Files

- `diagram.json` – Wokwi circuit layout and component connections.

## Simulation

Import the circuit configuration into a Wokwi ESP32 project and use the firmware file from the repository.

The ESP32 reads temperature and humidity values from the DHT22 and uploads them to ThingSpeak.
