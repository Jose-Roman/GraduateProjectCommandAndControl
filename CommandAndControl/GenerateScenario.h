//
// Created by Jose Roman  on 1/9/26.
//

#ifndef GENERATESCENARIO_H
#define GENERATESCENARIO_H

#include <map>
#include <Types.h>
#include <MissionPlanner.h>
#include <Geography.h>
#include <CommandExecutor.h>

class MissionPlanner;
class SensorData;

class GenerateScenario {
    public:
        explicit GenerateScenario(SensorData& sensor, Geography& geography, CommandExecutor& commandExecutor);

        void setFullMission(Mission newMission);

        // entry point
        void startScenario();

    private:
        Mission mission_;
        SensorData& sensor_;
        Geography& geography_;
        CommandExecutor& commandExecutor_;

};

#endif // GENERATESCENARIO_H