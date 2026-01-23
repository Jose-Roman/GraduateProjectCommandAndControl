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

    activeTracks_[track.id] = track;

    std::cout << "[TargetTracker] Active Track Created, ID = " << track.id << std::endl;

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

void TargetTracker::updateTrack(int targetId, double deltaTimeSec) {
    auto it = activeTracks_.find(targetId);

    if (it == activeTracks_.end()) {
        std::cout << "[TargetTracker] No active track found for ID " << targetId << std::endl;
        return;
    }

    Target& target = it->second;
    // Convert speed (m/s) into distance traveled
    double distance = target.speed * deltaTimeSec;

    double headingRadians = geography_.randomDouble(0.0, 2 * M_PI);

    int updates = 5;
    for (int i = 0; i < updates; i++) {
        // Simplified lat/long update
        target.latitude += (distance * std::cos(headingRadians)) * 1e-5 ;
        target.longitude += (distance * std::sin(headingRadians)) * 1e-5 ;

        target.altitude += geography_.randomDouble(-5.0, 5.0);

        target.numOfUpdates++;

        std::cout << "[TargetTracker] Target # " << target.id << " Update #: "
        << target.numOfUpdates << ""
        << target.latitude << ", "
        << target.longitude << ")"
        << std::endl;
    }
}
