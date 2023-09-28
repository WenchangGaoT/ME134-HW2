#include <WiFi.h>
#include <ESP32Servo.h>
#include <Stepper.h>
#include <math.h>

// PINs

#define STEPS 100

// Motors
Servo servo;
Stepper stepper1(STEPS, 8, 9, 10, 11);
Stepper stepper2(STEPS, 1, 2, 3, 4);


// Global variables

double l1 = 1;
double l2 = 1;
double l3 = 1;

class Coordinate {
public:
  double x, y, z;
  Coordinate(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

class Angle {
public: 
  double theta1, theta2, theta3; 
  Angle(double theta1, double theta2, double theta3) {
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


void calculate_angles(Coordinate c, Angle* angle) {
  // Calculate the corresponding angles for the given coordinates.
  // The angles are directly set with the angle

  double theta1 = atan(c.y/c.x);

  double a = 0;
  if(cos(theta1) <= 0.0001) a = c.y/sin(theta1) - l1;
  else a = c.x/cos(theta1) - l1;

  double theta2 = acos((a*a+c.z*c.z+l2*l2-l3*l3)/(2*l2));
  if(c.z <= 0.0001) theta2 += 90; 
  else theta2 += atan(a/c.z);

  double theta3 = acos((a*a+c.z*c.z+l3*l3-l2*l2)/(2*l3)) - theta2;
  if(a <= 0.0001) theta3 += 90;
  else theta3 += atan(c.z/a); 

  (*angle).theta1 = theta1;
  (*angle).theta2 = theta2;
  (*angle).theta3 = theta3;
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