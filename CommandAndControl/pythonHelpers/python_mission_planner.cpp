// Functions
// explicit MissionPlanner(Messaging& messaging, TargetTracker& tracker);
// void initialize();
//void setMission(const Mission& mission);
// void planMission(Target& track);

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "MissionPlanner.h"
#include "Messaging.h"
#include "TargetTracker.h"
#include "Types.h"

namespace py = pybind11;

PYBIND11_MODULE(mission_planner_py, m) {

    m.doc() = "Python bindings for MissionPlanner";

    //--------------------------------------------------
    // Enums
    //--------------------------------------------------

    py::enum_<MissionArea>(m, "MissionArea")
        .value("LosAngeles", MissionArea::LosAngeles)
        .value("NewYork", MissionArea::NewYork)
        .value("Miami", MissionArea::Miami)
        .export_values();

    py::enum_<TargetType>(m, "TargetType")
        .value("Plane", TargetType::Plane)
        .value("Ship", TargetType::Ship)
        .value("Missile", TargetType::Missile)
        .export_values();

    //--------------------------------------------------
    // Mission Struct
    //--------------------------------------------------

    py::class_<Mission>(m, "Mission")

        .def(py::init<>())

        .def_readwrite("area", &Mission::area)
        .def_readwrite("name", &Mission::name)
        .def_readwrite("targetCounts", &Mission::targetCounts)
        .def_readwrite("scenarioDuration", &Mission::scenarioDuration);

    //--------------------------------------------------
    // MissionPlanner Class
    //--------------------------------------------------

    py::class_<MissionPlanner>(m, "MissionPlanner")

        .def(py::init<Messaging&, TargetTracker&>(),
             py::arg("messaging"),
             py::arg("tracker"))

        .def("initialize", &MissionPlanner::initialize)

        .def("setMission", &MissionPlanner::setMission);
}