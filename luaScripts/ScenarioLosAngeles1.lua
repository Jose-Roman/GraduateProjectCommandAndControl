-- Add build directory to Lua native module search path
package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local command = require("commandcore")

command.start_mission{
	name = "Scenario Los Angeles 1",
	area = "LosAngeles",
	duration = 300,
	targets = {
		Plane = 17,
		Ship = 4,
		Missile = 0
	}
}
