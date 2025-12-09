#pragma once

#include "io/IO.h"

char splitCommand(char* str);
void processSetCommand(char*);

void processCommands() {
    if (io->isCommandAvailable()){
        char* input_command = io->getCommand();
        if (input_command == nullptr || strlen(input_command) == 0) {
            io->debug("Received NULL command");
            return;
        }
        io->debug("Command: %s", input_command);
        char command_type = splitCommand(input_command);
        if (command_type == '?') {
            if (strlen(input_command) == 0) {
                dumpState();
            }
        }
        else if (command_type=='=') {
            processSetCommand(input_command);
        }
    }
}

void processSetCommand(char* input_command) {
    if (strncmp(input_command, "RA",2) == 0) {
        if (strlen(input_command) > 2) {
            uint8_t ra = atoi(input_command+2);
            io->debug("Set RA=%d", ra);
            if (ra == 0) {
                setRemoteAlert(0);
            } else if (ra == 1) {
                setRemoteAlert(1);
            } else {
                io->debug("Invalid RA value: %d", ra);
            }
        } else {
            io->debug("Unrecognized RA command: %s", input_command);
        }
    } else if (strncmp(input_command, "RC",2) == 0) {
        if (strlen(input_command) > 2) {
            uint8_t rc = atoi(input_command+2);
            io->debug("Set RC=%d", rc);
            if (rc == 0) {
                setRemoteClose(0);
            } else if (rc == 1) {
                setRemoteClose(1);
            } else {
                io->debug("Invalid RC value: %d", rc);
            }
        } else {
            io->debug("Unrecognized RC command: %s", input_command);
        }
    } else {
        io->debug("Unknown command: %s", input_command);
    }
}

char splitCommand(char* str) {
    const char res = str[0];
    const int len = strlen(str);
    for (int i = 0; i < len; i++) {
        str[i] = str[i + 1];
    }
    return res;
}