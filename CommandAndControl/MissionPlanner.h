//
// Created by Jose Roman  on 12/22/25.
//

#ifndef MISSIONPLANNER_H
#define MISSIONPLANNER_H

#pragma once
#include <string>
#include "Messaging.h"
#include "MissionPlanner.h"

class TargetTracker;
class Target;

enum class MissionArea {
    LosAngeles,
    NewYork,
    Miami
};

struct Mission {
    MissionArea area;
    std::string name;
};

class MissionPlanner {
    public:
        // Constructor that accepts a reference to the messaging system
        explicit MissionPlanner(Messaging& messaging, TargetTracker& tracker);

        // Registers the MissionPlanner to receive targer tracking updates
        void initialize();

        void setMission(const Mission& mission);
    private:
        Messaging& messaging_;
        TargetTracker& tracker_;
        Mission currentMission_;

        // Callback invoked when a target tracking message is received
        void onTargetReceived(const Message& msg);

        // Creates and publishes a command based on target data
        void planMission(Target& track);

        void planMissionArea(Target &target);
};


#endif // MISSIONPLANNER_H