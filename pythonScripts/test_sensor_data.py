import sys
sys.path.append("../cmake-build-debug")

import sensor_data_py as sensor
import messaging_py as messaging
import geography_py as geo

print("sensor_data_py module loaded")

msg = messaging.Messaging()

sensor_system = sensor.SensorData(msg)

sensor_system.initialize()

mission = sensor.Mission()
mission.area = geo.MissionArea.LosAngeles
mission.name = "Los Angeles"
mission.scenarioDuration = 120

sensor_system.startSensor(mission)