//
// Created by Jose Roman  on 2/1/26.
//

#include <gtest/gtest.h>

#include "GenerateScenario.h"
#include "Messaging.h"
#include "SensorData.h"
#include "Geography.h"
#include "TargetTracker.h"
#include "CommandExecutor.h"

class GenerateScenarioTest : public ::testing::Test {
protected:
    Messaging msg;
    Geography geo;
    TargetTracker tracker{msg, geo};
    SensorData sensor{msg};
    CommandExecutor executor{msg, tracker};

    GenerateScenario scenario{sensor, geo, executor};

    Mission mission;

    void SetUp() override {
        mission.name = "Los Angeles";
        mission.area = MissionArea::LosAngeles;
        mission.scenarioDuration = 60;

        mission.targetCounts[TargetType::Plane] = 2;
    }
};

TEST_F(GenerateScenarioTest, SetFullMissionDoesNotThrow) {
    EXPECT_NO_THROW(scenario.setFullMission(mission));
}

TEST_F(GenerateScenarioTest, StartScenarioDoesNotThrow) {
    scenario.setFullMission(mission);

    EXPECT_NO_THROW(scenario.startScenario());
}

TEST_F(GenerateScenarioTest, FullScenarioPipelineRuns) {
    scenario.setFullMission(mission);

    EXPECT_NO_THROW({
        scenario.startScenario();
    });
}
