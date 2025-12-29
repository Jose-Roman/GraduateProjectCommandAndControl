//
// Created by Jose Roman  on 12/22/25.
//

#include "TargetTracker.h"
#include <iostream>
#include <sstream>

// Constructor
TargetTracker::TargetTracker(Messaging &messaging) : messaging_(messaging) {}

// Subscribes to sensor data messages so targets can be tracked
void TargetTracker::initialize() {}

// Callback invoked when sensor data is received
void TargetTracker::onSensorDataReceived(const Message& msg) {

}

// Simulates basic target tracking logic
Target TargetTracker::trackTarget() {}
