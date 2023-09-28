// #include <WiFi.h>
// #include <ESP32Servo.h>
// #include <Stepper.h>
#include <math.h>
#include <string>
#include <iostream> 
// #include <AccelStepper.h>

/* GPIO */
#define J1_DIR_PIN 2  // HIGH: CW; LOW: CCW
#define J1_STEP_PIN 15
#define J2_DIR_PIN 4
#define J2_STEP_PIN 0
#define J3_PWM_PIN 32

// Global variables
#define NEMA_STEP 200.0 // Nema 17HS4401 stepper motor spec. 

using namespace std;

double l1 = 20; // is this correct???
double l2 = 150;
double l3 = 100;

// wrapper class
class Arm {
  public:
    Arm() {
    //   AccelStepper J1(1, J1_STEP_PIN, J1_DIR_PIN);
    //   AccelStepper J2(1, J2_STEP_PIN, J2_DIR_PIN);
    //   Servo J3;
    //   J3.attach(J3_PWM_PIN);

      theta1 = 0;
      theta2 = 0;
      theta3 = 0;
    }

    void write(float x, float y, float z) {
      inverseKinematics(x, y, z);
      writeAngles();
    }

    void inverseKinematics(float x, float y, float z) {
      // Theta 1
      theta1 = atan(y/x);
      double a = 0;
      if(cos(theta1) <= 0.0001) a = y/sin(theta1) - l1;
      else a = x/cos(theta1) - l1;

      // Theta 2
      double temp = a*a + z*z;
      double alpha = atan(a/z);
      cout << "temp: " << temp << endl;
      if(temp <= 0.0001) theta2 = acos((l2*l2-l3*l3)/(2.0*l2));
      else theta2 = acos((temp+l2*l2-l3*l3)/(2.0*l2*sqrt(temp)));
      if(z <= 0.0001) theta2 += 90.0*(1000.0/57296.0); 
      else theta2 += alpha;
      cout << "acos: " << (temp+l2*l2-l3*l3)/(2.0*l2*sqrt(temp)) << endl;
      cout << "alpha: " << alpha << endl;
      cout << "a: " << a << endl;
      cout << "z: " << z << endl;
      cout << "atan2(a,z): " << atan2(a, z) << endl;
      cout << "atan(a/z): " << atan(a/z) << endl;

      // double theta2 = 2;

      // Theta 3
      if(temp <= 0.0001) theta3 = -acos((l3*l3-l2*l2)/(2.0*l3)) ;
      else theta3 = -acos((temp+l3*l3-l2*l2)/(2.0*l3*sqrt(temp))) ;
      if(z <= 0.0001) theta3 += 90.0*(1000.0/57296.0);
      else theta3 += alpha;
      theta3 -= theta2;
    //   theta3 += alpha;
      // double theta3 = acos((z-l2*cos(theta2))/l3);

      // converting radians to degrees
      this->theta1 = theta1 * (57296.0/1000.0);
      this->theta2 = theta2 * (57296.0/1000.0);
      this->theta3 = theta3 * (57296.0/1000.0);

      // updating coordinates
      this->x = x;
      this->y = y;
      this->z = z;
    }

    void writeAngles() {
      int theta1_pos = int((theta1/360.0) * NEMA_STEP) + 1; // + 1 to account for float rounding truncation
      int theta2_pos = int((theta2/360.0) * NEMA_STEP) + 1;
      int theta3_pos = int(theta3) + 1;
      /*
      J1.moveTo(theta1_pos);
      J2.moveTo(theta2_pos);
      J3.write(theta3_pos);
      J1.runToPosition();
      J2.runToPosition();
      J3.runToPosition();
      */

    //   theta1_true = J1.currentPosition();
    //   theta2_true = J2.currentPosition();
    //   theta3_true = J3.read();
    }

    // testing function
    void print() {
        cout << "theta1: " << theta1 << " theta2: "<< theta2 << " theta3: " << theta3 << endl;
      cout << "Coordinates: " << endl;
      cout << x << " " << y << " " << z << endl;

      //printf("TRUE ANGLES:");
      //printf(String(theta1_true) + " " + String(theta2_true) + " " + String(theta3_true));
    }

  private:
    /* Actuators */
    // AccelStepper J1;
    // AccelStepper J2;
    // Servo J3;
    
    /* Angles */
    float theta1;
    float theta2;
    float theta3;

    float theta1_true;
    float theta2_true;
    float theta3_true;

    /* XYZ Coordinates */
    float x;
    float y;
    float z;
};

/* */

Arm wenchoi;

void loop() {
  printf("INITIAL: ");
//   delay(1000);
  wenchoi.print();
//   delay(1000);
  wenchoi.inverseKinematics(150, 100, 100);
//   delay(1000);
  printf("FINAL:");
  wenchoi.print();
//   delay(5000);
  while (true) {}
}


int main() {
    loop();
}