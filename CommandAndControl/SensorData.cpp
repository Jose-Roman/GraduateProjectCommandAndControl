//
// Created by Jose Roman  on 12/22/25.
//

#include "SensorData.h"
#include <iostream>

// Constructor
SensorData::SensorData(Messaging &messaging) : messaging_(messaging){}

// Initialize the sensor system
void SensorData::initialize() {
    std::cout << "[SensorData] Sensor initialized" << std::endl;
}

// Simulates retriving data from the system
SensorReading SensorData::readSensor() const {
    SensorReading reading;
    // TODO sensor name and value
    // default values for now
    reading.sensorName = "TEMP NAME";
    reading.value = 60.0;
    return reading;
}

// Publishes sensor data to the messaging system
void SensorData::publishSensorData() {
    SensorReading reading = readSensor();
    std::cout << "[SensorData] Sensor Reading: "
                << reading.sensorName << " = "
                << reading.value << std::endl;

    Message msg;
    msg.topic = "sensor.data";
    msg.payload = reading.sensorName + " = " + std::to_string(reading.value);
    msg.source = "SensorData";

    // Publish message
    messaging_.publish(msg);
}

void SensorData::startSensorTwo(const Mission& mission) {
    std::cout << "[SensorData] Starting Sensor for mission: "
                << mission.name << std::endl;

    Message msg;
    msg.topic = "sensor.target.detected";
    msg.source = "SensorData";

    // Plane
    msg.payload = mission.name + ":Plane";
    messaging_.publish(msg);
    // Ship
    msg.payload = mission.name + ":Ship";
    messaging_.publish(msg);
    // Missile
    msg.payload = mission.name + ":Missile";
    messaging_.publish(msg);
}


void SensorData::startSensor(const Mission& mission) {
    std::cout << "[SensorData] Starting Sensor for mission" << std::endl;

    for (const auto& [type, count] : mission.targetCounts) {
        for (int i = 0; i < count; i++) {
            Message msg;
            msg.topic = "sensor.target.detected";
            msg.payload = std::to_string(static_cast<int>(type));
            msg.source = "SensorData";
            messaging_.publish(msg);
        }

    }
}
