/*
  Automated Snooker Table System
  Author: Michael Unuaga-Joel (devjunkiee)
  Organization: Neovate Technologies
*/

#include <WiFi.h>
#include <ESP32Servo.h>
#include <Firebase_ESP_Client.h>


// Firebase helpers
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>


// ================= WIFI =================
#define WIFI_SSID     "NAME"  
#define WIFI_PASSWORD "PASSWORD"


// ================= FIREBASE =================
#define DATABASE_URL ""
#define DATABASE_SECRET ""


// ================= PINS =================
#define RED_LED     33
#define YELLOW_LED  26
#define GREEN_LED   27
#define BUZZER      14
#define SERVO_PIN   13


// ================= OBJECTS =================
Servo gateServo;
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


// ================= STATE =================
enum SystemState {
  CONNECTING_WIFI,
  CONNECTING_FIREBASE,
  IDLE_MONITORING,
  PAYMENT_SEQUENCE
};


SystemState systemState = CONNECTING_WIFI;


unsigned long blinkTimer = 0;
bool blinkState = false;


// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  delay(1000);


  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);


  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);


  // Servo
  gateServo.setPeriodHertz(50);
  gateServo.attach(SERVO_PIN, 500, 2400);
  gateServo.write(110); // CLOSED


  // WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}


// ================= LOOP =================
void loop() {


  // ---- WIFI ----
  if (systemState == CONNECTING_WIFI) {


    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("WiFi connected");
      beep(1);


      config.database_url = DATABASE_URL;
      config.signer.tokens.legacy_token = DATABASE_SECRET;


      Firebase.begin(&config, &auth);
      Firebase.reconnectWiFi(true);


      systemState = CONNECTING_FIREBASE;
    }
    else {
      blinkRed(500);
    }
  }


  // ---- FIREBASE ----
  else if (systemState == CONNECTING_FIREBASE) {


    if (Firebase.ready()) {
      Serial.println("Firebase connected");
      beep(1);


      digitalWrite(RED_LED, HIGH);
      systemState = IDLE_MONITORING;
    }
    else {
      blinkYellow(300);
    }
  }


  // ---- IDLE ----
  else if (systemState == IDLE_MONITORING) {


    digitalWrite(RED_LED, HIGH);


    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 3000) {
      lastCheck = millis();


      if (Firebase.RTDB.getBool(&fbdo, "/paid") && fbdo.boolData()) {
        systemState = PAYMENT_SEQUENCE;
      }
    }
  }


  // ---- PAYMENT ----
  else if (systemState == PAYMENT_SEQUENCE) {


    digitalWrite(RED_LED, LOW);
    beep(1);


    digitalWrite(YELLOW_LED, HIGH);
    delay(3000);
    digitalWrite(YELLOW_LED, LOW);


    digitalWrite(GREEN_LED, HIGH);
    gateServo.write(0);
    beep(1);


    delay(15000);


    gateServo.write(110);
    digitalWrite(GREEN_LED, LOW);


    Firebase.RTDB.setBool(&fbdo, "/paid", false);


    digitalWrite(RED_LED, HIGH);
    beep(1);


    systemState = IDLE_MONITORING;
  }
}


// ================= HELPERS =================


void blinkRed(int interval) {
  static unsigned long t = 0;
  if (millis() - t > interval) {
    t = millis();
    blinkState = !blinkState;
    digitalWrite(RED_LED, blinkState);
  }
}


void blinkYellow(int interval) {
  static unsigned long t = 0;
  if (millis() - t > interval) {
    t = millis();
    blinkState = !blinkState;
    digitalWrite(YELLOW_LED, blinkState);
  }
}


void beep(int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(150);
  }
}


