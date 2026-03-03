import sys
sys.path.append("../cmake-build-debug")

import types_py as types
import mission_planner_py as planner
from run_mission import runMission

LosAngeles = planner.Mission()
LosAngeles.area = types.MissionArea.LosAngeles
LosAngeles.name = "Los Angeles Scenario 2"

LosAngeles.targetCounts = {
    types.TargetType.Plane: 10,
    types.TargetType.Ship: 2,
    types.TargetType.Missile: 4
}

LosAngeles.scenarioDuration = 300

runMission(LosAngeles)