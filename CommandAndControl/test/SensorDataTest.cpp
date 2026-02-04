//
// Created by Jose Roman  on 2/3/26.
//

#include <gtest/gtest.h>
#include "SensorData.h"
#include "Messaging.h"

class SensorDataTest : public ::testing::Test {
protected:
    Messaging messaging;
    SensorData sensor{messaging};
};

TEST_F(SensorDataTest, ReadSensorReturnsDefaultReading) {
    SensorReading reading = sensor.readSensor();

    EXPECT_EQ(reading.sensorName, "TEMP NAME");
    EXPECT_DOUBLE_EQ(reading.value, 60.0);
}

TEST_F(SensorDataTest, PublishSensorDataEmitsMessage) {
    bool called = false;
    Message received;

    messaging.subscribe("sensor.data",
        [&](Message& msg) {
            called = true;
            received = msg;
        });

    sensor.publishSensorData();

    EXPECT_TRUE(called);
    EXPECT_EQ(received.topic, "sensor.data");
    EXPECT_NE(received.payload.find("TEMP NAME"), std::string::npos);
}

TEST_F(SensorDataTest, StartSensorPublishesTargetCount) {
    Mission mission;
    mission.area = MissionArea::LosAngeles;
    mission.targetCounts[TargetType::Plane] = 2;
    mission.targetCounts[TargetType::Ship] = 1;

    int detectedCount = 0;

    messaging.subscribe("sensor.target.detected",
        [&](Message&) {
            detectedCount++;
        });

    sensor.startSensor(mission);

    // Expect 3 total messages
    EXPECT_EQ(detectedCount, 3);
}

TEST_F(SensorDataTest, StartSensorPayloadContainsArea) {
    Mission mission;
    mission.area = MissionArea::Miami;
    mission.targetCounts[TargetType::Plane] = 1;

    std::string payload;

    messaging.subscribe("sensor.target.detected",
        [&](Message& msg) {
            payload = msg.payload;
        });

    sensor.startSensor(mission);

    EXPECT_NE(payload.find("Miami"), std::string::npos);
}

