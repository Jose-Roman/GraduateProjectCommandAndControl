//
// Created by Jose Roman  on 1/9/26.
//

#ifndef GENERATESCENARIO_H
#define GENERATESCENARIO_H

#include <map>
#include <Types.h>
#include <MissionPlanner.h>

class MissionPlanner;
class SensorData;

class GenerateScenario {
    public:
        explicit GenerateScenario(SensorData& sensor);
        void setMissionArea(MissionArea area);
        void setTargets(const std::map<TargetType, int>& targets);
        void setMissionName(std::string name);

        // entry point
        void startScenario();

    private:
        Mission mission_;
        SensorData& sensor_;

};

#endif // GENERATESCENARIO_H