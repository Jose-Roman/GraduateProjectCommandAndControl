//
// Created by Jose Roman  on 12/22/25.
//

#ifndef COMMANDEXECUTOR_H
#define COMMANDEXECUTOR_H
#include <string>
#include "Messaging.h"


class CommandExecutor {
    public:
        explicit  CommandExecutor(Messaging& messaging);

        void initialize();
        void executeCommand(const std::string& command);

    private:
        Messaging& messaging_;

        void onCommandMessage(const Message& msg);

};


#endif //COMMANDEXECUTOR_H