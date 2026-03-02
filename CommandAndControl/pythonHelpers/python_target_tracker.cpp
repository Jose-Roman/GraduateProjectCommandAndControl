// Functions
// explicit TargetTracker(Messaging& messaging, Geography& geography);
// void initialize();
// Target trackTarget(MissionArea area, TargetType track);
// void updateTrack(int targetId, int duration);
// int getUpdateInterval(TargetType type);
// std::string serializeTarget(const Target& target);
// Target deserializeTarget(const std::string& payload);
// void addActiveTrack(const Target& t)
// Target getActiveTrack(int id)

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "TargetTracker.h"
#include "Messaging.h"
#include "Geography.h"
#include "Types.h"

namespace py = pybind11;

PYBIND11_MODULE(target_tracker_py, m) {

    m.doc() = "Python bindings for TargetTracker";

    //-------------------------------------
    // Target Struct
    //-------------------------------------
    py::class_<Target>(m, "Target")
        .def(py::init<>())

        .def_readwrite("id", &Target::id)
        .def_readwrite("type", &Target::type)
        .def_readwrite("latitude", &Target::latitude)
        .def_readwrite("longitude", &Target::longitude)
        .def_readwrite("altitude", &Target::altitude)
        .def_readwrite("speed", &Target::speed)
        .def_readwrite("numOfUpdates", &Target::numOfUpdates);

    //-------------------------------------
    // TargetTracker Class
    //-------------------------------------
    py::class_<TargetTracker>(m, "TargetTracker")

        .def(py::init<Messaging&, Geography&>())

        .def("initialize", &TargetTracker::initialize)

        .def("trackTarget", &TargetTracker::trackTarget)

        .def("updateTrack", &TargetTracker::updateTrack)

        .def("getUpdateInterval", &TargetTracker::getUpdateInterval)

        .def("serializeTarget", &TargetTracker::serializeTarget)

        .def("deserializeTarget", &TargetTracker::deserializeTarget)

        .def("addActiveTrack", &TargetTracker::addActiveTrack)

        .def("getActiveTrack", &TargetTracker::getActiveTrack);
}