//
// Created by Jose Roman  on 1/3/26.
//

#ifndef GEOGRAPHY_H
#define GEOGRAPHY_H

#include "MissionPlanner.h"
#include "TargetTracker.h"
#include <Types.h>

#pragma once

struct GeoBounds {
    double minLatitude;
    double maxLatitude;
    double minLongitude;
    double maxLongitude;
};

struct GeoKinematics {
    double minAltitude;
    double maxAltitude;
    double minSpeed;
    double maxSpeed;
};

class Geography {
    public:
        GeoBounds getGioBounds(MissionArea& area);
        GeoKinematics getGioKinematics(TargetType& track);
        double randomDouble(double min, double max);
};


#endif // GEOGRAPHY_H