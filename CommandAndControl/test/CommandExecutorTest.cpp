//
// Created by Jose Roman  on 2/1/26.
//

#include <gtest/gtest.h>

#include "CommandExecutor.h"
#include "Messaging.h"
#include "TargetTracker.h"
#include "Geography.h"

class CommandExecutorTest : public ::testing::Test {
protected:
    Messaging messaging;
    Geography geography;
    TargetTracker tracker;
    CommandExecutor executor;

    CommandExecutorTest()
        : tracker(messaging, geography),
          executor(messaging, tracker)
    {}

    void SetUp() override {
        tracker.initialize();
        executor.initialize();
        executor.setScenarioDuration(30);
    }
};

TEST_F(CommandExecutorTest, PublishesCommandStatus)
{
    bool statusReceived = false;

    messaging.subscribe("command.status",
        [&](const Message&) {
            statusReceived = true;
        });

    Message cmd;
    cmd.topic = "command.execute";
    cmd.payload = "1 0 34.0 -118.0 10000 200 0";
    cmd.source = "test";

    messaging.publish(cmd);

    EXPECT_TRUE(statusReceived);
}

TEST_F(CommandExecutorTest, CommandTriggersTrackUpdate)
{
    Target t = tracker.trackTarget(MissionArea::LosAngeles,
                                   TargetType::Plane);

    tracker.addActiveTrack(t);

    Message cmd;
    cmd.topic = "command.execute";
    cmd.payload = tracker.serializeTarget(t);
    cmd.source = "test";

    messaging.publish(cmd);

    Target updated = tracker.getActiveTrack(t.id);

    EXPECT_GT(updated.numOfUpdates, 0);
}


TEST_F(CommandExecutorTest, LongerScenarioProducesMoreUpdates)
{
    Target t = tracker.trackTarget(MissionArea::LosAngeles,
                                   TargetType::Plane);

    tracker.addActiveTrack(t);

    executor.setScenarioDuration(60);

    Message cmd1;
    cmd1.topic = "command.execute";
    cmd1.payload = tracker.serializeTarget(t);

    messaging.publish(cmd1);

    int shortUpdates =
        tracker.getActiveTrack(t.id).numOfUpdates;

    // Reset
    t.numOfUpdates = 0;
    tracker.addActiveTrack(t);

    executor.setScenarioDuration(120);

    Message cmd2;
    cmd2.topic = "command.execute";
    cmd2.payload = tracker.serializeTarget(t);

    messaging.publish(cmd2);

    int longUpdates =
        tracker.getActiveTrack(t.id).numOfUpdates;

    EXPECT_GT(longUpdates, shortUpdates);
}