#ifndef __THE_ANSWER_H__
#define __THE_ANSWER_H__

#include <stdint.h>
#include "mbed.h"

class Blinker {
public:
    Blinker(DigitalOut & led, uint16_t times) : led(led), times_left(times) {}

    void start() {
        ticker.attach(this, &Blinker::blink, 0.2f);
    }

private:
    void blink() {
        led = !led;
        if (--times_left == 0) {
            ticker.detach();
        }
    }

    DigitalOut & led;
    uint16_t times_left;
    Ticker ticker;
};

class TheAnswer {
public:
    uint8_t give() { return 42; }

    void blink42times(DigitalOut & led) {
        Blinker* blinker = new Blinker(led, 42);
        blinker->start();
    }
};

#endif
