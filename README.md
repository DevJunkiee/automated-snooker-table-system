# Automated Snooker Table System

## Overview
An event-driven snooker table access control system that replaces coin-based play using payment-triggered automation.

The system currently uses an Android device to detect payment alerts and trigger table access via a cloud-connected ESP32 controller.

## How the System Works
1. A customer makes a ₦500 payment.
2. An Android phone receives the payment notification.
3. MacroDroid detects the alert and updates Firebase Realtime Database.
4. The ESP32 listens for changes in Firebase.
5. When payment is confirmed, the ESP32 activates the table lock mechanism using a servo motor and provides visual and audio feedback.

## System Architecture
![System Architecture](diagrams/system-architecture-v1.png)

## Hardware Components
- ESP32
- Servo motor
- Buzzer
- Traffic light indicator
- Buck converter
- Capacitor
- Power bank

## Software Components
- Arduino IDE (ESP32 firmware)
- Firebase Realtime Database
- MacroDroid (Android automation)

## Current Limitations
- The system relies on an Android phone for payment detection.
- MacroDroid struggles to read notifications reliably when the phone screen is off.
- Notification-based payment detection is not fully robust.

## Possible Improvements
- Replace phone-based automation with direct payment API integration.
- Build a dedicated backend to validate payments.
- Add a web-based admin dashboard.
- Improve reliability with event acknowledgements and retries.
