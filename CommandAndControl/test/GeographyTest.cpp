//
// Created by Jose Roman  on 2/3/26.
//

#include <gtest/gtest.h>

#include "Geography.h"
#include "Types.h"

class GeographyTest : public ::testing::Test {
protected:
    Geography geo;
};

TEST_F(GeographyTest, GetGeoBoundsReturnsCorrectLosAngelesBounds) {
    MissionArea area = MissionArea::LosAngeles;

    GeoBounds bounds = geo.getGioBounds(area);

    EXPECT_DOUBLE_EQ(bounds.minLatitude, 33.7);
    EXPECT_DOUBLE_EQ(bounds.maxLatitude, 34.4);
    EXPECT_DOUBLE_EQ(bounds.minLongitude, -118.9);
    EXPECT_DOUBLE_EQ(bounds.maxLongitude, -117.6);
}

TEST_F(GeographyTest, GetGeoKinematicsReturnsPlaneValues) {
    TargetType type = TargetType::Plane;

    GeoKinematics kin = geo.getGioKinematics(type);

    EXPECT_EQ(kin.minAltitude, 5000);
    EXPECT_EQ(kin.maxAltitude, 40000);
    EXPECT_EQ(kin.minSpeed, 200);
    EXPECT_EQ(kin.maxSpeed, 600);
}

TEST_F(GeographyTest, RandomDoubleWithinBounds) {
    double min = 10.0;
    double max = 20.0;

    for (int i = 0; i < 100; ++i) {
        double value = geo.randomDouble(min, max);

        EXPECT_GE(value, min);
        EXPECT_LE(value, max);
    }
}

TEST_F(GeographyTest, GetSensorLocationMiami) {
    MissionArea area = MissionArea::Miami;

    sensorLocation loc = geo.getSensorLocation(area);

    EXPECT_DOUBLE_EQ(loc.latitude, 25.7617);
    EXPECT_DOUBLE_EQ(loc.longitude, -80.1918);
}

TEST_F(GeographyTest, ParseMissionAreaLosAngeles)
{
    MissionArea area = geo.parseMissionArea("LosAngeles");

    EXPECT_EQ(area, MissionArea::LosAngeles);
}

TEST_F(GeographyTest, ParseMissionAreaNewYork)
{
    MissionArea area = geo.parseMissionArea("NewYork");

    EXPECT_EQ(area, MissionArea::NewYork);
}

TEST_F(GeographyTest, ParseMissionAreaMiami)
{
    MissionArea area = geo.parseMissionArea("Miami");

    EXPECT_EQ(area, MissionArea::Miami);
}