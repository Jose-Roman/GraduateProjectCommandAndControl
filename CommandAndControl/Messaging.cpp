//
// Created by Jose Roman  on 12/22/25.
//

#include "Messaging.h"
#include <iostream>
#include <chrono>

void Messaging::publish(const std::string& topic,
                        const std::string& payload,
                        const std:: string& source) {
    Message msg;
    msg.messageId = ++messageCounter_;
    msg.timestamp = getTimestamp();
    msg.topic = topic;
    msg.payload = payload;
    msg.source = source;

    // Log Message
    std::cout << "[Messaging::publish] "
                << "ID = " << msg.messageId << " "
                << "[" << msg.topic << "] "
                << "from " << msg.source << " "
                << "| payload: " << msg.payload
                << std::endl;

    // Callback
    auto it = subscribers_.find(topic);
    if (it != subscribers_.end()) {
        for (const auto& callback : it->second) {
            callback(msg);
        }
    }
}


void Messaging::subscribe(const std::string &topic, Callback cb) {
    subscribers_[topic].push_back(cb);

    std::cout << "[Messaging::subscribe] Subscribed to topic:" << topic << std::endl;
}

int Messaging::getTimestamp() {
    return static_cast<int>(
        std::chrono::system_clock::now().time_since_epoch().count() / 1000000000);
}
