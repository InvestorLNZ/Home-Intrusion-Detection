#include <WiFiS3.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <PubSubClient.h>  

const char* ssid = "VM2233583";  
const char* password = "Jr3nttcntSrd";  
const char* mqtt_server = "test.mosquitto.org";  
const char* mqtt_topic = "security/intrusion_detection";

#define PIR_SENSOR 2  // PIR Motion Sensor on D2
#define BUZZER 3  // Buzzer on D3
#define LED_BUTTON 5  // LED Button on D5 (Acts as both LED and Button)
rgb_lcd lcd;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMotionTime = 0;
const unsigned long safeModeDelay = 10000; // 10 seconds

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message received: ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ArduinoClient")) {
            Serial.println("Connected to MQTT Broker!");
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" Trying again in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);  // Serial Monitor
    pinMode(PIR_SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED_BUTTON, OUTPUT);
    digitalWrite(LED_BUTTON, LOW); // Ensure LED is off initially

    // Initialize LCD
    lcd.begin(16, 2);
    lcd.setRGB(0, 255, 0);
    lcd.print("System Ready");

    Serial.println(" Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
    }
    Serial.println(" Connected to WiFi!");

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    int motionDetected = digitalRead(PIR_SENSOR);

    if (motionDetected == HIGH) {
        Serial.println(" Motion Detected!");
        client.publish(mqtt_topic, "ALERT: Trespassing Detected!");

        digitalWrite(BUZZER, HIGH);
        digitalWrite(LED_BUTTON, HIGH);
        lcd.clear();
        lcd.setRGB(255, 0, 0);
        lcd.setCursor(0, 0);
        lcd.print("Trespassing ALERT!");

        delay(2000);  // Buzzer beeps for 2 seconds
        digitalWrite(BUZZER, LOW);  // Turn off buzzer after 2 seconds

        lastMotionTime = millis(); // Update last motion time
    }

    // Reset LCD and LED to Safe Mode if no motion detected for 10 seconds
    if ((millis() - lastMotionTime) >= safeModeDelay) {
        lcd.clear();
        lcd.setRGB(0, 255, 0);
        lcd.setCursor(0, 0);
        lcd.print("System Secure");
        digitalWrite(LED_BUTTON, LOW); // Turn off LED after safe mode
    }

    delay(1000);
}

