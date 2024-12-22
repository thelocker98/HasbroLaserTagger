#include <IRHasbroTag.h>

IRHasbroTag IRHasbroTag(23); // Initialize with pin 23

void setup() {
    Serial.begin(115200);
    IRHasbroTag.begin();
}

void loop() {
    Serial.println("Sending a raw payload...");
    
    // Generate a payload with custom parameters
    IRHasbroTag::PayloadData data = IRHasbroTag.generatePayload(false, 3, false, true);

    // Print payload size
    Serial.println("Payload Length: " + String(data.size));

    // Send the payload
    IRHasbroTag.sendPayload(data);

    delay(500); // Delay between transmissions
}
