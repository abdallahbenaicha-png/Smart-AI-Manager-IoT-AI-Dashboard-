#include <WiFi.h>
#include <FirebaseESP32.h>

// WiFi
#define WIFI_SSID "YOUR_WIFI"
#define WIFI_PASSWORD "YOUR_PASSWORD"

// Firebase
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your_firebase_secret"

FirebaseData fbdo;

// Sensors
int tempPin = 34;
int relayPin = 26;

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  int tempValue = analogRead(tempPin);
  float temperature = (tempValue * 3.3 / 4095.0) * 100;

  // Send data to Firebase
  Firebase.setFloat(fbdo, "/sensor/temperature", temperature);

  // Receive AI decision
  Firebase.getString(fbdo, "/ai/fan_status");
  String fanStatus = fbdo.stringData();

  if (fanStatus == "ON") {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

  delay(2000);
}
