ARCHITECTURE  = avr
BOARD_TAG    = pro
BOARD_SUB    = 16MHzatmega328
#ARDUINO_PORT = /dev/cu.usbserial-1410
#ARDUINO_PORT = /dev/cu.usbserial-14510
ARDUINO_PORT = /dev/cu.usbserial-2110
#ARDUINO_PORT=/dev/tty.usbserial-110

ARDUINO_LIBS = Wire PinChangeInterrupt EEPROM
#ARDUINO_LIBS = EEPROM PCA95x5 Wire
USER_LIB_PATH = ./lib
AVR_TOOLS_DIR=/opt/homebrew/
#AVR_TOOLS_DIR = /usr/local
#ARDUINO_DIR	= /Applications/Arduino.app/Contents/Java
#AVRDUDE_OPTS = -V

MONITOR_PORT = $(ARDUINO_PORT)
MONITOR_BAUDRATE = 57600
#MONITOR_CMD = picocom --omap lfcrlf --imap lfcrlf -l --noreset --echo -b $(MONITOR_BAUDRATE) $(MONITOR_PORT) \#
MONITOR_CMD = picocom --omap crlf --imap lfcrlf -l --noreset --echo -b $(MONITOR_BAUDRATE) $(MONITOR_PORT) \#
# comment this string to see Arduino variables
ARDUINO_QUIET = 0

#include /usr/local/opt/arduino-mk/Arduino.mk
include /opt/homebrew/opt/arduino-mk/Arduino.mk
