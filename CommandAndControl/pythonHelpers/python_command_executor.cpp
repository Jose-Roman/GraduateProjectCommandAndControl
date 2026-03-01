//
// Created by Jose Roman  on 2/28/26.
//

//functions
//CommandExecutor(Messaging& messaging, TargetTracker& tracker);
//void initialize();
//void executeCommand(const std::string& command);
//void setScenarioDuration(int scenarioDuration);
//void onCommandReceived(const Message& msg) const;

#include <pybind11/pybind11.h>
#include "CommandExecutor.h"
#include "Messaging.h"
#include "TargetTracker.h"

namespace py = pybind11;

PYBIND11_MODULE(command_executor_py, m) {

    py::class_<CommandExecutor>(m, "CommandExecutor")
        .def(py::init<Messaging&, TargetTracker&>(),
             py::arg("messaging"),
             py::arg("tracker"))

        .def("initialize", &CommandExecutor::initialize)

        .def("execute_command", &CommandExecutor::executeCommand)

        .def("set_scenario_duration", &CommandExecutor::setScenarioDuration);
}