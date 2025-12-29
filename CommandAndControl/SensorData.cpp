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
    msg.topic = "SensorUpdate";
    msg.payload = reading.sensorName + " = " + std::to_string(reading.value);
    msg.source = "SensorData";

    // Publish message
    messaging_.publish(msg);
}