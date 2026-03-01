// Functions
// explicit SensorData(Messaging& messaging);
// void initialize();
// SensorReading readSensor() const;
// void publishSensorData();
// void startSensor(const Mission& mission);

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "SensorData.h"
#include "Messaging.h"
#include "MissionPlanner.h"
#include "Types.h"

namespace py = pybind11;

PYBIND11_MODULE(sensor_data_py, m) {

    m.doc() = "Python bindings for SensorData";

    //-----------------------------------------
    // SensorReading Struct
    //-----------------------------------------
    py::class_<SensorReading>(m, "SensorReading")
        .def(py::init<>())

        .def_readwrite("sensorName", &SensorReading::sensorName)
        .def_readwrite("value", &SensorReading::value);

    //-----------------------------------------
    // Mission Struct
    //-----------------------------------------
    py::class_<Mission>(m, "Mission")
        .def(py::init<>())

        .def_readwrite("area", &Mission::area)
        .def_readwrite("name", &Mission::name)
        .def_readwrite("targetCounts", &Mission::targetCounts)
        .def_readwrite("scenarioDuration", &Mission::scenarioDuration);

    //-----------------------------------------
    // SensorData Class
    //-----------------------------------------
    py::class_<SensorData>(m, "SensorData")

        .def(py::init<Messaging&>())

        .def("initialize", &SensorData::initialize)

        .def("readSensor", &SensorData::readSensor)

        .def("publishSensorData", &SensorData::publishSensorData)

        .def("startSensor", &SensorData::startSensor);
}