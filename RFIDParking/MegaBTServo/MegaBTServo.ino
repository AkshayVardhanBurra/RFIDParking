
#define BT Serial1

#define OPEN 1
#define CLOSED 0

void sendServoCommand(int state)
{
    if (state == OPEN)
    {
        BT.write('1');
        Serial.println("Open command sent");
    }
    else if (state == CLOSED)
    {
        BT.write('0');
        Serial.println("Close command sent");
    }
}

void setup()
{
    Serial.begin(9600);
    BT.begin(9600);

    Serial.println("Bluetooth Servo Controller");
    Serial.println("Enter 1 to open or 0 to close");
}

void loop()
{
    if (Serial.available() > 0)
    {
        char command = Serial.read();

        if (command == '1')
        {
            sendServoCommand(OPEN);
        }
        else if (command == '0')
        {
            sendServoCommand(CLOSED);
        }
    }
}
