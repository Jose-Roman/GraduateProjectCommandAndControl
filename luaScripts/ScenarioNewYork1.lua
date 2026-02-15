-- Add build directory to Lua native module search path
package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

local command = require("commandcore")

command.start_mission{
	area = "NewYork",
	duration = 180,
	targets = {
		Plane = 1,
		Ship = 0,
		Missile = 0
	}
}
