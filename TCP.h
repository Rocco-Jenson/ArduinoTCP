#ifndef TCP_H
#define TCP_H

#include "Arduino.h"
#include <ezButton.h>

// Check If Buttons Are Pressed, Send Correct Message, And Flush Stream
void isPressed_write_flush(ezButton& button_1, ezButton& button_2, ezButton& button_3, WiFiClient& client, DFRobotDFPlayerMini& mp3) {
    char command = 0;

    if (button_1.isPressed()) {
        command = '1';
        Serial.println("Button 1 Pressed");
    }

    if (button_2.isPressed()) {
        command = '2';
        Serial.println("Button 2 Pressed");
    }

    if (button_3.isPressed()) {
        command = '3';
        Serial.println("Button 3 Pressed");
    }

    if (command != 0) {
        // Send command to the other device (client or server)
        client.write(command);
        client.flush();

        // Play audio locally
        switch (command) {
            case '1':
                mp3.playMp3Folder(1);
                break;
            case '2':
                mp3.playMp3Folder(2);
                break;
            case '3':
                mp3.playMp3Folder(3);
                break;
            default:
                break;
        }

        if (mp3.available()) {
            printDetail(mp3.readType(), mp3.read());
            delay(250);
        }
    }
}

// Read If Client Connected, Parse Written Data, Output Message Audio Through Speaker
void read_parse_speak(WiFiClient& client, DFRobotDFPlayerMini& mp3) {
    if (client) {
        char command = client.read();

        Serial.println("Received command: ");
        Serial.print(command);
        Serial.println();

        switch (command) {
            case '1':
                mp3.playMp3Folder(1);
                break;
            case '2':
                mp3.playMp3Folder(2);
                break;
            case '3':
                mp3.playMp3Folder(3);
                break;
            default:
                break;
        }

        if (mp3.available()) {
            printDetail(mp3.readType(), mp3.read());
            delay(250);
        }
    }
}

#endif