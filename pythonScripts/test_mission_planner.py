import sys
sys.path.append("../cmake-build-debug")

import messaging_py as messaging_mod
import geography_py as geo_mod
import target_tracker_py as tracker_mod
import mission_planner_py as planner_mod
import types_py as types

print("mission_planner_py module loaded")


# --------------------------------------------------
# Create Core System Components
# --------------------------------------------------

messaging = messaging_mod.Messaging()

geography = geo_mod.Geography()

tracker = tracker_mod.TargetTracker(messaging, geography)
tracker.initialize()

mission_planner = planner_mod.MissionPlanner(messaging, tracker)
mission_planner.initialize()


# --------------------------------------------------
# Create Mission
# --------------------------------------------------

mission = planner_mod.Mission()

mission.name = "Los Angeles"
mission.scenarioDuration = 120
mission.area = types.MissionArea.LosAngeles

# Target counts map
mission.targetCounts = {
    types.TargetType.Plane: 1,
    types.TargetType.Ship: 1,
    types.TargetType.Missile: 1
}


# --------------------------------------------------
# Set Mission
# --------------------------------------------------

mission_planner.setMission(mission)


print("Mission successfully configured")

print("Mission Name:", mission.name)
print("Mission Area:", mission.area)
print("Scenario Duration:", mission.scenarioDuration)

print("Target Counts:")
for t, count in mission.targetCounts.items():
    print("  ", t, ":", count)


print("Mission Planner complete")