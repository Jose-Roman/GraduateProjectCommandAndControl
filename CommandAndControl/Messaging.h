//
// Created by Jose Roman  on 12/22/25.
//

#ifndef MESSAGING_H
#define MESSAGING_H

#include <string>
#include <functional>
#include <unordered_map>
#include <vector>

struct Message {
    std::string topic;
    std::string payload;
    int timestamp;
    int messageId;
    std::string source;
};

class Messaging {
    public:
        using Callback = std::function<void(Message &)>;
        Messaging() = default;
        ~Messaging() = default;

        //Publish a message to all subscribers of the topic
    void publish(Message& msg);

        //Subscribe to a callback of a specific topic
        void subscribe(const std::string& topic, Callback cb);

    private:
        std::unordered_map<std::string, std::vector<Callback>> subscribers_;
        int messageCounter_ = 0;
        int getTimestamp();
};

#endif // MESSAGING_H