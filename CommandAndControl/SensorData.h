//
// Created by Jose Roman  on 12/22/25.
//

#ifndef SENSORDATA_H
#define SENSORDATA_H
#include "Messaging.h"
#include <string>

// Struct representing a sensor reading
struct SensorReading {
    std::string sensorName;
    double value;
};

class SensorData {
    public:
        // Constructor that makes reference to messaging system
        explicit SensorData(Messaging& messaging);

        // Initializes the sensor system abd prepares it to publish data
        void initialize();

        // Simulates reading data from a sensor
        // TODO: generate data that represents sensor activites
        SensorReading readSensor() const;

        // Publishes a sensor update message
        void publishSensorData();

    private:
        Messaging& messaging_;
};

#endif //SENSORDATA_H