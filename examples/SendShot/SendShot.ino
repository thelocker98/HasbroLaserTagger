#include <IRPayload.h>

IRPayload irPayload(23); // Initialize with pin 23

void setup() {
    Serial.begin(115200);
    irPayload.begin();
}

void loop() {
    Serial.println("Sending a raw payload...");
    
    // Generate a payload with custom parameters
    IRPayload::PayloadData data = irPayload.generatePayload(false, 3, false, true);

    // Print payload size
    Serial.println("Payload Length: " + String(data.size));

    // Send the payload
    irPayload.sendPayload(data);

    delay(500); // Delay between transmissions
}
