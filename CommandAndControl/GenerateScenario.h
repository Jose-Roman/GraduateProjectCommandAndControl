//
// Created by Jose Roman  on 1/9/26.
//

#ifndef GENERATESCENARIO_H
#define GENERATESCENARIO_H

#include <map>
#include <Types.h>
#include <MissionPlanner.h>
#include <Geography.h>

class MissionPlanner;
class SensorData;

class GenerateScenario {
    public:
        explicit GenerateScenario(SensorData& sensor, Geography& geography);
        void setMissionArea(MissionArea area);
        void setTargets(const std::map<TargetType, int>& targets);
        void setMissionName(std::string name);

        // entry point
        void startScenario();

    private:
        Mission mission_;
        SensorData& sensor_;
        Geography& geography_;

};

#endif // GENERATESCENARIO_H