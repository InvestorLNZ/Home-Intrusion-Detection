Smart Home Intrusion Detection System

Overview

This project is an **IoT-based Smart Home Intrusion Detection System** that detects motion using a **PIR sensor** and alerts the homeowner in real-time. The system integrates **Arduino UNO R4 WiFi**, **Raspberry Pi**, **MQTT protocol**, and **Telegram notifications** for remote security monitoring.

Features

✅ **Motion Detection** using a PIR sensor.
✅ **Buzzer & LED Alert** when intrusion is detected.
✅ **LCD Display** showing system status.
✅ **MQTT Communication** between Arduino and Raspberry Pi.
✅ **Telegram Notifications** for real-time alerts.
✅ **Auto-Reset** if no motion is detected for 10 seconds.

---

## **Hardware Components**

- **Arduino UNO R4 WiFi**
- **PIR Motion Sensor**
- **Buzzer**
- **LED Button**
- **Grove 16x2 LCD**
- **Raspberry Pi (for MQTT & Telegram integration)**

## **Software & Cloud Services**

- **Arduino IDE**
- **Python (for Raspberry Pi)**
- **Mosquitto MQTT Broker**
- **Telegram API**
- **ThingSpeak (Optional for logging)**

---

## **Project Structure**

```
Smart-Home-Intrusion/
│── Arduino_Code/
│   ├── Smart_Home_Intrusion.ino
│── RaspberryPi_Code/
│   ├── mqtt_subscriber.py
│   ├── telegram_notifier.py
│── intrusion_log.txt  # Logs alerts
│── README.md  # This Documentation
```

---

## **Installation & Setup**

### **1️ Setup Arduino**

1. Install **Arduino IDE**.
2. Upload `Smart_Home_Intrusion.ino` to the **Arduino UNO R4 WiFi**.
3. Ensure PIR, Buzzer, LED, and LCD are correctly wired.

### **2️ Setup Raspberry Pi**

1. Install **MQTT Broker (Mosquitto)**:
   ```bash
   sudo apt update
   sudo apt install mosquitto mosquitto-clients
   ```
2. Install required Python libraries:
   ```bash
   pip3 install paho-mqtt requests
   ```
3. Place `mqtt_subscriber.py` and `telegram_notifier.py` in your **Raspberry Pi home directory**.

### **  Run the System**

#### **Start MQTT Listener on Raspberry Pi**

```bash
python3 mqtt_subscriber.py
```

#### **Run Telegram Notifications**

```bash
python3 telegram_notifier.py
```

---

Usage

- When motion is detected:
  - The Buzzer sounds, LED lights up, and LCD displays 'Intrusion Alert!'
  - **Arduino publishes an MQTT message** to Raspberry Pi.
  - **Raspberry Pi forwards the alert to Telegram**.
- **If no motion is detected for 10 seconds:**
  - System resets to **'Safe Mode'**.
  - **Buzzer & LED turn off**, LCD updates to 'System Secure'.

---

Automation (Optional: Run on Boot)

To **automatically start MQTT & Telegram scripts on boot:

1. Open the crontab editor:
   ```bash
   crontab -e
   ```
2. Add the following lines at the end:
   ```bash
   @reboot python3 /home/pi/mqtt_subscriber.py &
   @reboot python3 /home/pi/telegram_notifier.py &
   ```
3. Save and exit.

---

Contributing

Feel free to improve this project by:

- Enhancing security (e.g., encrypt MQTT messages).
- Adding a **mobile app integration.
- Implementing **AI-based motion detection.

---

License

This project is open-source under the **MIT License**. **Developed by Investor Lnz*

