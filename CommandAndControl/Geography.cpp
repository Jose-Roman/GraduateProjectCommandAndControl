//
// Created by Jose Roman  on 1/3/26.
//

#include "Geography.h"
#include <random>

/**
 * Returns the geographic bounding box for a given mission area.
 *
 * This function defines the operational region for a mission by providing
 * minimum and maximum latitude and longitude values. These bounds are used
 * to constrain simulated target generation within realistic geographic limits.
 */

GeoBounds Geography::getGioBounds(MissionArea& area) {
    switch (area) {
        case MissionArea::LosAngeles:
            return {33.7,34.4, -118.9, -117.6};
        case MissionArea::Miami:
            return {25.3, 26.1, -80.9, -80.0};
        case MissionArea::NewYork:
            return {40.4, 41.0, -74.5, -73.6};
    }

    return {};
}

/**
 *  Returns kinematic constraints for a given target type.
 *
 * Provides realistic ranges for altitude and speed based on the type
 * of target being simulated (e.g., aircraft, ship, missile). These values
 * are used to generate plausible motion characteristics for targets.
 */
GeoKinematics Geography::getGioKinematics(TargetType& track) {
    if (track == TargetType::Plane) {
        return {5000, 40000, 200, 600};
    }
    else if (track == TargetType::Ship) {
        return {0, 0, 10, 40};
    }
    else {
        return {100, 50000, 200, 1000};
    }

}

// Random double value within [min, max]
double Geography::randomDouble(double min, double max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(rng);
}

/**
* Returns a fixed sensor location for a given mission area.
* Provides a representative geographic coordinate for a sensor within
* the mission region. These coordinates are used as the origin point
* for simulated sensor detections.
*/
sensorLocation Geography::getSensorLocation(MissionArea& area) {
    switch (area) {
        case MissionArea::LosAngeles:
            return {34.0522, -118.2437};  //Downtown LA
        case MissionArea::Miami:
            return {25.7617, -80.1918};   //Downtown Miami
        case MissionArea::NewYork:
            return {40.7128, -74.0060};   // Manhattan
        default:
            return {0,0};
    }
}


// Converts a string representation of a mission area into its enum value.
MissionArea Geography::parseMissionArea(const std::string& areaStr) {
    if (areaStr == "LosAngeles") return MissionArea::LosAngeles;
    if (areaStr == "NewYork")    return MissionArea::NewYork;
    if (areaStr == "Miami")      return MissionArea::Miami;

    throw std::runtime_error("Invalid MissionArea: " + areaStr);
}