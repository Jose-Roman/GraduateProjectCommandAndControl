package.cpath = package.cpath .. ";../cmake-build-debug/?.dylib"

print("---- Starting Command and Control Mission System ----")

local Messaging        = require("messaging")
local Geography        = require("geography")
local sensorData       = require("sensor")
local targetTracker    = require("target_tracker")
local missionPlanner   = require("mission_planner")
local commandExecutor  = require("command_executor")
local genScenario      = require("generate_scenario")

--------------------------------------------------
-- Define Mission
--------------------------------------------------
local LosAngeles = {
	area = "LosAngeles",   -- MUST match struct field exactly
	name = "Los Angeles",
	duration = 120,
	targets = {
		Plane   = 1,
		Ship    = 1,
		Missile = 1
	}
}

--------------------------------------------------
-- Start Scenario (constructors already initialized)
--------------------------------------------------
genScenario.set_mission(LosAngeles)
genScenario.start()

print("******** ---- [CommandAndControl] Mission Completed ---- ********")
print("******** ---- [CommandAndControl] Mission Completed ---- ********")