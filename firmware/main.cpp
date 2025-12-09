#include <Arduino.h>
unsigned long t;
#include "PinChangeInterrupt.h"
#include "config.h"
#include "state.h"
#include "io/IO.h"
#include "commands.h"

struct Event {
  uint8_t value;
  unsigned long t;
}
sensing_changed,
manual_changed,
inp_tick,
fun_tick;

unsigned long rct, inp_tick_prev=0, fun_tick_prev=0;


void onSensingChanged() {
  sensing_changed.value = 1;
  sensing_changed.t = t;
}
void onManualChanged() {
  manual_changed.value = 1;
  manual_changed.t = t;
}

void onInpTick() {
  inp_tick.value = 1;
  inp_tick.t = t;
}

void onFunTick() {
  fun_tick.value = 1;
  fun_tick.t = t;
}


void setup() {
  configurePins();

  attachPCINT(digitalPinToPCINT(SENS_FUN), onSensingChanged, CHANGE);
  attachPCINT(digitalPinToPCINT(SENS_INP), onSensingChanged, CHANGE);
  attachPCINT(digitalPinToPCINT(CLOSE), onManualChanged, CHANGE);
  attachPCINT(digitalPinToPCINT(INP), onInpTick, RISING);
  attachPCINT(digitalPinToPCINT(FUN), onFunTick, RISING);

  initState();
  io = new IO();
  io->debug("Setup completed");
  dumpState();
}

void processSensingChange() {
  if (!sensing_changed.value || t - sensing_changed.t < DEBOUNCE_TIME) return;
  sensing_changed.value = 0;
  uint8_t oldSensing = state.sensing;
  if (digitalRead(SENS_FUN)) {
    state.sensing = SENSING_FUNC;
    digitalWrite(SENS_NC, LOW);
  } else if (digitalRead(SENS_INP)) {
    state.sensing = SENSING_INP;
    digitalWrite(SENS_NC, LOW);
  } else {
    state.sensing = SENSING_NC;
    digitalWrite(SENS_NC, HIGH);
  }
  if (oldSensing != state.sensing) {
    io->output("SENSING=%d", state.sensing);
  }
}

void processManualChange() {
  if (!manual_changed.value || t - manual_changed.t < DEBOUNCE_TIME) return;
  manual_changed.value = 0;
  uint8_t prevOpen = state.open;
  if (digitalRead(CLOSE)) {
    state.open = 0;
  } else if (analogRead(OPEN)> 1000) {
    state.open = 1;
  } else {
    manual_changed.value = 1; // repeat the check
    io->debug("ERROR: Neither CLOSE nor OPEN is pressed");
  }
  if (prevOpen != state.open) {
    io->output("OPEN=%d", state.open);
  }
}

void processInputTick() {
  if (inp_tick.value) {
    digitalWrite(OP_INP, !digitalRead(OP_INP));
    inp_tick.value = 0;
    state.imp_inp = (inp_tick.t > inp_tick_prev)? inp_tick.t - inp_tick_prev : inp_tick.t;
    io->debug("INPUT_TICK=%lu;STATE_IMP_INP=%lu", inp_tick.t, state.imp_inp);
    inp_tick_prev = inp_tick.t;
    state.last_imp_inp = inp_tick.t;
  }
}

void processFunTick() {
  if (fun_tick.value) {
    digitalWrite(OP_FUN, !digitalRead(OP_FUN));
    fun_tick.value = 0;
    state.imp_fun = ( fun_tick.t > fun_tick_prev) ? fun_tick.t - fun_tick_prev : fun_tick.t;
    io->debug("FUNCTION_TICK=%lu;STATE_IMP_FUN=%lu", fun_tick.t, state.imp_fun);
    fun_tick_prev = fun_tick.t;
    state.last_imp_fun = fun_tick.t;
  }
}

void processRemoteClear() {
  if (!state.remote_alert && !state.remote_close) return;

  if ( analogRead(REMOTE_CLEAR) > 1000) {
    if (rct == 0) rct = t;
  }
  else rct=0;

  if (rct > 0 && t - rct > 1500) {
      setRemoteAlert(0);
      setRemoteClose(0);
      io->output("REMOTE_CLEAR=%d", 1);
  }
}
void loop() {
  t = millis();
  processSensingChange();
  processManualChange();
  processCommands();
  processInputTick();
  processFunTick();
  processRemoteClear();
}


