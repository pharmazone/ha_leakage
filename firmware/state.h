#pragma once
#include <EEPROM.h>
#include "config.h"
#include "io/IO.h"

struct State {
  uint8_t open: 1;
  uint8_t sensing: 2;
  uint8_t imp_fun: 1;
  uint8_t imp_inp: 1;
  uint8_t remote_alert: 1;
  uint8_t remote_close: 1;
} state;

void initState() {
  state.open = analogRead(OPEN) > 1000 ? 1 : 0;
  state.sensing = digitalRead(SENS_FUN) ? SENSING_FUNC :
                  (digitalRead(SENS_INP) ? SENSING_INP : SENSING_NC);
  state.imp_fun = 0;
  state.imp_inp = 0;
  state.remote_alert = EEPROM.read(REMOTE_ALERT_ADDR);
  digitalWrite(REMOTE_ALERT, state.remote_alert);
  state.remote_close = EEPROM.read(REMOTE_CLOSE_ADDR);
  digitalWrite(REMOTE_CLOSE, state.remote_close);
}

void setRemoteAlert(uint8_t value) {
  state.remote_alert = value;
  EEPROM.write(REMOTE_ALERT_ADDR, value);
  digitalWrite(REMOTE_ALERT, value);
}

void setRemoteClose(uint8_t value) {
  state.remote_close = value;
  EEPROM.write(REMOTE_CLOSE_ADDR, value);
  digitalWrite(REMOTE_CLOSE, value);
}

void dumpState(){
  io->debug("State: open=%d, sensing=%d, imp_fun=%d, imp_inp=%d, remote_alert=%d, remote_close=%d",
            state.open, state.sensing, state.imp_fun, state.imp_inp,
            state.remote_alert, state.remote_close);
  }