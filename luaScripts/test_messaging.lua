package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local messaging = require("messaging")

messaging.subscribe("sensor.data")

local result = messaging.publish{
	topic = "sensor.data",
	payload = "NewYork:0",
	source = "messaging lua test"
}

print("Message ID: ", result.messageId)
print("Timestamp: ", result.timestamp)