import sys
sys.path.append("../cmake-build-debug")

import messaging_py as messaging
import geography_py as geo
import sensor_data_py as sensor
import target_tracker_py as tracker
import mission_planner_py as planner
import command_executor_py as executor
import generate_scenario_py as gs
import types_py as types

print("---- Starting Command and Control Mission System ----")

### Create messaging and geography helpers
msg = messaging.Messaging()
geoSystem = geo.Geography()

### Create system components
sensorData = sensor.SensorData(msg)

targetTracker = tracker.TargetTracker(msg, geoSystem)

missionPlanner = planner.MissionPlanner(msg, targetTracker)

commandExecutor = executor.CommandExecutor(msg, targetTracker)

genScenStart = gs.GenerateScenario(sensorData, geoSystem, commandExecutor)

print("[Test Full Mission PY] ALL MODULES LOADED")

### Initialize system components
commandExecutor.initialize()
sensorData.initialize()
targetTracker.initialize()
missionPlanner.initialize()

print("[Test Full Mission PY] ALL System Components INITIALIZED")

LosAngeles = planner.Mission()
LosAngeles.area = types.MissionArea.LosAngeles
LosAngeles.name = "Los Angeles Python Scenario Run"

LosAngeles.targetCounts = {
    types.TargetType.Plane: 1,
    types.TargetType.Ship: 1,
    types.TargetType.Missile: 1
}

LosAngeles.scenarioDuration = 120

genScenStart.setFullMission(LosAngeles)
genScenStart.startScenario()

print("******** ---- [CommandAndControl] Mission Completed ---- ********")