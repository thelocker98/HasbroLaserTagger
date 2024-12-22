#include "IRHasbroTag.h"

// set max length of ir packet. for Hasbro Lazzer taggers leave it at 30
#define MAX_RAW_DATA 30

// tag(irsend_pin, irrecv_pin);
IRHasbroTag tag(23, 18); // Create an instance of IRHasbroTag 

uint16_t rawDataArray[MAX_RAW_DATA]; // Array to store received raw data

void setup() {
  Serial.begin(115200);
  tag.begin(); // Initialize the IRHasbroTag
  Serial.println("IRHasbroTag ready to receive data.");
}

void loop() {
  // Attempt to read raw data from the IR receiver
  int dataSize = tag.getPayload(rawDataArray, MAX_RAW_DATA);

  if (dataSize > 0) {
    // Parse the raw data to interpret the shot details
    IRHasbroTag::IRData shotData = tag.readShotData(rawDataArray, dataSize);

    // Display parsed shot data
    if (shotData.team != -1) {

      // Display parsed shot data
      Serial.print("Shot Detected: ");
      Serial.println(shotData.isShot ? "Yes" : "No");

      Serial.print("Team: ");
      Serial.println(shotData.team);

      Serial.print("Successful Hit: ");
      Serial.println(shotData.successfulHit ? "Yes" : "No");

      Serial.print("Shield On: ");
      Serial.println(shotData.shieldOn ? "Yes" : "No");

      Serial.print("MegaShot: ");
      Serial.println(shotData.megaShot ? "Yes" : "No");

      Serial.println();


    }
    delay(100); // Add a small delay to prevent spamming the Serial Monitor
  }
}