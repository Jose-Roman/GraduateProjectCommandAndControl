import sys
sys.path.append("../cmake-build-debug")

import types_py as types
import mission_planner_py as planner
from run_mission import runMission

NewYork = planner.Mission()
NewYork.area = types.MissionArea.Miami
NewYork.name = "New York Scenario 2"

NewYork.targetCounts = {
    types.TargetType.Plane: 8,
    types.TargetType.Ship: 2,
    types.TargetType.Missile: 3
}

NewYork.scenarioDuration = 400

runMission(NewYork)