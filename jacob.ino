/*
  main.ino
  ME134 HW #2
  Jacob Choi 09/28/23
*/

#include <AccelStepper.h>
#include <ESP32Servo.h>
#include <math.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "ESPAsyncWebServer.h"
#include <string>

// WiFi settings
const char *server_id = "ESP";
const char *server_pwd = "espespespesp";
AsyncWebServer server(80);

/* GPIO */
#define J1_DIR_PIN 2 // HIGH: CW; LOW: CCW
#define J1_STEP_PIN 15
#define J2_DIR_PIN 0
#define J2_STEP_PIN 4
#define J3_PWM_PIN 32

/* Global variables */
#define NEMA_STEP 200.0 // Nema 17HS4401 stepper motor spec.
int idx = 0;

// Wrapper class
class Arm {
  public:
    Arm() {
      AccelStepper J1(1, J1_STEP_PIN, J1_DIR_PIN);
      AccelStepper J2(1, J2_STEP_PIN, J2_DIR_PIN);

      J1.setMaxSpeed(1000);
      J1.setAcceleration(30);
      J2.setMaxSpeed(1000);
      J2.setAcceleration(20);

      Servo J3;
      J3.attach(J3_PWM_PIN);

      theta1 = 0;
      theta2 = 0;
      theta3 = 0;
    }

    void write() {
      int theta1_pos = int((theta1/360.0) * NEMA_STEP) + 1; // + 1 to account for float rounding truncation
      int theta2_pos = int((theta2/360.0) * NEMA_STEP) + 1;
      int theta3_pos = int(theta3) + 1;
      
      // J1 actuation
      J1.moveTo(theta1_pos);
      Serial.println("THETA1 POS: " + String(theta1_pos));
      while (J1.distanceToGo() != 0) {
        if (J1.distanceToGo() == 0) { break; }
        Serial.println("***************");
        J1.run();
      }

      // J2 actuation
      J2.moveTo(theta2_pos);
      while (J2.distanceToGo() != 0) {
        if (J2.distanceToGo() == 0) { break; }
        J2.run();
      }

      // J3 actuation
      J3.write(theta3_pos);

      // Debugging purposes
      theta1_true = J1.currentPosition();
      theta2_true = J2.currentPosition();
      theta3_true = J3.read();
    }

    void print() {
      Serial.println("ANGLES:");
      Serial.println(String(theta1) + " " + String(theta2) + " " + String(theta3));

      Serial.println("COORDINATES:");
      Serial.println(String(x) + " " + String(y) + " " + String(z));

      Serial.println("TRUE ANGLES:");
      Serial.println(String(theta1_true) + " " + String(theta2_true) + " " + String(theta3_true));
    }

  public:
    /* Actuators */
    AccelStepper J1;
    AccelStepper J2;
    Servo J3;
    
    /* Angles */
    float theta1;
    float theta2;
    float theta3;

    int theta1_true;
    int theta2_true;
    int theta3_true;

    /* XYZ Coordinates */
    float x;
    float y;
    float z;
};

Arm wenchoi;

void setup() {
  Serial.begin(115200);

  WiFi.softAP(server_id, server_pwd);
  Serial.print("\nSetting up server...");
  IPAddress IP = WiFi.softAPIP();
  Serial.print("\nSuccessfully set up server.\n");
  Serial.println(IP);
  server.on("/test",HTTP_POST,[](AsyncWebServerRequest * request){},
    NULL,[](AsyncWebServerRequest * request, uint8_t *data_in, size_t len, size_t index, size_t total) {
      String angs = String((char*) data_in, len);
      //Serial.println("Received request!");
      //Serial.println(angs);
      request->send_P(200, "text/plain", String("received").c_str());
      int cur_theta = angs.toInt(); 
      //Serial.println(cur_theta);

      // TODO: Update thetas according to idx
      switch(idx) {
      case 0: {wenchoi.theta1 = cur_theta; break;}
      case 1: {wenchoi.theta2 = cur_theta; break;} 
      case 2: {wenchoi.theta3 = cur_theta; break;} 
      }
      idx++;
      if(idx == 3) {
        Serial.println(wenchoi.theta1);
        wenchoi.write();
      }
      idx %= 3;

  });

  server.begin();
}
void loop() { }
