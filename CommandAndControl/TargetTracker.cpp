//
// Created by Jose Roman  on 12/22/25.
//

#include "TargetTracker.h"
#include <iostream>
#include <sstream>

// Constructor
TargetTracker::TargetTracker(Messaging &messaging) : messaging_(messaging) {}

// Subscribes to sensor data messages so targets can be tracked
void TargetTracker::initialize() {
    messaging_.subscribe("sensor.data",
        [this](const Message& msg) {
            onSensorDataReceived(msg);
        });

    std::cout << "[TargetTracker] Initialized and listening for sensor data"
                << std::endl;
}

// Callback invoked when sensor data is received
void TargetTracker::onSensorDataReceived(const Message& msg) {
    std::cout << "[TargetTracker] Sensor Data Received: "
                << msg.payload << std::endl;

    Target track = trackTarget();
    Message targetMsg;
    targetMsg.topic = "target.update";

    std::ostringstream payload;
    payload << "Target ID = " << track.id
            << " Position = ("<< track.x  << ", " << track.y << ")";
    targetMsg.payload = payload.str();
    targetMsg.source = "TargetTracker";

    messaging_.publish(targetMsg);
}

// Simulates basic target tracking logic
// TODO : make a helper randomizer script that will generate simulated
// data that gives us long, lat, etc position values to simulate
// real world command and control environment
Target TargetTracker::trackTarget() {
    static int targetCounter = 0;

    Target target;
    target.id = ++targetCounter;
    target.x = 100.0;
    target.y = 200.0;

    std::cout << "[TargetTracker] Tracking Target:" << target.id << std::endl;
}
