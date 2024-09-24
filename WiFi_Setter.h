/*
* A Single Header .h File For
* The Arduino UNO R4 To Set Wifi Connections
* With or Without The LED MATRIX
*/

#ifndef WIFI_SETTER_H
#define WIFI_SETTER_H

#include "Arduino.h"
#include <WiFiS3.h>
#include "Arduino_LED_Matrix.h"

// Reconfigure PASSWORD, SSID & DEFAULT_BAUD On Change
#define SSID_3050 "TELUSWiFi3050"
#define PASSWORD_3050 "gUrmgEU47h"

#define SSID_2152 "TELUS2152"
#define PASSWORD_2152 "YFHGjEi4K6q2"

#define SSID_IZZY "PrettyWiFi"
#define PASSWORD_IZZY "4Awhiteguy!"

#define DEFAULT_BAUD 230400

class WiFiSetter {
public:
  const char* ssid;
  const char* password;

  // All WiFiSetter Functions Declared Here

  // Initialize WiFiSetter
  WiFiSetter(const char* ssid, const char* password) : ssid(ssid), password(password) {}

  // Begin Wifi Connection
  void begin_wifi_connection();

  // Begin Wifi Connection With LED Matrix
  void begin_wifi_connection_matrix(const unsigned short iters, ArduinoLEDMatrix& matrix);

  // Flash LED With Variable Iters
  static void flash_led(const unsigned short input_pin, const unsigned short iters);

  // Display A Loading Screen For A Var of iters Using The LED Matrix
  static void loading_screen(const unsigned short iters, ArduinoLEDMatrix& matrix);

  // Print To Serial Status And Conditional Check WiFi Matrix Sign
  static void check_wifi_status(ArduinoLEDMatrix& matrix);

  // Begin Matrix (USED TO SIMPLIFY matrix.begin();)
  static void begin_ArduinoLEDMatrix(ArduinoLEDMatrix& matrix);

  // Create An ArduinoLEDMatrix Class Instance (USED TO SIMPLIFY (ArduinoLEDMatrix matrix;))
  static ArduinoLEDMatrix create_ArduinoLEDMatrix_class();

  static constexpr uint32_t load_frame_1[1][4] = {
	{ 0x7f, 0xe7027027, 0xfe000000, 66 }
  };

  static constexpr uint32_t load_frame_2[1][4] = {
    { 0x7f, 0xe7c27c27, 0xfe000000, 66 }
  };

  static constexpr uint32_t load_frame_3[1][4] = {
    { 0x7f, 0xe7f27f27, 0xfe000000, 66 }
  };

  static constexpr uint32_t load_frame_4[1][4] = {
    { 0x7f, 0xe7fe7fe7, 0xfe000000, 66 }
  };

  static constexpr uint32_t empty[1][4] = {
    { 0x0, 0x0, 0x0, 66 }
  };

  static constexpr uint32_t wifi_connected[1][4] = {
	  { 0x1f82044f, 0x21082640, 0x90000060, 66 }
  };
};

void WiFiSetter::begin_wifi_connection() {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  // String == Arduino string
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  unsigned short current_state{WL_IDLE_STATUS};

  while (current_state != WL_CONNECTED) {
    Serial.print("Connecting To: "); Serial.println(ssid);
    current_state = WiFi.begin(ssid, password);
    delay(5000);
  }

  Serial.print("Successfully Connected To: ");
  Serial.println(ssid);
}

void WiFiSetter::begin_wifi_connection_matrix(const unsigned short iters, ArduinoLEDMatrix& matrix) {
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  // String == Arduino string
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  unsigned short current_state{WL_IDLE_STATUS};

  while (current_state != WL_CONNECTED) {
    Serial.print("Connecting To: "); Serial.println(ssid);
    loading_screen(iters, matrix);
    current_state = WiFi.begin(ssid, password);
    delay(5000);
  }

  Serial.print("Successfully Connected To: ");
  Serial.println(ssid);
}

void WiFiSetter::flash_led(const unsigned short input_pin, const unsigned short iters) {
  for (int i = 0; i < iters; i++) {
    digitalWrite(input_pin, HIGH);
    delay(250);
    digitalWrite(input_pin, LOW);
    delay(250);
  }
}

void WiFiSetter::loading_screen(const unsigned short iters, ArduinoLEDMatrix& matrix) {
  for (int i = 0; i < iters; i++) {
    matrix.loadFrame(*load_frame_1);
    delay(150);
    matrix.loadFrame(*load_frame_2);
    delay(150);
    matrix.loadFrame(*load_frame_3);
    delay(150);
    matrix.loadFrame(*load_frame_4);
    delay(150);
  }

  matrix.loadFrame(*empty);
}

void WiFiSetter::check_wifi_status(ArduinoLEDMatrix& matrix) {
  (WiFi.status() == WL_CONNECTED) ? matrix.loadFrame(*wifi_connected) : matrix.loadFrame(*empty);
}

void WiFiSetter::begin_ArduinoLEDMatrix(ArduinoLEDMatrix& matrix) {
  matrix.begin();
}

ArduinoLEDMatrix WiFiSetter::create_ArduinoLEDMatrix_class() {
  ArduinoLEDMatrix matrix;
  return matrix;
}

#endif