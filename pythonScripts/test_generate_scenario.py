import sys
sys.path.append("../cmake-build-debug")

import messaging_py as messaging
import geography_py as geo
import target_tracker_py as tracker
import sensor_data_py as sensor
import mission_planner_py as planner
import command_executor_py as executor
import generate_scenario_py as scenario
import types_py as types

print("generate_scenario_py module loaded")

# --------------------------------------------------
# Create core systems
# --------------------------------------------------

msg_system = messaging.Messaging()

geography = geo.Geography()

target_tracker = tracker.TargetTracker(msg_system, geography)
target_tracker.initialize()

sensor_system = sensor.SensorData(msg_system)
sensor_system.initialize()

command_executor = executor.CommandExecutor(msg_system, target_tracker)
command_executor.initialize()

mission_planner = planner.MissionPlanner(msg_system, target_tracker)
mission_planner.initialize()

# --------------------------------------------------
# Create GenerateScenario engine
# --------------------------------------------------

scenario_engine = scenario.GenerateScenario(
    sensor_system,
    geography,
    command_executor
)

# --------------------------------------------------
# Configure mission
# --------------------------------------------------

mission = planner.Mission()
mission.area = types.MissionArea.LosAngeles
mission.name = "Los Angeles Mission"
mission.scenarioDuration = 120

mission.targetCounts = {
    types.TargetType.Plane: 1,
    types.TargetType.Ship: 1,
    types.TargetType.Missile: 1
}

mission_planner.setMission(mission)

# --------------------------------------------------
# Start Scenario
# --------------------------------------------------

print("---- Starting Scenario ----")

scenario_engine.startScenario()

print("******** Mission Completed ********")