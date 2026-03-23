# GPS Tracker — ESP32 + NEO-6M

A real-time GPS tracking system that displays live location and satellite 
count on an interactive web map.
built on ESP32 with Firebase as backend.

## Demo
![Hardware](assets/hardware.jpg)
![Dashboard](assets/dashboard.png)

## What It Does
- Reads GPS coordinates and satellite count from NEO-6M module
- Sends live data to Firebase Realtime Database
- Displays real-time position on an interactive map via local web dashboard

## Hardware
| Component | Details |
|---|---|
| Microcontroller | ESP32 |
| GPS Module | NEO-6M |

## Wiring
![Wiring Diagram](assets/wiring.jpg)

## Libraries Used
- [TinyGPSPlus](https://github.com/mikalhart/TinyGPSPlus) — GPS data parsing
- [Firebase ESP32 Client](https://github.com/mobizt/Firebase-ESP32-Client) — Firebase communication

## How It Works
1. NEO-6M reads GPS coordinates and satellite count
2. ESP32 parses data using TinyGPSPlus
3. Data pushed to Firebase Realtime Database in real time
4. Local web dashboard reads Firebase and renders position on map using Leaflet.js

## Built With
- PlatformIO
- Firebase Realtime Database
- HTML / CSS / JavaScript
- Leaflet.js

## Author
Anas El-Bouzidi — ENIAD Berkane, Robotique et Objets Connectés
