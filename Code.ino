#include <Servo.h>

// Motors
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
int MOTOR_PIN3 = 4;

// Ultrasonic sensor
int TRIG_PIN = 13;
int ECHO_PIN = 12;

// Servo
Servo servo;
int SERVO_PIN = 2;

// Constants
float SOUND_SPEED = 0.0345; // cm/microsecs
int MIN_DISTANCE = 6;       // cm

void setup()
{
    // Set up the motors
    pinMode(MOTOR_PIN1, OUTPUT);
    pinMode(MOTOR_PIN2, OUTPUT);
    pinMode(MOTOR_PIN3, OUTPUT);

    // Set up the ultrasonic sensor
    pinMode(TRIG_PIN, OUTPUT);
    digitalWrite(TRIG_PIN, LOW);
    pinMode(ECHO_PIN, INPUT);

    // Set up the servo motor
    servo.attach(SERVO_PIN, 0, 2700);
    servo.write(90);

    // Set up serial communication
    Serial.begin(9600);
}

void loop()
{
    // Trigger the ultrasonic sensor every 10 microseconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Obtain distance from obstacle
    int duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * SOUND_SPEED / 2;

    // Log distance
    Serial.println(distance);

    if (distance < MIN_DISTANCE)
    {
        // Stop all motors
        digitalWrite(MOTOR_PIN1, LOW);
        digitalWrite(MOTOR_PIN2, LOW);
        digitalWrite(MOTOR_PIN3, LOW);

        // Yeet the ball
        for (int i = 190; i >= 90; i--)
        {
            servo.write(i);
            delay(20);
        }
    }
    else
    {
        // Return the rotor to its initial position
        servo.write(90);

        // Run all motors
        digitalWrite(MOTOR_PIN1, HIGH);
        digitalWrite(MOTOR_PIN2, HIGH);
        digitalWrite(MOTOR_PIN3, HIGH);
    }
}
