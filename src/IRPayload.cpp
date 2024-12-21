#include "IRPayload.h"

IRPayload::IRPayload(uint8_t sendPin) : irsend(sendPin) {}

IRPayload::~IRPayload() {}

void IRPayload::begin() {
    irsend.begin();
}

IRPayload::PayloadData IRPayload::generatePayload(bool isShot, int team, bool successfulHit, bool shieldOn) {
    IRPayload::PayloadData data;

    int bit1 = (team & 1) * 1000 + 1000;
    int bit2 = ((team >> 1) & 1) * 1000 + 1000;
    int shield = shieldOn * 1000 + 1000;
    int hit = successfulHit * 1000 + 1000;

    if (isShot) {
        data.payload = new uint16_t[17]{3000, 6000, 3000, 2000, 1000, 2000, 1000, 2000, 1000, 2000, bit2, 2000, bit1, 2000, 1000, 2000, 1000};
        data.size = 17;
    } else {
        data.payload = new uint16_t[21]{3000, 6000, 6000, 2000, hit, 2000, shield, 2000, 2000, 2000, 2000, 2000, 1000, 2000, 1000, 2000, 1000, 2000, bit2, 2000, bit1};
        data.size = 21;
    }

    return data;
}

void IRPayload::sendPayload(IRPayload::PayloadData data) {
    irsend.sendRaw(data.payload, data.size, 38);
    delete[] data.payload; // Free allocated memory
}
