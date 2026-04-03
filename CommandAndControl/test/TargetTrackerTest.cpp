//
// Created by Jose Roman  on 1/29/26.
//

#include <gtest/gtest.h>

#include "TargetTracker.h"
#include "Geography.h"
#include "Messaging.h"

class TargetTrackerTest : public ::testing::Test {
protected:
    Messaging msg;
    Geography geo;

    TargetTracker targetTracker;

    TargetTrackerTest() : targetTracker(msg, geo) {}

};

TEST_F(TargetTrackerTest, TrackTargetCreatesValidTarget)
{
    Target t = targetTracker.trackTarget(MissionArea::LosAngeles,
                                         TargetType::Plane);

    EXPECT_GT(t.id, 0);
    EXPECT_EQ(t.type, TargetType::Plane);
}

TEST_F(TargetTrackerTest, UpdateTrackIncrementsUpdateCounter)
{
    Target t = targetTracker.trackTarget(MissionArea::LosAngeles,
                                         TargetType::Plane);

    targetTracker.addActiveTrack(t);

    targetTracker.updateTrack(t.id, 30, MissionArea::LosAngeles);  // 30 seconds

    Target updated = targetTracker.getActiveTrack(t.id);

    EXPECT_GT(updated.numOfUpdates, 0);
}

TEST_F(TargetTrackerTest, UpdateTrackChangesPosition)
{
    Target t = targetTracker.trackTarget(MissionArea::LosAngeles,
                                         TargetType::Plane);

    double latBefore = t.latitude;
    double lonBefore = t.longitude;

    targetTracker.addActiveTrack(t);

    targetTracker.updateTrack(t.id, 30, MissionArea::LosAngeles);

    Target updated = targetTracker.getActiveTrack(t.id);

    EXPECT_TRUE(updated.latitude != latBefore ||
                updated.longitude != lonBefore);
}

TEST_F(TargetTrackerTest, UpdateTrack_OutOfBoundsTarget)
{
    // Create a valid target first
    Target t = targetTracker.trackTarget(MissionArea::LosAngeles,
                                         TargetType::Plane);

    // Force it OUTSIDE Los Angeles bounds
    // LA bounds: {33.7, 34.4, -118.9, -117.6}
    t.latitude = 35.0;     // outside max latitude
    t.longitude = -120.0;  // outside min longitude

    t.numOfUpdates = 0;

    targetTracker.addActiveTrack(t);

    // Run update
    targetTracker.updateTrack(t.id, 120, MissionArea::LosAngeles);

    Target updated = targetTracker.getActiveTrack(t.id);

    // Expect only 1 update
    EXPECT_EQ(updated.numOfUpdates, 1);
}