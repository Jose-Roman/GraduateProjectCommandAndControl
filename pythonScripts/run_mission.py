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

def runMission(mission):
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

    genScenStart.setFullMission(mission)
    genScenStart.startScenario()
