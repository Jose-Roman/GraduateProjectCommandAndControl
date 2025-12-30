//
// Created by Jose Roman  on 12/22/25.
//

#ifndef MISSIONPLANNER_H
#define MISSIONPLANNER_H

#include <string>
#include "Messaging.h"
#include "TargetTracker.h"

class MissionPlanner {
    public:
        // Constructor that accepts a reference to the messaging system
        explicit MissionPlanner(Messaging& messaging, TargetTracker& tracker);

        // Registers the MissionPlanner to receive targer tracking updates
        void initialize();
    private:
        Messaging& messaging_;
        TargetTracker& tracker_;

        // Callback invoked when a target tracking message is received
        void onTargetReceived(const Message& msg) const;

        // Creates and publishes a command based on target data
        void planMission(const Target& track) const;
};


#endif // MISSIONPLANNER_H