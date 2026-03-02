#include <pybind11/pybind11.h>
#include "Types.h"

namespace py = pybind11;

PYBIND11_MODULE(types_py, m) {

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
}