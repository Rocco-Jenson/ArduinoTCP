// ARDUINO #2: TCP SERVER

#include "C:\Users\rocco\OneDrive\Desktop\Arduino_TCP\DF_PLAYER_MINI.h"
#include "C:\Users\rocco\OneDrive\Desktop\Arduino_TCP\WiFi_Setter.h"
#include "C:\Users\rocco\OneDrive\Desktop\Arduino_TCP\TCP.h"
#include <ezButton.h>

const char ssid[] {SSID_3050};
const char pass[] {PASSWORD_3050};

const int serverPort{4080};

const int BUTTON_PIN_1{7};
const int BUTTON_PIN_2{6};
const int BUTTON_PIN_3{5};
const int BUTTON_PIN_4{4};

const int VCC_OUTPUT{3};

bool vcc_status{true};
bool load_status{true};

DFRobotDFPlayerMini myDFPlayer;
ArduinoLEDMatrix matrix;

WiFiSetter setter(ssid, pass);
WiFiServer TCPserver(serverPort);

ezButton button_1(BUTTON_PIN_1);
ezButton button_2(BUTTON_PIN_2);
ezButton button_3(BUTTON_PIN_3);
ezButton button_4(BUTTON_PIN_4);

void setup() {
  pinMode(VCC_OUTPUT, OUTPUT);
  digitalWrite(VCC_OUTPUT, HIGH);

  Serial.begin(DEFAULT_BAUD);
  Serial.println(F("ARDUINO #2: TCP SERVER"));

  MP3_Serial.begin(MP3_DEFAULT_BAUD);

  if (!myDFPlayer.begin(MP3_Serial, /*isACK = */true, /*doReset = */true)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1. Please recheck the connection!"));
    Serial.println(F("2. Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }

  Serial.println(F("DFPlayer Mini online"));

  myDFPlayer.volume(30);

  button_1.setDebounceTime(50);
  button_2.setDebounceTime(50);
  button_3.setDebounceTime(50);
  button_4.setDebounceTime(50);

  WiFiSetter::begin_ArduinoLEDMatrix(matrix);

  setter.begin_wifi_connection_matrix(5, matrix);

  /*Change TCP_CLIENT SERVER ADDRESS On Server Init WiFi.localIP();*/
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());
  Serial.println(F("-> Please update the serverAddress in Arduino #1 code"));

  TCPserver.begin();
}

void loop() {
  button_1.loop();
  button_2.loop();
  button_3.loop();
  button_4.loop();

  WiFiClient client = TCPserver.available();

  if (button_4.isPressed()) {
    bool t = vcc_status;
    vcc_status = !t;
    Serial.println(F("Button 4 Pressed"));
  }

  if (vcc_status) {
    if (load_status) {
      matrix.loadFrame(*MATRIX_ON);
    }

    load_status = false;

    digitalWrite(VCC_OUTPUT, HIGH);

    if (client.connected()) {
      isPressed_write_flush(button_1, button_2, button_3, client, myDFPlayer);
      read_parse_speak(client, myDFPlayer);
    } else {
      client.stop();
    }

  } else {
    load_status = true;

    matrix.loadFrame(*MATRIX_OFF);

    digitalWrite(VCC_OUTPUT, LOW);
  }
}