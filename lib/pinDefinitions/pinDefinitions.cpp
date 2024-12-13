#include <pinDefinitions.h>
#include <Arduino.h>

void setupPins()
{
    pinMode(D1, INPUT);
    pinMode(D2, INPUT);
    pinMode(D3, INPUT);
    pinMode(D4, INPUT);
    pinMode(D5, INPUT);
    pinMode(D6, INPUT);
    pinMode(D7, INPUT);
    pinMode(D8, INPUT);
    pinMode(D9, INPUT);
    pinMode(D10, INPUT);


    pinMode(Green, OUTPUT);
    pinMode(Red, OUTPUT);
    pinMode(Blue, OUTPUT);
    pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
    pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
    pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
    pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);

    pinMode(LEFT_PWM, OUTPUT);
    pinMode(RIGHT_PWM, OUTPUT);

    pinMode(ENCODER_LEFT, INPUT);
    pinMode(ENCODER_RIGHT, INPUT);

    pinMode(S1, INPUT_PULLUP);
    pinMode(S2, INPUT_PULLUP);
    pinMode(S3, INPUT_PULLUP);
    pinMode(S4, INPUT_PULLUP);
    pinMode(S5, INPUT_PULLUP);
    pinMode(S6, INPUT_PULLUP);
    pinMode(S7, INPUT_PULLUP);
    pinMode(S8, INPUT_PULLUP);

    pinMode(XSHUT_PIN, OUTPUT);
    digitalWrite(XSHUT_PIN, LOW); 

}