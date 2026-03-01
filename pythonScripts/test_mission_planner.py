import sys
sys.path.append("../cmake-build-debug")

import mission_planner_py

print("mission_planner_py module loaded")

# TODO: test this later
# import messaging_py as msg
# import target_tracker_py as tracker
# import mission_planner_py as planner
#
# messaging = msg.Messaging()
# tracker = tracker.TargetTracker(messaging)
#
# planner = planner.MissionPlanner(messaging, tracker)
#
# planner.initialize()
#
# mission = planner.Mission()
# mission.area = planner.MissionArea.LosAngeles
# mission.name = "LA Defense"
# mission.scenarioDuration = 120
#
# mission.targetCounts = {
#     planner.TargetType.Plane: 1,
#     planner.TargetType.Ship: 1,
#     planner.TargetType.Missile: 1
# }
#
# planner.setMission(mission)
#
# print("Mission configured")