import sys
sys.path.append("../cmake-build-debug")

import types_py as types
import mission_planner_py as planner
from run_mission import runMission

Miami = planner.Mission()
Miami.area = types.MissionArea.Miami
Miami.name = "Miami Scenario 2"

Miami.targetCounts = {
    types.TargetType.Plane: 2,
    types.TargetType.Ship: 12,
    types.TargetType.Missile: 1
}

Miami.scenarioDuration = 400

runMission(Miami)