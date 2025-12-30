//
// Created by Jose Roman  on 12/22/25.
//

#ifndef TARGETTRACKER_H
#define TARGETTRACKER_H

#include "Messaging.h"

// Data structure representing a tracked target
struct Target {
    // Includes a Target ID, and positioning info (x,y)
    int id;
    double x;
    double y;
};

class TargetTracker {
    public:
        // Constructor takes a reference to the messaging system
        explicit TargetTracker(Messaging& messaging);

        // Registers subscriptions needed for target tracking
        void initialize();

        // simulates the target tracking logic
        Target trackTarget();

    private:
        Messaging& messaging_;

        // Handles incoming sensor data messages
        void onSensorDataReceived(const Message& msg);
};

#endif //TARGETTRACKER_H