import sys
sys.path.append("../cmake-build-debug")

import types_py as types
import geography_py as geo

print("types_py module loaded")

g = geo.Geography()

bounds = g.getGeoBounds(types.MissionArea.LosAngeles)

print("----Los Angeles Mission Geo Bounds----")
print("Area Bounds")
print("Min Latitude: ", bounds.minLatitude)
print("Max Latitude: ", bounds.maxLatitude)
print("Min Longitude: ", bounds.minLongitude)
print("Max Longitude: ", bounds.maxLongitude)