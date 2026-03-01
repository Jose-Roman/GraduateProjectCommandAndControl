import sys
sys.path.append("../cmake-build-debug")

import messaging_py as msg

print("messaging_py module loaded")

messaging = msg.Messaging()

def on_sensor(message):
    print("Received message")
    print("Topic:", message.topic)
    print("Payload:", message.payload)

messaging.subscribe("sensor.data", on_sensor)

m = msg.Message()
m.topic = "sensor.data"
m.payload = "target detected"
m.timestamp = 10
m.source = "sensor"

published = messaging.publish(m)
