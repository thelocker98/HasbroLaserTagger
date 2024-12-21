#include <IRsend.h>

class IRPayload {
public:
    IRPayload(int pin);
    ~IRPayload();

    void begin();
    void sendPayload(bool isShot, int team, bool successfulHit, bool shieldOn);

private:
    struct PayloadData {
        int size;
        uint16_t* payload;
    };

    IRsend irsend;
    PayloadData generatePayload(bool isShot, int team, bool successfulHit, bool shieldOn);
};
