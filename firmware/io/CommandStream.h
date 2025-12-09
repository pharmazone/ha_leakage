#pragma once
// https://github.com/AlexGyver/tutorials/blob/master/processingSerial/updated/serialArduUpd/AsyncStream.h

template < uint16_t SIZE > class CommandStream {
public:
    CommandStream(Stream* port, char ter, uint16_t tout) {
        _port = port;
        _tout = tout;
        _ter = ter;
    }
    bool hasCommand() {
        if (_port -> available()) {
            if (!_parseF) {
                _parseF = true;
                for (uint8_t i = 0; i < _count; i++) buf[i] = '\0';
                _count = 0;
                _tmr = millis();
            }
            char ch = _port -> read();
            if (ch == _ter) {
                buf[_count] = '\0';
                _parseF = false;
                return true;
            } else if (_count < SIZE - 1) {
                buf[_count] = ch;
            }
            _count ++;
            _tmr = millis();
        }
        if (_parseF && millis() - _tmr >= _tout) {
            _parseF = false;
            return false; //true;
        }
        return false;
    }

    char* getCommand() {
        return buf;
    }

    char buf[SIZE];

private:
    Stream* _port;
    char _ter;
    uint8_t _count = 0;
    uint16_t _tout;
    uint32_t _tmr = 0;
    bool _parseF = false;
};