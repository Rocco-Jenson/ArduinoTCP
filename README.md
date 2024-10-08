# Arduino TCP

This project demonstrates how to connect two Arduino devices using TCP (Transmission Control Protocol) to communicate and play pre-selected audio messages on each other through an MP3 player module and speaker system. The messages are stored on a microSD card and are triggered using three buttons, with each button playing a different audio message.

### Functionality
- Each Arduino has three buttons, and each button is linked to a different pre-recorded message stored on the microSD card of the MP3 player module.
- When a button is pressed on one Arduino, it sends a message over the TCP connection to the other Arduino.
- The receiving Arduino then plays the corresponding audio file on the MP3 player module through the speaker.

## System Architecture

1. **Arduino 1**:
   - Listens for button presses (Button 1, Button 2, Button 3).
   - When a button is pressed, it sends a TCP message to Arduino 2 with the corresponding button ID.
   
2. **Arduino 2**:
   - Receives the TCP message from Arduino 1.
   - Plays the associated MP3 file (pre-loaded on the microSD card) based on the button ID received.
   
3. **Vice Versa**:
   - The same functionality is implemented for Arduino 2, where it sends a TCP message to Arduino 1, and Arduino 1 plays the associated audio file.
