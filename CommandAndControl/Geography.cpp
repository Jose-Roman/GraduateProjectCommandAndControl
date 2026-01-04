//
// Created by Jose Roman  on 1/3/26.
//

#include "Geography.h"
#include <random>

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

double Geography::randomDouble(double min, double max) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(rng);
}