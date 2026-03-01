//
// Created by Jose Roman  on 2/28/26.
//

// functions

//explicit GenerateScenario(SensorData& sensor, Geography& geography, CommandExecutor& commandExecutor);
//void setFullMission(Mission newMission);
//void startScenario();

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "GenerateScenario.h"
#include "MissionPlanner.h"
#include "SensorData.h"
#include "Geography.h"
#include "CommandExecutor.h"

namespace py = pybind11;

PYBIND11_MODULE(generate_scenario_py, m) {
    m.doc() = "Python bindings for GenerateScenario";

    //------------------------------------------------
    // MissionArea Enum
    //------------------------------------------------
    py::enum_<MissionArea>(m, "MissionArea")
        .value("LosAngeles", MissionArea::LosAngeles)
        .value("Miami", MissionArea::Miami)
        .value("NewYork", MissionArea::NewYork)
        .export_values();

    //------------------------------------------------
    // TargetType Enum
    //------------------------------------------------
    py::enum_<TargetType>(m, "TargetType")
        .value("Plane", TargetType::Plane)
        .value("Ship", TargetType::Ship)
        .value("Missile", TargetType::Missile)
        .export_values();

    //------------------------------------------------
    // Mission Struct
    //------------------------------------------------
    py::class_<Mission>(m, "Mission")
        .def(py::init<>())
        .def_readwrite("area", &Mission::area)
        .def_readwrite("name", &Mission::name)
        .def_readwrite("scenarioDuration", &Mission::scenarioDuration)
        .def_readwrite("targetCounts", &Mission::targetCounts);

    //------------------------------------------------
    // GenerateScenario Class
    //------------------------------------------------
    py::class_<GenerateScenario>(m, "GenerateScenario")
        .def(py::init<SensorData&, Geography&, CommandExecutor&>())
        .def("setFullMission", &GenerateScenario::setFullMission)
        .def("startScenario", &GenerateScenario::startScenario);
}