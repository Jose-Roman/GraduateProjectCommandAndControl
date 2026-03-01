// functions
//GeoBounds getGioBounds(MissionArea& area);
//GeoKinematics getGioKinematics(TargetType& track);
//double randomDouble(double min, double max);
//static sensorLocation getSensorLocation(MissionArea& area);
//MissionArea parseMissionArea(const std::string& areaStr);

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Geography.h"
#include "MissionPlanner.h"
#include "TargetTracker.h"

namespace py = pybind11;

PYBIND11_MODULE(geography_py, m) {
    m.doc() = "Python bindings for Geography";

    //------------------------------------------------
    // Enums
    //------------------------------------------------
    py::enum_<MissionArea>(m, "MissionArea")
        .value("LosAngeles", MissionArea::LosAngeles)
        .value("NewYork",    MissionArea::NewYork)
        .value("Miami",      MissionArea::Miami)
        .export_values();

    py::enum_<TargetType>(m, "TargetType")
        .value("Plane",   TargetType::Plane)
        .value("Ship",    TargetType::Ship)
        .value("Missile", TargetType::Missile)
        .export_values();

    //------------------------------------------------
    // GeoBounds Struct
    //------------------------------------------------
    py::class_<GeoBounds>(m, "GeoBounds")
        .def(py::init<>())
        .def_readwrite("minLatitude", &GeoBounds::minLatitude)
        .def_readwrite("maxLatitude", &GeoBounds::maxLatitude)
        .def_readwrite("minLongitude", &GeoBounds::minLongitude)
        .def_readwrite("maxLongitude", &GeoBounds::maxLongitude);

    //------------------------------------------------
    // GeoKinematics Struct
    //------------------------------------------------
    py::class_<GeoKinematics>(m, "GeoKinematics")
        .def(py::init<>())
        .def_readwrite("minAltitude", &GeoKinematics::minAltitude)
        .def_readwrite("maxAltitude", &GeoKinematics::maxAltitude)
        .def_readwrite("minSpeed", &GeoKinematics::minSpeed)
        .def_readwrite("maxSpeed", &GeoKinematics::maxSpeed);

    //------------------------------------------------
    // Sensor Location Struct
    //------------------------------------------------
    py::class_<sensorLocation>(m, "SensorLocation")
        .def(py::init<>())
        .def_readwrite("latitude", &sensorLocation::latitude)
        .def_readwrite("longitude", &sensorLocation::longitude);

    //------------------------------------------------
    // Geography Class
    //------------------------------------------------
    py::class_<Geography>(m, "Geography")
        .def(py::init<>())

        .def("getGeoBounds", &Geography::getGioBounds)
        .def("getGeoKinematics", &Geography::getGioKinematics)
        .def("randomDouble", &Geography::randomDouble)
        .def("parseMissionArea", &Geography::parseMissionArea)

        .def_static("getSensorLocation", &Geography::getSensorLocation);
}