#include "mbed.h"
#include <chrono>
#include <cmath>


using namespace std::chrono;




BufferedSerial bt(D8, D2, 9600);


// L298N Motor Driver - Speed Control (PWM)
PwmOut ENA(D11);
PwmOut ENB(D10);


BusOut motor_pins(D3, D4, D5, D6);


// MH-Sensor Series Line Tracking Pins
DigitalIn sensorLeft(D7);
DigitalIn sensorCenter(D9);
DigitalIn sensorRight(D12);




bool isLineTrackingMode = false;


const float MAX_SPEED      = 0.98f;
const float LINE_MAX_SPEED = 0.65f;


float Kp = 0.15f;
float Kd = 0.70f;


int lastError = 0;


Timer connectionTimer;




void stopCar() {
    ENA.write(0.0f);
    ENB.write(0.0f);
    motor_pins.write(0b0000);
}


void setMotorSpeeds(float leftSpeed, float rightSpeed, float speedLimit = MAX_SPEED) {
    bool leftFwd = (leftSpeed >= 0);
    bool rightFwd = (rightSpeed >= 0);


    leftSpeed = fabs(leftSpeed);
    rightSpeed = fabs(rightSpeed);


    if (leftSpeed > speedLimit) leftSpeed = speedLimit;
    if (rightSpeed > speedLimit) rightSpeed = speedLimit;


    uint8_t dirBits = 0;
    if (leftFwd)  dirBits |= 0b0001;
    else          dirBits |= 0b0010;
    if (rightFwd) dirBits |= 0b0100;
    else          dirBits |= 0b1000;


    motor_pins.write(dirBits);
    ENA.write(leftSpeed);
    ENB.write(rightSpeed);
}




void lineTrackingLogic() {
    int sl = sensorLeft.read();
    int sc = sensorCenter.read();
    int sr = sensorRight.read();


    int error = 0;
 // 1. Calculate Error based on sensor states
    if (sl == 0 && sc == 1 && sr == 0) {
        error = 0;
    }
    else if (sl == 0 && sc == 1 && sr == 1) {
        error = 1;
    }
    else if (sl == 0 && sc == 0 && sr == 1) {
        error = 2;
    }
    else if (sl == 1 && sc == 1 && sr == 0) {
        error = -1;
    }
    else if (sl == 1 && sc == 0 && sr == 0) {
        error = -2;
    }
    else if (sl == 1 && sc == 1 && sr == 1) {
        error = 0;
    }
    else if (sl == 0 && sc == 0 && sr == 0) {
        if (lastError < 0) {
            error = -4;
        } else if (lastError > 0) {
            error = 4;
        } else {
            error = 0;
        }
    }


    float P = Kp * error;
    float D = Kd * (error - lastError);
    float correction = P + D;


    lastError = error;


    float leftMotorSpeed = LINE_MAX_SPEED + correction;
    float rightMotorSpeed = LINE_MAX_SPEED - correction;


    setMotorSpeeds(leftMotorSpeed, rightMotorSpeed, LINE_MAX_SPEED);
}




int main() {


    ENA.period_us(50);
    ENB.period_us(50);


    // Start the failsafe timer
    connectionTimer.start();


    stopCar();
    char rx_char;


    while (true) {
        if (bt.readable()) {
            ssize_t n = bt.read(&rx_char, 1);


            if (n > 0) {
                connectionTimer.reset();


                if (rx_char == 'X' || rx_char == 'W') {
                    isLineTrackingMode = true;
                    lastError = 0;
                    stopCar();
                }
                else if (rx_char == 'x' || rx_char == 'w') {
                    isLineTrackingMode = false;
                    stopCar();
                }



                if (!isLineTrackingMode) {
                    switch(rx_char) {
                        case 'F': setMotorSpeeds(MAX_SPEED, MAX_SPEED); break;
                        case 'B': setMotorSpeeds(-MAX_SPEED, -MAX_SPEED); break;
                        case 'L': setMotorSpeeds(-MAX_SPEED, MAX_SPEED); break;
                        case 'R': setMotorSpeeds(MAX_SPEED, -MAX_SPEED); break;


                        case 'G': setMotorSpeeds(MAX_SPEED * 0.5f, MAX_SPEED); break; // Forward-Left
                        case 'I': setMotorSpeeds(MAX_SPEED, MAX_SPEED * 0.5f); break; // Forward-Right
                        case 'J': setMotorSpeeds(-MAX_SPEED * 0.5f, -MAX_SPEED); break; // Back-Left
                        case 'H': setMotorSpeeds(-MAX_SPEED, -MAX_SPEED * 0.5f); break; // Back-Right


                        case 'S': stopCar(); break;
                    }
                }
            }
        }
        // If no Bluetooth data is received for more than 500ms in manual mode, stop the car
            if (!isLineTrackingMode) {
            auto elapsedTime = duration_cast<milliseconds>(connectionTimer.elapsed_time()).count();
            if (elapsedTime > 500) {
                stopCar();
            }
        }
        // 4. Execute Line Tracking continuously if active
        if (isLineTrackingMode) {
            lineTrackingLogic();
        }


        ThisThread::sleep_for(2ms);
    }
}



