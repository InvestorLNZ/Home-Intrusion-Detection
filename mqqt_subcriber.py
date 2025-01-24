
import paho.mqtt.client as mqtt


BROKER = "test.mosquitto.org"
TOPIC = "security/intrusion_detection"


def on_message(client, userdata, message):
    print(f" Received: {message.payload.decode()}")
    
    # Log message to CSV file
    with open("fall_detection_log.csv", "a") as log_file:
        log_file.write(f"{message.payload.decode()}\n")


# Initialize MQTT client
client = mqtt.Client()
client.on_message = on_message
client.connect(BROKER, 1883, 60)


client.subscribe(TOPIC)
print(" Listening for MQTT messages...")


client.loop_forever()

