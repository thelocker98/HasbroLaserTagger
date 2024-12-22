#include "IRHasbroTag.h"
#include <IRsend.h>
#include <IRrecv.h> // Added include for IRrecv to decode signals

IRHasbroTag::IRHasbroTag(uint8_t sendPin) : irsend(sendPin), irrecv(nullptr) {} // Initialize irrecv to nullptr

IRHasbroTag::~IRHasbroTag() {
    // Free any dynamically allocated memory
    if (irrecv != nullptr) {
        delete irrecv;
    }
}

void IRHasbroTag::begin() {
    irsend.begin();
    irrecv = new IRrecv(18); // Set a default pin for receiving
    irrecv->enableIRIn();    // Start the receiver
}

IRHasbroTag::PayloadData IRHasbroTag::generatePayload(bool isShot, int team, bool successfulHit, bool shieldOn, bool megaShot) {
    IRHasbroTag::PayloadData data;

    int bit1 = (team & 1) * 1000 + 1000;
    int bit2 = ((team >> 1) & 1) * 1000 + 1000;
    int shield = shieldOn ? 2000 : 1000;
    int hit = successfulHit ? 2000 : 1000;
    int mega = megaShot ? 2000 : 1000;


    if (isShot) {
        data.payload = new uint16_t[17]{3000, 6000, 3000, 2000, 1000, 2000, 1000, 2000, 1000, 2000, bit2, 2000, bit1, 2000, 1000, 2000, mega};
        data.size = 17;
    } else {
        data.payload = new uint16_t[21]{3000, 6000, 6000, 2000, hit, 2000, shield, 2000, 2000, 2000, 2000, 2000, 1000, 2000, 1000, 2000, 1000, 2000, bit2, 2000, bit1};
        data.size = 21;
    }

    return data;
}

void IRHasbroTag::sendPayload(IRHasbroTag::PayloadData data) {
    if (data.payload != nullptr) {
        irsend.sendRaw(data.payload, data.size, 38); // Ensure data is valid
        delete[] data.payload;                      // Free dynamically allocated memory
        data.payload = nullptr;                     // Prevent double deletion
    }
}

int IRHasbroTag::getPayload(uint16_t *dataArray) {
    if (irrecv == nullptr) {
        Serial.println("IRrecv instance not initialized.");
        return 0;
    }

    decode_results results;
    if (irrecv->decode(&results)) {
        irrecv->resume();
        
        int dataSize = (results.rawlen < 30) ? results.rawlen : 30;
        for (int i = 1; i < dataSize; i++) {
            dataArray[i-1] = results.rawbuf[i] * 2; // Scale raw buffer values
        }
        dataSize -= 1;

        return dataSize;
    }

    return 0; // No data received
}

IRHasbroTag::IRData IRHasbroTag::readShotData(uint16_t *dataArray, int dataSize) {
    IRData shotData = {false, -1, false, false, false}; // Default values
    if (dataSize == 17) {
        shotData.isShot = true;
        shotData.team = (dataArray[12] > 1500) + ((dataArray[10] > 1500) * 2);
        shotData.shieldOn = false;
        shotData.successfulHit = false;
        shotData.megaShot = (dataArray[16] > 1500);


        return shotData;
    }
    else if (dataSize == 21)
    {
        shotData.isShot = false;
        shotData.team = (dataArray[20] > 1500) + ((dataArray[18] > 1500) << 1);
        shotData.successfulHit = (dataArray[4] > 1500);
        shotData.shieldOn = (dataArray[6] > 1500);
        shotData.megaShot = false;

        
        return shotData;
    }
    else
    {
        return shotData;
    }

    return shotData;
}
