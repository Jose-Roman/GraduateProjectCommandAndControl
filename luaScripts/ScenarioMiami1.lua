-- Add build directory to Lua native module search path
package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local command = require("commandcore")

command.start_mission{
	name = "Scenario Miami 1",
	area = "Miami",
	duration = 120,
	targets = {
		Plane = 1,
		Ship = 1,
		Missile = 1
	}
}
