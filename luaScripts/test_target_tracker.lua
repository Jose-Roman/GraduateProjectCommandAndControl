package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local tracker = require("target_tracker")

tracker.initialize()

tracker.simulate_sensor("LosAngeles", 0)

tracker.simulate_detection("Miami", 2)