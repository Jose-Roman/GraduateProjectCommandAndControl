import sys
sys.path.append("../cmake-build-debug")

import types_py as types
import mission_planner_py as planner
from run_mission import runMission

def get_mission_area():
    print("Select Mission Area:")
    print("1. Los Angeles")
    print("2. Miami")
    print("3. New York")

    choice = input("Enter choice: ")
    if choice == "1":
        return types.MissionArea.LosAngeles
    elif choice == "2":
        return types.MissionArea.Miami
    elif choice == "3":
        return types.MissionArea.NewYork
    else:
        print("Invalid choice. Defaulting to Los Angeles")
        return types.MissionArea.LosAngeles


def get_target_counts():
    print("\nEnter number of targets: ")

    plane = int(input("Planes: "))
    ship = int(input("Ships: "))
    missile = int(input("Missiles: "))

    return {
        types.TargetType.Plane: plane,
        types.TargetType.Ship: ship,
        types.TargetType.Missile: missile
    }

def create_mission_from_input():
    mission = planner.Mission()

    mission.area = get_mission_area()

    mission.targetCounts = get_target_counts()

    mission.scenarioDuration = int(input("\nEnter scenario duration (seconds): "))

    return mission

if __name__ == "__main__":
    print("----Custom Command & Control Scenario----")

    mission = create_mission_from_input()

    print("\nRunning Mission:", mission.name)
    print("----------------------------------------")

    runMission(mission)