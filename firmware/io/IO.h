#pragma once
#include <stdarg.h>
#include "CommandStream.h"

class IO;
IO *io;

#define BAUDRATE 57600

#define OUTPUT_DEBUG "# "
#define OUTPUT_VALUE "="
#define OUTPUT_END "\n"

#define INPUT_BUFFER_SIZE 64
#define INPUT_TERMINATOR '\n'
#define INPUT_COMMAND_TIMEOUT 3000


//const char row[] PROGMEM = {"Row: %d %d"};

class IO{
    va_list ap;
public:
    IO(){
        Serial.begin(BAUDRATE);
        serialstdout.put = serial_putchar;
        serialstdout.flags = _FDEV_SETUP_WRITE;
        stdout = &serialstdout;
//        debug("%s", "sdfsdfsfS");
//        debug_P(row, 30, 20);
        input= new CommandStream<INPUT_BUFFER_SIZE>(&Serial, INPUT_TERMINATOR, INPUT_COMMAND_TIMEOUT);
    }

    void setDebug(bool debug){
        isDebug = debug;
    }

    bool isCommandAvailable(){
        return input->hasCommand();
    }

    char* getCommand(){
        return input->getCommand();
    }

    static int serial_putchar(char c, FILE *stream) {
        Serial.write(c);
        return 0;
    }

    void debug(const char *__fmt, ...){
        if (!isDebug) return;
        printf(OUTPUT_DEBUG);
        va_start(ap, __fmt);
        vprintf( __fmt, ap);
        va_end(ap);
        printf(OUTPUT_END);
    };

    void debug_P(const char *__fmt, ...){
        if (!isDebug) return;
        printf(OUTPUT_DEBUG);
        va_start(ap, __fmt);
        vfprintf_P(&serialstdout,  __fmt, ap);
        va_end(ap);
        printf(OUTPUT_END);
    };

    void output(const int value){
        printf(OUTPUT_VALUE);
        printf("%d", value);
        printf(OUTPUT_END);
    };

    void output(const char *value){
        printf(OUTPUT_VALUE);
        printf("%s", value);
        printf(OUTPUT_END);
    };

    void output(const double value){
        printf(OUTPUT_VALUE);
        printf("%f", value);
        printf(OUTPUT_END);
    };

    void output(const char *__fmt, ...){
        printf(OUTPUT_VALUE);
        va_start(ap, __fmt);
        vprintf( __fmt, ap);
        va_end(ap);
        printf(OUTPUT_END);
    };

    FILE serialstdout;
    CommandStream<INPUT_BUFFER_SIZE>* input;// = CommandStream<50>( &Serial, '\n');
    bool hasCommandFlag = false;
    bool isDebug = true;
};
