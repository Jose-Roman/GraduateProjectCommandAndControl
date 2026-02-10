local command = require("commandcore")

command.start_mission{
	area = "Miami",
	duration = 60,
	targets = {
		Plane = 4,
		Ship = 1,
		Missile = 2
	}
}
