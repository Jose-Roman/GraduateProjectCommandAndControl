#include <pybind11/pybind11.h>
#include <iostream>

namespace py = pybind11;

void helloWorld() {
    std::cout << "Hello from C++!" << std::endl;
}

PYBIND11_MODULE(command_system, m) {
    m.def("helloWorld", &helloWorld);
}