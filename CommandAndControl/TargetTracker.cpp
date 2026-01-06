//
// Created by Jose Roman  on 12/22/25.
//

#include "TargetTracker.h"
#include <iostream>
#include <sstream>
#include "Geography.h"

// Constructor
TargetTracker::TargetTracker(Messaging &messaging, Geography& geography) : messaging_(messaging), geography_(geography) {
}

// Subscribes to sensor data messages so targets can be tracked
void TargetTracker::initialize() {
    messaging_.subscribe("sensor.data",
        [this](const Message& msg) {
            onSensorDataReceived(msg);
        });

    messaging_.subscribe("sensor.target.detected",
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

    std::string areaStr;
    std::string typeStr;

    std::istringstream iss(msg.payload);
    std::getline(iss, areaStr, ':');
    std::getline(iss, typeStr);

    MissionArea missionArea;
    TargetType targetType;
    if (areaStr == "LosAngeles")
        missionArea = MissionArea::LosAngeles;
    else if (typeStr == "NewYork")
        missionArea = MissionArea::NewYork;
    else
        missionArea = MissionArea::Miami;

    if (typeStr == "Plane")
        targetType = TargetType::Plane;
    else if (typeStr == "Ship")
        targetType = TargetType::Ship;
    else
        targetType = TargetType::Missile;

    Target track = trackTarget(missionArea, targetType);
    Message targetMsg;
    targetMsg.topic = "target.update";

    //std::ostringstream payload;
    //payload << "Target ID = " << track.id
    //        << " Position = ("<< track.latitude  << ", " << track.longitude << ")";
    //targetMsg.payload = payload.str();

    targetMsg.payload = serializeTarget(track);

    targetMsg.source = "TargetTracker";

    messaging_.publish(targetMsg);
}

// Simulates basic target tracking logic
// TODO : make a helper randomizer script that will generate simulated
// data that gives us long, lat, etc position values to simulate
// real world command and control environment
Target TargetTracker::trackTarget(MissionArea area, TargetType track) {
    static int targetCounter = 0;

    GeoBounds bounds = geography_.getGioBounds(area);
    GeoKinematics kinematics = geography_.getGioKinematics(track);

    Target target;
    target.id = ++targetCounter;
    target.type = track;
    //target.x = 100.0;
    //target.y = 200.0;

    target.latitude = geography_.randomDouble(bounds.minLatitude, bounds.maxLatitude);
    target.longitude = geography_.randomDouble(bounds.minLongitude,bounds.maxLongitude);
    target.altitude = geography_.randomDouble(kinematics.minAltitude, kinematics.maxAltitude);
    target.speed = geography_.randomDouble(kinematics.minSpeed, kinematics.maxSpeed);

    target.numOfUpdates = 0; // initialize

    std::cout << "[TargetTracker] Tracking Target: " << target.id << std::endl;
    return target;
}

std::string TargetTracker::serializeTarget(const Target& target) {
    std::ostringstream oss;
    oss << target.id << " "
        <<static_cast<int>(target.type) << " "
        <<target.latitude << " "
        <<target.longitude << " "
        <<target.altitude << " "
        <<target.speed << " "
        <<target.numOfUpdates;
    return oss.str();
}

Target TargetTracker::deserializeTarget(const std::string& payload) {
    Target track;
    std::istringstream iss(payload);
    int type;
    iss >> track.id
        >> type
        >> track.latitude
        >> track.longitude
        >> track.altitude
        >> track.speed
        >> track.numOfUpdates;

    track.type = static_cast<TargetType>(type);
    return track;
}