#ifndef IRHasbroTag_H
#define IRHasbroTag_H

#include <IRsend.h>
#include <IRrecv.h>
#include <Arduino.h>

class IRHasbroTag {
public:
    explicit IRHasbroTag(uint8_t sendPin, uint8_t recvPin); // Constructor
    ~IRHasbroTag();

    struct PayloadData {
        int size;
        uint16_t* payload;
    };

    struct IRData {
        bool isShot;
        int team;
        bool successfulHit;
        bool shieldOn;
        bool megaShot;
    };

    void begin();
    PayloadData generatePayload(bool isShot = true, int team = 0, bool successfulHit = false, bool shieldOn = false, bool megaShot = false);
    IRData readShotData(uint16_t *dataArray, int dataSize);
    void printShotData(uint16_t *dataArray);

    void sendPayload(PayloadData data);
    int getPayload(uint16_t *dataArray, int dataSize);

private:
    IRsend irsend;   // IRsend instance
    IRrecv irrecv;  // Pointer to IRrecv instance
};

#endif // IRHasbroTag_H
