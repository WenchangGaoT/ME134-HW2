#include <WiFi.h>
#include <ESP32Servo.h>
#include <Stepper.h>

// PINs

#define STEPS 100

// Motors
Servo servo;
Stepper stepper1(STEPS, 8, 9, 10, 11);
Stepper stepper2(STEPS, 1, 2, 3, 4);


// Global variables

float l1 = 0;
float l2 = 0;
float l3 = 0;

class Coordinate {
public:
  float x, y, z;
  Coordinate(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

class Angle {
public: 
  float theta1, theta2, theta3; 
  Angle(float theta1, float theta2, float theta3) {
    this->theta1 = theta1;
    this->theta2 = theta2;
    this->theta3 = theta3;
  }
};

// Coordinate trajectory for the desired 4 letters
Coordinate* j_trajectory;
Coordinate* c_trajectory;
Coordinate* w_trajectory;
Coordinate* g_trajectory;


void calculate_angles(Coordinate c, Angle* a) {
  // Calculate the corresponding angles for the given coordinates.
  // The angles are directly set with the angle
}

void write_j() {
  // write the letter J using its trajectory 
  Angle* a;
  for(int i = 0; i < 50; i++) {
    calculate_angles(j_trajectory[i], a);
    // // TODO: move motors to a angles
  }
}

void write_c() {
  Angle* a;
  for(int i = 0; i < 50; i++) {
    calculate_angles(c_trajectory[i], a);
    // // TODO: move motors to a angles
  }
}

void write_w() {
  Angle* a;
  for(int i = 0; i < 50; i++) {
    calculate_angles(w_trajectory[i], a);
    // // TODO: move motors to a angles
  }
}

void write_g() {
  Angle* a;
  for(int i = 0; i < 50; i++) {
    calculate_angles(g_trajectory[i], a);
    // // TODO: move motors to a angles
  }
}

void setup() {
  Angle* a;
  for(int i = 0; i < 50; i++) {
    // calculate_angles(j_trajectory[i], a);
    // // TODO: move motors to a angles
  }
}

void loop() {
  Angle* a;
  for(int i = 0; i < 50; i++) {
    // calculate_angles(j_trajectory[i], a);
    // // TODO: move motors to a angles
  }
}