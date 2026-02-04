//
// Created by Jose Roman  on 2/3/26.
//

#include <gtest/gtest.h>
#include "MissionPlanner.h"
#include "SensorData.h"
#include "Geography.h"

class MissionPlannerTest : public ::testing::Test {
protected:
    Messaging messaging;
    Geography geo;
    TargetTracker tracker{messaging, geo};
    MissionPlanner planner{messaging, tracker};

    void SetUp() override {
        planner.initialize();
    }
};

TEST_F(MissionPlannerTest, TargetUpdatePublishesCommandExecute) {
    bool commandPublished = false;

    messaging.subscribe("command.execute",
        [&](const Message& msg) {
            commandPublished = true;
        });

    Message targetMsg;
    targetMsg.topic = "target.update";
    targetMsg.payload = "1,34.0,-118.0,1000,300";
    targetMsg.source = "Test";

    messaging.publish(targetMsg);

    EXPECT_TRUE(commandPublished);
}

TEST_F(MissionPlannerTest, SetMissionGeneratesTargetsAndPublishesCommands) {
    int commandCount = 0;

    messaging.subscribe("command.execute",
        [&](const Message&) {
            commandCount++;
        });

    Mission mission;
    mission.name = "TestMission";
    mission.area = MissionArea::Miami;
    mission.targetCounts[TargetType::Plane] = 2;

    planner.setMission(mission);

    EXPECT_EQ(commandCount, 2);
}

TEST_F(MissionPlannerTest, PlanMissionPublishesSerializedTarget) {
    std::string payload;

    messaging.subscribe("command.execute",
        [&](const Message& msg) {
            payload = msg.payload;
        });

    Target target;
    target.id = 50;
    target.latitude = 40.0;
    target.longitude = -73.0;
    target.altitude = 10000;
    target.speed = 400;

    planner.planMission(target);

    EXPECT_FALSE(payload.empty());
}

