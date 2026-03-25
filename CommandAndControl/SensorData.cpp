//
// Created by Jose Roman  on 12/22/25.
//

#include "SensorData.h"
#include <iostream>

/**
 * Constructor for SensorData instance
 *
 * The SensorData component simulates a physical sensor system that generates
 * raw environmental or detection data. It acts as the entry point of the
 * command-and-control pipeline by publishing sensor observations to the
 * messaging system.
 */
SensorData::SensorData(Messaging &messaging) : messaging_(messaging){}

/**
 * Initializes the sensor system.
 *
 * Prepares the sensor component for operation. In a real-world system,
 * this could include hardware initialization, calibration, or network setup.
 * In this simulation, it simply logs that the sensor is ready.
 */
void SensorData::initialize() {
    std::cout << "[SensorData] Sensor initialized" << std::endl;
}

/**
 * Simulates retrieving data from a sensor.
 *
 * @return A SensorReading structure containing simulated sensor data
 */
SensorReading SensorData::readSensor() const {
    SensorReading reading;
    // TODO sensor name and value
    // default values for now
    reading.sensorName = "TEMP NAME";
    reading.value = 60.0;
    return reading;
}

/**
 * Publishes sensor data to the messaging system.
 *
 * Retrieves a simulated sensor reading and publishes it as a message
 * under the "sensor.data" topic. This allows downstream components
 * to process raw sensor information.
 */
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

/**
 * Alternative sensor startup method using string-based target types.
 */
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

/**
 * Starts the sensor simulation for a given mission.
 *
 * This function acts as the primary entry point for generating detection
 * events. Publishes a series of "sensor.target.detected" messages
 * based on the mission's target configuration.
 */
void SensorData::startSensor(const Mission& mission) {
    std::cout << "[SensorData] Starting Sensor for mission" << std::endl;
    std::string areaStr;
    switch (mission.area) {
        case MissionArea::LosAngeles:
            areaStr = "LosAngeles"; break;
        case MissionArea::Miami:
            areaStr = "Miami"; break;
        case MissionArea::NewYork:
            areaStr = "NewYork"; break;
    }

    for (const auto& [type, count] : mission.targetCounts) {
        for (int i = 0; i < count; i++) {
            Message msg;
            msg.topic = "sensor.target.detected";
            msg.payload = areaStr + ":" + std::to_string(static_cast<int>(type));
            messaging_.publish(msg);
        }

    }
}
