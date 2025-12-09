#pragma once

#define DEBOUNCE_TIME 50

#define INP A1
#define SENS_FUN A2
#define SENS_INP A3
#define FUN A4
#define CLOSE A5
#define OPEN A6
#define REMOTE_CLEAR A7

#define REMOTE_CLOSE 7
#define REMOTE_ALERT 8
#define OP_INP 11
#define OP_FUN 10
#define SENS_NC 6


#define SENSING_INP 0
#define SENSING_FUNC 1
#define SENSING_NC 2

void configurePins() {
    pinMode(INP, INPUT); // ?
    pinMode(SENS_FUN, INPUT); // PCINT
    pinMode(SENS_INP, INPUT); // PCINT
    pinMode(FUN, INPUT); // ?
    pinMode(CLOSE, INPUT); //PCINT
    pinMode(OPEN, INPUT); // analogRead
    pinMode(REMOTE_CLEAR, INPUT); // analogRead
    pinMode(REMOTE_CLOSE, OUTPUT);
    pinMode(REMOTE_ALERT, OUTPUT);
    pinMode(OP_INP, OUTPUT);
    pinMode(OP_FUN, OUTPUT);
    pinMode(SENS_NC, OUTPUT);
}

#define REMOTE_CLOSE_ADDR 8
#define REMOTE_ALERT_ADDR 128
