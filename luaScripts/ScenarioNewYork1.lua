-- Add build directory to Lua native module search path
package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local command = require("commandcore")

command.start_mission{
	name = "Scenario New York 1",
	area = "NewYork",
	duration = 180,
	targets = {
		Plane = 7,
		Ship = 5,
		Missile = 2
	}
}
