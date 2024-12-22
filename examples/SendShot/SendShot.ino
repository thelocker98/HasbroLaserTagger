#include "IRHasbroTag.h"

// tag(irsend_pin, irrecv_pin);
IRHasbroTag tag(23, 18); // Create an instance of IRHasbroTag 


// variable to store ir payload
IRHasbroTag::PayloadData ir_payload;


void setup() {
  Serial.begin(115200);
  tag.begin(); // Initialize the IRHasbroTag
  Serial.println("IRHasbroTag ready to transmit data.");
}

void loop() {
  // Generate a mega shot that will take two lives
  ir_payload = tag.generatePayload(true, 0, false, false, true);
  tag.sendPayload(ir_payload);

  // wait to give the player a chance to escape
  delay(1000);
}