import sys
sys.path.append("../cmake-build-debug")

import geography_py as geo

print("geography_py module loaded")

g = geo.Geography()

bounds = g.getGeoBounds(geo.MissionArea.LosAngeles)

print("----Los Angeles Mission----")
print("Area Bounds")
print("Min Latitude: ", bounds.minLatitude)
print("Max Latitude: ", bounds.maxLatitude)
print("Min Longitude: ", bounds.minLongitude)
print("Max Longitude: ", bounds.maxLongitude)

sensor = geo.Geography.getSensorLocation(geo.MissionArea.LosAngeles)
print("Sensor Location")

print("Latitude: ", sensor.latitude)
print("Longitude: ", sensor.longitude)
print("----------------------------")

miamiBounds = g.getGeoBounds(geo.MissionArea.Miami)

print("----Miami Mission----")
print("Area Bounds")
print("Min Latitude: ", miamiBounds.minLatitude)
print("Max Latitude: ", miamiBounds.maxLatitude)
print("Min Longitude: ", miamiBounds.minLongitude)
print("Max Longitude: ", miamiBounds.maxLongitude)

miamiSensor = geo.Geography.getSensorLocation(geo.MissionArea.Miami)
print("Sensor Location")

print("Latitude: ", miamiSensor.latitude)
print("Longitude: ", miamiSensor.longitude)
print("----------------------------")

nyBounds = g.getGeoBounds(geo.MissionArea.NewYork)

print("----New York Mission----")
print("Area Bounds")
print("Min Latitude: ", nyBounds.minLatitude)
print("Max Latitude: ", nyBounds.maxLatitude)
print("Min Longitude: ", nyBounds.minLongitude)
print("Max Longitude: ", nyBounds.maxLongitude)

nySensor = geo.Geography.getSensorLocation(geo.MissionArea.NewYork)
print("Sensor Location")

print("Latitude: ", nySensor.latitude)
print("Longitude: ", nySensor.longitude)
print("----------------------------")



print("---- Plane Kinematics ----")

kin = g.getGeoKinematics(geo.TargetType.Plane)

print("Min Altitude: ", kin.minAltitude)
print("Max Altitude: ", kin.maxAltitude)
print("Min Speed: ", kin.minSpeed)
print("Max Speed: ", kin.maxSpeed)

print("---- Ship Kinematics ----")

ship = g.getGeoKinematics(geo.TargetType.Ship)

print("Min Altitude: ", ship.minAltitude)
print("Max Altitude: ", ship.maxAltitude)
print("Min Speed: ", ship.minSpeed)
print("Max Speed: ", ship.maxSpeed)

print("---- Missile Kinematics ----")

missile = g.getGeoKinematics(geo.TargetType.Missile)

print("Min Altitude: ", missile.minAltitude)
print("Max Altitude: ", missile.maxAltitude)
print("Min Speed: ", missile.minSpeed)
print("Max Speed: ", missile.maxSpeed)

print("---- Random Double----")
print(g.randomDouble(0, 100))