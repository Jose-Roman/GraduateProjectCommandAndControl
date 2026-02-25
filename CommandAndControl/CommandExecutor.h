//
// Created by Jose Roman  on 12/22/25.
//

#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <string>
#include "Messaging.h"
#include "TargetTracker.h"

class CommandExecutor {
    public:
        CommandExecutor(Messaging& messaging, TargetTracker& tracker);

        void initialize();
        void executeCommand(const std::string& command);
        void setScenarioDuration(int scenarioDuration);

    private:
        Messaging& messaging_;
        TargetTracker& tracker_;
        int missionDuration_;
        void onCommandReceived(const Message& msg) const;

};

#endif //COMMANDEXECUTOR_H