//
// Created by Jose Roman  on 12/22/25.
//

#ifndef TARGETTRACKER_H
#define TARGETTRACKER_H

#include "Messaging.h"
#pragma once
#include <string>

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
    double x;
    double y;
    int numOfUpdates;
};

class TargetTracker {
    public:
        // Constructor takes a reference to the messaging system
        explicit TargetTracker(Messaging& messaging);

        // Registers subscriptions needed for target tracking
        void initialize();

        // simulates the target tracking logic
        Target trackTarget();

        std::string serializeTarget(const Target& target);

    private:
        Messaging& messaging_;

        // Handles incoming sensor data messages
        void onSensorDataReceived(const Message& msg);
};

#endif //TARGETTRACKER_H