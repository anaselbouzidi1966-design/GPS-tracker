#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <TinyGPS++.h>
#include "config.h"


// 3. GPS Pins 
#define RXD2 27
#define TXD2 26

TinyGPSPlus gps;
FirebaseData firebaseData;
FirebaseConfig config;
FirebaseAuth auth;

void setup()
{
  Serial.begin(115200);

  // Initialize GPS Serial
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // Initialize Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("System Ready. Waiting for GPS Lock...");
}

void loop()
{
  // Feed GPS data to the library
  while (Serial2.available() > 0)
  {
    gps.encode(Serial2.read());
  }

  // Send data to Firebase every 5 seconds
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 5000)
  {
    lastUpdate = millis();

    if (gps.location.isValid())
    {
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();
      float speedKmh = gps.speed.kmph();
      int satellites = gps.satellites.value();

      // Create a Google Maps Link
      String googleMapsLink = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);

      // Upload to Firebase
      Firebase.setFloat(firebaseData, "/Tracker/Latitude", latitude);
      Firebase.setFloat(firebaseData, "/Tracker/Longitude", longitude);
      Firebase.setFloat(firebaseData, "/Tracker/Speed", speedKmh);
      Firebase.setInt(firebaseData, "/Tracker/Satellites", satellites);
      Firebase.setString(firebaseData, "/Tracker/MapsLink", googleMapsLink);

      // Local Debugging
      Serial.printf("Sats: %d | Speed: %.2f km/h | Lat: %.6f\n", satellites, speedKmh, latitude);
    }
    else
    {
      Serial.print("Waiting for lock... Sats visible: ");
      Serial.println(gps.satellites.value());
    }
  }
}