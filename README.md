# Automated Snooker Table System

## Overview
An event-driven snooker table access control system that replaces coin-based play using payment-triggered automation.

The system currently uses an Android device to detect payment alerts and trigger table access via a cloud-connected ESP32 controller, with Firebase acting as the central event broker.

---

## How the System Works
1. A customer makes a ₦500 payment.
2. An Android phone receives the payment notification.
3. MacroDroid detects the notification and updates the `paid` flag in Firebase Realtime Database.
4. The ESP32 continuously listens for realtime database changes.
5. When `paid = true` is detected:
   - The system enters a processing state.
   - Visual and audio indicators are activated.
   - The servo motor unlocks the snooker table.
6. After a fixed gameplay duration, the table is locked again and the system resets for the next user.

---

## System Architecture
The system follows a payment-triggered access control pipeline, with Firebase serving as the single source of truth.

![System Architecture](diagrams/system Architecture.png)

---

## ESP32 Control Logic
The ESP32 operates as a state-based controller, managing Wi-Fi connectivity, payment detection, and timed table access.

![ESP32 State Flow](diagrams/esp32 control logic.png)

---

## Hardware Components

### ESP32
- Acts as the main controller for system logic and decision-making.  
- Listens to Firebase and controls all connected peripherals.

### Servo Motor
- Mechanically locks and unlocks the snooker table.  
- Activated when payment is confirmed.

### Buzzer
- Provides audio feedback during payment and state transitions.  
- Signals successful activation and reset events.

### Traffic Light Indicator
- Displays system states using color signals.  
- Indicates idle, processing, and active gameplay states.

### Buck Converter
- Steps down and regulates voltage from the power source.  
- Protects components by ensuring stable power delivery.

### Capacitor
- Smooths voltage fluctuations during servo operation.  
- Prevents resets and unstable ESP32 behavior.

### Power Bank
- Supplies portable power to the system.  
- Allows operation without direct mains electricity.

---

## Software Components
- **Arduino IDE** – used to develop and upload ESP32 firmware.
- **Firebase Realtime Database** – acts as the central event broker and state store.
- **MacroDroid** – detects payment notifications and updates Firebase accordingly.

---

## Current Limitations
- The system relies on an Android phone for payment detection.
- Notification-based triggers may fail when the phone screen is off.
- Payment validation depends on notification content matching.

---

## Possible Improvements
- Replace phone-based automation with direct payment API or webhook integration.
- Introduce a dedicated backend for secure payment verification.
- Add a web-based admin dashboard for analytics and monitoring.
- Extend support to multiple tables and locations.

---

## License
MIT License © 2026 Michael Unuaga-Joel (devjunkiee)
