package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local msnplanner = require("mission_planner")

msnplanner.initialize()

msnplanner.set_mission("Surveillance Mission")

msnplanner.simulate_target("Target_001, 34.05, -118.25, 5000, 300");