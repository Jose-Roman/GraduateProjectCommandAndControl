//
// Created by Jose Roman  on 1/9/26.
//

#ifndef GENERATESCENARIO_H
#define GENERATESCENARIO_H

#include <map>
#include <Types.h>
#include "MissionPlanner.h"

class MissionPlanner;
class SensorData;

class GenerateScenario {
    public:
        GenerateScenario(MissionPlanner& planner, SensorData& sensor);
        void setLocation(MissionArea area);
        void setTargetCount(TargetType type, int count);
        void startScenario();

    private:
        MissionArea area_;
        Mission mission_;
        std::map<TargetType, int> targetCounts_;

        MissionPlanner& planner_;
        SensorData& sensor_;
};


#endif // GENERATESCENARIO_H