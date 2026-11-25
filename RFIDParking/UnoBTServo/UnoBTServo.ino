
#include <Servo.h>
#include <SoftwareSerial.h>

#define SERVO_PIN 9

// Pulse widths in microseconds
#define PULSE_MIN 500
#define PULSE_MID 1500
#define PULSE_MAX 2500

SoftwareSerial BT(2, 3); // RX, TX
Servo gateServo;

void setup()
{
    Serial.begin(9600);
    BT.begin(9600);

    gateServo.attach(SERVO_PIN, PULSE_MIN, PULSE_MAX);
    gateServo.writeMicroseconds(PULSE_MIN);

    Serial.println("Bluetooth Servo Receiver");
    Serial.println("Waiting for commands...");
}

void loop()
{
    if (BT.available() > 0)
    {
        char command = BT.read();

        if (command == '1')
        {
            gateServo.writeMicroseconds(PULSE_MID);
            Serial.println("Gate Opened");
        }
        else if (command == '0')
        {
            gateServo.writeMicroseconds(PULSE_MIN);
            Serial.println("Gate Closed");
        }
    }
}
