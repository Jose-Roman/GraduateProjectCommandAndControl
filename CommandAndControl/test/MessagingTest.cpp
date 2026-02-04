//
// Created by Jose Roman  on 2/3/26.
//

#include <gtest/gtest.h>
#include "Messaging.h"

class MessagingTest : public ::testing::Test {
protected:
    Messaging messaging;
};

TEST_F(MessagingTest, PublishCallsSubscriber) {
    bool callbackCalled = false;

    messaging.subscribe("test.topic",
        [&](Message& msg) {
            callbackCalled = true;
        });

    Message msg;
    msg.topic = "test.topic";
    msg.payload = "hello";
    msg.source = "unit";

    messaging.publish(msg);

    EXPECT_TRUE(callbackCalled);
}

TEST_F(MessagingTest, PublishIncrementsMessageId) {
    Message msg1;
    msg1.topic = "a";

    Message msg2;
    msg2.topic = "a";

    messaging.publish(msg1);
    messaging.publish(msg2);

    EXPECT_EQ(msg1.messageId + 1, msg2.messageId);
}

TEST_F(MessagingTest, PublishSetsTimestamp) {
    Message msg;
    msg.topic = "time";

    messaging.publish(msg);

    EXPECT_GT(msg.timestamp, 0);
}

TEST_F(MessagingTest, OnlyMatchingTopicReceivesMessage) {
    bool calledA = false;
    bool calledB = false;

    messaging.subscribe("topicA",
        [&](Message&) {
            calledA = true;
        });

    messaging.subscribe("topicB",
        [&](Message&) {
            calledB = true;
        });

    Message msg;
    msg.topic = "topicA";

    messaging.publish(msg);

    EXPECT_TRUE(calledA);
    EXPECT_FALSE(calledB);
}

