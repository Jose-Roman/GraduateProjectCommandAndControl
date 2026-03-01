// Functions
//using Callback = std::function<void(Message &)>;
//Messaging() = default;
//~Messaging() = default;
//void publish(Message& msg);
//void subscribe(const std::string& topic, Callback cb);
//int getTimestamp();

#include <pybind11/pybind11.h>
#include <pybind11/functional.h>

#include "Messaging.h"

namespace py = pybind11;

PYBIND11_MODULE(messaging_py, m) {

    m.doc() = "Python bindings for Messaging system";

    //--------------------------------------------------
    // Message Struct
    //--------------------------------------------------
    py::class_<Message>(m, "Message")
        .def(py::init<>())

        .def_readwrite("topic", &Message::topic)
        .def_readwrite("payload", &Message::payload)
        .def_readwrite("timestamp", &Message::timestamp)
        .def_readwrite("messageId", &Message::messageId)
        .def_readwrite("source", &Message::source);

    //--------------------------------------------------
    // Messaging Class
    //--------------------------------------------------
    py::class_<Messaging>(m, "Messaging")

        .def(py::init<>())

        //--------------------------------------------------
        // Publish
        //--------------------------------------------------
        .def("publish",
            [](Messaging& self, Message& msg) {
                self.publish(msg);
            })

        //--------------------------------------------------
        // Subscribe
        //--------------------------------------------------
        .def("subscribe",
            [](Messaging& self,
               const std::string& topic,
               py::function pyCallback)
            {
                self.subscribe(topic,
                    [pyCallback](Message& msg)
                    {
                        pyCallback(msg);
                    });
            });
}