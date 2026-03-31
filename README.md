# 🔐 Smart Home Intrusion Detection System

An end-to-end IoT security system built on Arduino and Raspberry Pi that detects motion, triggers local alerts, and delivers real-time notifications via Telegram — with cloud-based event logging through ThingSpeak.

---

## Overview

This project was built to explore how low-cost IoT hardware can be used to construct a functional, real-time security alerting pipeline. It covers the full stack: embedded hardware, wireless messaging protocol (MQTT), Python scripting, API integration, and cloud data logging.

**Key design principle:** alerts should reach the owner within seconds of detection, regardless of whether they are on-site.

---

## System Architecture

```
PIR Sensor → Arduino UNO R4 WiFi
                    │
               MQTT Publish (Mosquitto broker)
                    │
             Raspberry Pi (MQTT Subscriber)
                    │
          ┌─────────┴──────────┐
     Telegram API          ThingSpeak
   (instant mobile alert)  (cloud event log)
```

---

## Hardware Components

| Component | Role |
|---|---|
| Arduino UNO R4 WiFi | Microcontroller — reads PIR sensor, publishes MQTT alerts |
| PIR Motion Sensor | Detects movement in monitored area |
| Raspberry Pi | MQTT broker + Telegram notification dispatcher |
| Grove 16x2 RGB LCD | Real-time status display |
| Buzzer | Audible local alarm |
| LED Button | Visual indicator |

---

## Software Stack

- **Arduino IDE** — C++ sketch for motion detection and MQTT publishing
- **Python 3** — MQTT subscriber and Telegram Bot API integration on Raspberry Pi
- **Mosquitto** — Lightweight MQTT broker
- **ThingSpeak** — Cloud-based IoT data logging and visualisation
- **Telegram Bot API** — Real-time push notifications

---

## Security Implementation

Credentials (WiFi SSID/password, Telegram Bot Token, Chat ID) are stored in a separate `arduino_secrets.h` file which is excluded from version control via `.gitignore`.

**Never hardcode credentials in your main sketch.** This project uses:

```cpp
// arduino_secrets.h (not committed to repo)
#define SECRET_SSID "your_wifi_name"
#define SECRET_PASS "your_wifi_password"
```

```python
# config.py (not committed to repo) 
BOT_TOKEN = "your_telegram_bot_token"
CHAT_ID = "your_chat_id"
```

A `.gitignore` is included to prevent accidental credential exposure.

---

## How It Works

1. **Detection** — PIR sensor continuously monitors the environment. On motion, Arduino reads a `HIGH` signal.
2. **Local Alert** — Buzzer activates, LED lights, LCD displays `"Trespassing ALERT!"` in red.
3. **MQTT Publish** — Arduino publishes an alert message to the `security/intrusion_detection` topic on the Mosquitto broker.
4. **Raspberry Pi Processing** — Python subscriber receives the MQTT message and logs it to `intrusion_log.txt`.
5. **Telegram Notification** — Alert is forwarded via Telegram Bot API to the owner's phone within seconds.
6. **Cloud Logging** — Event data is pushed to ThingSpeak for historical analysis and visualisation.
7. **Auto-Reset** — If no motion for 10 seconds, system resets: LCD shows `"System Secure"`, LED and buzzer deactivate.

---

## Setup Instructions

### Arduino
1. Install dependencies: `WiFiS3`, `PubSubClient`, `rgb_lcd`
2. Create `arduino_secrets.h` with your WiFi credentials (see template above)
3. Flash `Intrusion_Detection__jan23a.ino` via Arduino IDE

### Raspberry Pi
1. Install dependencies: `pip install paho-mqtt requests`
2. Create `config.py` with your Telegram bot token and chat ID
3. Run the subscriber: `python3 mqtt_subscriber.py`
4. Run the Telegram dispatcher: `python3 telegram_alert.py`

### Create a Telegram Bot
1. Message `@BotFather` on Telegram → `/newbot`
2. Copy the token into `config.py`
3. Get your Chat ID via `https://api.telegram.org/bot<token>/getUpdates`

---

## Testing Results

| Test Case | Expected Result | Status |
|---|---|---|
| Motion detected | Buzzer sounds, LED on, LCD shows alert | ✅ Pass |
| No motion for 10s | System resets to secure mode | ✅ Pass |
| Telegram alert | Push notification received on phone | ✅ Pass |
| MQTT logging | Events logged on Raspberry Pi terminal | ✅ Pass |
| ThingSpeak logging | Events visible on cloud dashboard | ✅ Pass |

---

## Challenges & Lessons Learned

- **Hardware failure:** Original project planned as an Elderly Fall Detection System using MPU9250 accelerometer. Sensor was damaged during testing — pivoted to Intrusion Detection. Reinforced the importance of contingency planning and component redundancy in hardware projects.
- **WiFi stability:** Intermittent disconnections caused MQTT publish failures. Implemented reconnect logic in the Arduino sketch to handle dropped connections gracefully.
- **Credential management:** Initial version had credentials hardcoded. Refactored to use `arduino_secrets.h` and environment-separated config to follow security best practices.

---

## Future Improvements

- [ ] Replace polling with interrupt-driven PIR detection for lower latency
- [ ] Add camera module to Raspberry Pi for image capture on alert
- [ ] Integrate with Azure IoT Hub for enterprise-grade cloud logging
- [ ] Add ML-based false positive filtering (distinguish human motion from pets/environmental movement)
- [ ] Encrypted MQTT (TLS) to prevent message interception on the broker

---

## Project Demo

Video walkthrough available — shows live motion detection, MQTT message flow, and Telegram alert delivery in real-time.

---

## Tech Stack Tags

`Arduino` `Raspberry Pi` `IoT` `MQTT` `Python` `Telegram API` `ThingSpeak` `Embedded Security` `Network Security` `C++`
