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
#include "Types.h"

namespace py = pybind11;

PYBIND11_MODULE(generate_scenario_py, m) {
    m.doc() = "Python bindings for GenerateScenario";

    //------------------------------------------------
    // GenerateScenario Class
    //------------------------------------------------
    py::class_<GenerateScenario>(m, "GenerateScenario")
        .def(py::init<SensorData&, Geography&, CommandExecutor&>())
        .def("setFullMission", &GenerateScenario::setFullMission)
        .def("startScenario", &GenerateScenario::startScenario);
}