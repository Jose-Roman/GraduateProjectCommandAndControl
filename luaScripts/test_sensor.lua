package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

sensor = require("sensor")

print("=== Sensor Test Start ===")

-- initialize sensor
sensor.initialize()

-- read sensor
local reading = sensor.read()
print("Sensor reading:")
print("Name:", reading.name)
print("Value:", reading.value)

-- publish sensor data
sensor.publish()

-- test mission trigger version
sensor.start_mission("TestMission")

print("=== Sensor Test Complete ===")

