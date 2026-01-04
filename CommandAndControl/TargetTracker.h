//
// Created by Jose Roman  on 12/22/25.
//

#ifndef TARGETTRACKER_H
#define TARGETTRACKER_H

#include "Messaging.h"
#include "MissionPlanner.h"
#include "TargetTracker.h"
#pragma once
#include <string>

class Geography;

enum class TargetType {
    Plane,
    Ship,
    Missile
};

// Data structure representing a tracked target
struct Target {
    // Includes a Target ID, and positioning info (x,y)
    int id;
    TargetType type;
    //double x;
    //double y;
    double latitude;
    double longitude;
    double altitude;
    double speed;
    int numOfUpdates;
};

class TargetTracker {
    public:
        // Constructor takes a reference to the messaging system
        explicit TargetTracker(Messaging& messaging, Geography& geography);

        // Registers subscriptions needed for target tracking
        void initialize();

        // simulates the target tracking logic
        Target trackTarget(MissionArea& area, TargetType& track);

        std::string serializeTarget(const Target& target);
        Target deserializeTarget(const std::string& payload);

    private:
        Messaging& messaging_;

        Geography& geography_;

        // Handles incoming sensor data messages
        void onSensorDataReceived(const Message& msg);
};

#endif //TARGETTRACKER_H