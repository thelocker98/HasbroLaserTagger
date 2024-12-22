#include "IRHasbroTag.h"

#define MAX_RAW_DATA 30

IRHasbroTag tag(23, 18); // Create an instance of IRHasbroTag

uint16_t rawDataArray[MAX_RAW_DATA]; // Array to store received raw data

// Variables to track hits for each team
int teamHits[4] = {0, 0, 0, 0}; // Index 0 for Team 0, Index 1 for Team 1, etc.

// Variable to track time
unsigned long lastTriggerTime = 0;
int team = 0;

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
      // increase counter
      if (shotData.team >= 0 && shotData.team < 4) { // Ensure valid team number (0-3)
        teamHits[shotData.team]++; // Increment hits for the respective team
      }

      // change team hit
      if(shotData.team != 0){
        if(shotData.team == 1)
          shotData.team = 3;
        else
          shotData.team = 1;
      }

      // generate and send payload
      ir_payload = tag.generatePayload(false, shotData.team, true, false, false);
      tag.sendPayload(ir_payload);
 
    }
    unsigned long currentTime = millis();

    // Check if 500 milliseconds have passed
    if (currentTime - lastTriggerTime >= 500) {
      lastTriggerTime = currentTime; // Update the last trigger time
      team++;
      if (team > 4)
        team=0;
      // Payload generation and sending
      IRHasbroTag::PayloadData ir_payload = tag.generatePayload(false, team, false, false, false);
      tag.sendPayload(ir_payload);

      // Print the hit counts for all teams
      for (int i = 0; i < 4; i++) {
        Serial.print("Team ");
        Serial.print(i);
        Serial.print(" Hits: ");
        Serial.println(teamHits[i]);
      }

      Serial.println();
    }
    delay(10); // Add a small delay to prevent spamming the Serial Monitor
  }
}