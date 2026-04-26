import sys
sys.path.append("../cmake-build-debug")

import types_py as types
import mission_planner_py as planner
from run_mission import runMission

Fullerton = planner.Mission()
Fullerton.area = types.MissionArea.Fullerton
Fullerton.name = "Fullerton Scenario 2"

Fullerton.targetCounts = {
    types.TargetType.Plane: 11,
    types.TargetType.Ship: 0,
    types.TargetType.Missile: 0
}

Fullerton.scenarioDuration = 240

runMission(Fullerton)