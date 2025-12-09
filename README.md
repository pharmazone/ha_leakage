Link to project https://u.easyeda.com/account/user/projects/person?folder=26a0db9e971f494a8bc3d32739867327


# Upload and monitoring at HA
## backup

`avrdude -p atmega328p -D -c arduino -b 57600 -P /dev/ttyUSB0 -U flash:r:backup.hex:i`

## Upload
`avrdude -p atmega328p -D -c arduino -b 57600 -P /dev/ttyUSB0 -U flash:w:20251209.hex:i`


## Monitor
`picocom -b 57600 -l --omap crlf --imap lfcrlf --echo --noreset /dev/ttyUSB0`