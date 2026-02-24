package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local scenario = require("generate_scenario")

scenario.set_mission{
	name = "Miami Defense Mission",
	area = "Miami",
	duration = 60,

	targets = {
		Plane = 2,
		Ship = 1,
		Missile = 1
	}
}

scenario.start()