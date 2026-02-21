package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local geo = require("geography")

print("---- Los Angeles Bounds ----")
local bounds = geo.get_bounds("LosAngeles")

print("Min Latitiude: ", bounds.minLatitude)
print("Max Latitiude: ", bounds.maxLatitude)
print("Min Longitude: ", bounds.minLongitude)
print("Max Longitude: ", bounds.maxLongitude)

print("\n---- New York Bounds ----")
local boundsNY = geo.get_bounds("NewYork")

print("Min Latitiude: ", boundsNY.minLatitude)
print("Max Latitiude: ", boundsNY.maxLatitude)
print("Min Longitude: ", boundsNY.minLongitude)
print("Max Longitude: ", boundsNY.maxLongitude)

print("\n---- Miami Bounds ----")
local boundsM = geo.get_bounds("Miami")

print("Min Latitiude: ", boundsM.minLatitude)
print("Max Latitiude: ", boundsM.maxLatitude)
print("Min Longitude: ", boundsM.minLongitude)
print("Max Longitude: ", boundsM.maxLongitude)


print("\n---- Plane Kinematics ----")
local kin = geo.get_kinematics("Plane")

print("Min Altitude: ", kin.minAltitude)
print("Max Altitude: ", kin.maxAltitude)
print("Min Speed: ", kin.minSpeed)
print("Max Speed: ", kin.maxSpeed)

print("\n---- Ship Kinematics ----")
local ship = geo.get_kinematics("Ship")

print("Min Altitude: ", ship.minAltitude)
print("Max Altitude: ", ship.maxAltitude)
print("Min Speed: ", ship.minSpeed)
print("Max Speed: ", ship.maxSpeed)

print("\n---- Missile Kinematics ----")
local missile = geo.get_kinematics("Missile")

print("Min Altitude: ", missile.minAltitude)
print("Max Altitude: ", missile.maxAltitude)
print("Min Speed: ", missile.minSpeed)
print("Max Speed: ", missile.maxSpeed)


print("\n---- Random ----")
print(geo.random(0, 100))

print("\n---- Los Angeles Sensor Location ----")
local locLA = geo.get_sensor_location("LosAngeles")

print("Latitiude: ", locLA.latitude)
print("Longitude: ", locLA.longitude)

print("\n---- New York Sensor Location ----")
local locNY = geo.get_sensor_location("NewYork")

print("Latitiude: ", locNY.latitude)
print("Longitude: ", locNY.longitude)

print("\n---- Miami Sensor Location ----")
local loc = geo.get_sensor_location("Miami")

print("Latitiude: ", loc.latitude)
print("Longitude: ", loc.longitude)


print("\n---- Los Angeles Parse Area ----")
print(geo.parse_area("LosAngeles"))

print("\n---- New York Parse Area ----")
print(geo.parse_area("NewYork"))

print("\n---- Maimi Parse Area ----")
print(geo.parse_area("Miami"))