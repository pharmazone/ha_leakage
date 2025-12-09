#pragma once
#include <EEPROM.h>
#include "config.h"
#include "io/IO.h"

struct State {
  uint8_t open: 1;
  uint8_t sensing: 2;
  unsigned long imp_fun;
  unsigned long imp_inp;
  unsigned long last_imp_fun;
  unsigned long last_imp_inp;
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
  io->output("State: open=%d, sensing=%d, imp_fun=%lu, last_imp_fun=%lu, imp_inp=%lu, last_imp_inp=%lu, remote_alert=%d, remote_close=%d",
            state.open, state.sensing,
            state.imp_fun, (t > state.last_imp_fun) ? t - state.last_imp_fun : t,
            state.imp_inp, (t > state.last_imp_inp) ? t - state.last_imp_inp : t,
            state.remote_alert, state.remote_close);
  }