#include <ezButton.h>
#include "C:\Users\rocco\OneDrive\Desktop\Arduino_TCP\DF_PLAYER_MINI.h"
#include "C:\Users\rocco\OneDrive\Desktop\Arduino_TCP\WiFi_Setter.h"

const int speakerPin = 9; // Replace with the actual pin connected to the speaker

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // Generate a 1 kHz tone for 1 second
  tone(speakerPin, 1000, 1000);
  delay(1000); // Pause for 1 second

  // Generate a 2 kHz tone for 1 second
  tone(speakerPin, 2000, 1000);
  delay(1000); // Pause for 1 second
}