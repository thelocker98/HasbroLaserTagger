#include "IRHasbroTag.h"

#define MAX_RAW_DATA 30

IRHasbroTag tag(23, 18); // Create an instance of IRHasbroTag

uint16_t rawDataArray[MAX_RAW_DATA]; // Array to store received raw data


// variable to store ir payload
IRHasbroTag::PayloadData ir_payload;

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
    if (shotData.team != -1 & shotData.isShot) {
      if(shotData.team != 0){
        if(shotData.team == 1)
          shotData.team = 3;
        else
          shotData.team = 1;
      }
        
          
      
      ir_payload = tag.generatePayload(false, shotData.team, true, true, false);
      tag.sendPayload(ir_payload);
 

      Serial.println();


    }
    delay(100); // Add a small delay to prevent spamming the Serial Monitor
  }
}
