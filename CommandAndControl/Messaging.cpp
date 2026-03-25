//
// Created by Jose Roman  on 12/22/25.
//

#include "Messaging.h"
#include <iostream>
#include <chrono>

/**
 * Publishes a message to all subscribers of a given topic.
 *
 * This function is the core of the messaging system. It assigns a unique
 * message ID and timestamp to the outgoing message, logs the message for
 * traceability, and then dispatches it to all registered subscribers
 * for the specified topic.
 *
 * The publish-subscribe mechanism enables loose coupling between system
 * components, allowing them to communicate without direct dependencies.
 */
void Messaging::publish(Message& msg) {
    msg.messageId = ++messageCounter_;
    msg.timestamp = getTimestamp();

    // Log Message
    std::cout << "[Messaging::publish] "
                << "ID = " << msg.messageId << " "
                << "[" << msg.topic << "] "
                << "from " << msg.source << " "
                << "| payload: " << msg.payload
                << std::endl;

    // Callback
    auto it = subscribers_.find(msg.topic);
    if (it != subscribers_.end()) {
        for (const auto& callback : it->second) {
            callback(msg);
        }
    }
}

/**
 * Subscribes a callback function to a specific topic.
 *
 * This function allows components to register interest in a particular
 * message topic. When a message with the matching topic is published,
 * the provided callback function will be invoked.
 *
 * Multiple subscribers can be registered to the same topic, enabling
 * broadcast-style communication across the system.
 *
 */
void Messaging::subscribe(const std::string &topic, Callback cb) {
    subscribers_[topic].push_back(cb);

    std::cout << "[Messaging::subscribe] Subscribed to topic:" << topic << std::endl;
}

/**
 * Generates a timestamp for messages.
 *
 * This timestamp is used to track when messages are published
 * and can assist in debugging, ordering events, or simulating
 * real-time behavior.
 *
 * @return Integer timestamp representing current time in seconds
 */
int Messaging::getTimestamp() {
    return static_cast<int>(
        std::chrono::system_clock::now().time_since_epoch().count() / 1000000000);
}
