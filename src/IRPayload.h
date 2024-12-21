#ifndef IRPAYLOAD_H
#define IRPAYLOAD_H

#include <IRsend.h>
#include <Arduino.h>

class IRPayload {
public:
    explicit IRPayload(uint8_t sendPin); // Constructor
    ~IRPayload();

    struct PayloadData {
        int size;
        uint16_t* payload;
    };

    void begin();
    PayloadData generatePayload(bool isShot = true, int team = 0, bool successfulHit = false, bool shieldOn = false);
    void sendPayload(PayloadData data);

private:
    IRsend irsend; // IRsend instance
};

#endif // IRPAYLOAD_H
