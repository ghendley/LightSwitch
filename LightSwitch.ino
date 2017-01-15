// Automatic light switch activator using 3D printed servo mount by carjo3000 http://www.thingiverse.com/thing:1156995

#include <Servo.h>

const int PIR_PIN = A5;
const int SERVO_PIN = 10;

const int REST_POSITION = 55;
const int ON_POSITION = 90;
const int OFF_POSITION = 20;

Servo switchServo;
unsigned int servoPosition;
unsigned int countdown;

void setup()
{
	servoPosition = REST_POSITION;
	countdown = 0;

	Serial.begin(9600);
	pinMode(PIR_PIN, INPUT);
	switchServo.attach(SERVO_PIN);
	switchServo.write(servoPosition);

	delay(3000); // allow PIR sensor to calibrate
}

void returnToRestPosition()
{
	Serial.println("Return to rest.");

	int delta = servoPosition < REST_POSITION ? 1 : -1;

	for (; servoPosition != REST_POSITION; servoPosition += delta)
	{
		switchServo.write(servoPosition);
		delay(15);
	}
}

void turnSwitchOn()
{
	Serial.println("Turn switch on.");

	for (; servoPosition <= ON_POSITION; servoPosition++)
	{
		switchServo.write(servoPosition);
		delay(15);
	}
	
	returnToRestPosition();
}

void turnSwitchOff()
{
	Serial.println("Turn switch off.");

	for (; servoPosition >= OFF_POSITION; servoPosition--)
	{
		switchServo.write(servoPosition);
		delay(15);
	}

	returnToRestPosition();
}

void loop()
{
	int pirVal = digitalRead(PIR_PIN);

	if (pirVal == HIGH)
	{
		if (countdown == 0)
		{
			turnSwitchOn();
		}
		countdown = 180;
	}
	else if (pirVal == LOW)
	{
		if (countdown > 0)
		{
			countdown--;
			if (countdown == 0)
			{
				turnSwitchOff();
			}
		}
	}

	delay(1000);
}
