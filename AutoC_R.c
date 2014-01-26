#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S2,     SensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     SensorColor,    sensorI2CHiTechnicColor)
#pragma config(Sensor, S4,     SensorSonic,    sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Motor F = Right Back
//Motor G = Right Front
//Motor H = Left Back
//Motor I = Left Front

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous B - Right
//
// Position robot so it is facing white line. Go towards and line fallow until in front of ramp.
// Check ultrasonic throughout making sure we don't run in to anything. Check again to see if there
// is a robot in the way of bridge. If not, go on bridge. If so, go on other side.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of autonomous mode, you may want to perform some initialization on your robot.
// Things that might be performed during initialization include:
//   1. Move motors and servos to a preset position.
//   2. Some sensor types take a short while to reach stable values during which time it is best that
//      robot is not moving. For example, gyro sensor needs a few seconds to obtain the background
//      "bias" value.
//
// In many cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.
	nMotorEncoder[motorF] = 0;
	nMotorEncoder[motorG] = 0;
	nMotorEncoder[motorH] = 0;
	nMotorEncoder[motorI] = 0;
	nMotorEncoder[motorB] = 0;
	nMotorEncoder[motorC] = 0;
  return;
}

//For condensed code, this function serves as an easy way to move all motors forward/backwards. Distance is in cm
void forward(int power, int distance)
{
	if(distance != 0)
	{
		nMotorEncoder[motorH] = 0;
		while (69 * abs(distance) > abs(nMotorEncoder[motorH]))
		{
			motor[motorF] = power;
			motor[motorG] = power;
			motor[motorH] = power;
			motor[motorI] = power;
		}
		motor[motorF] = 0;
		motor[motorG] = 0;
		motor[motorH] = 0;
		motor[motorI] = 0;
	}
	else
	{
		motor[motorF] = power;
		motor[motorG] = power;
		motor[motorH] = power;
		motor[motorI] = power;
	}
}

//For condensed code, this function serves as an easy way to turn the robot by specifing the two sides power
void turn(int powL, int powR, int distance)
{
	if(distance != 0)
	{
		nMotorEncoder[motorH] = 0;
		while (69 * abs(distance) > abs(nMotorEncoder[motorH]))
		{
			motor[motorF] = powR;
			motor[motorG] = powR;
			motor[motorH] = powL;
			motor[motorI] = powL;
		}
		motor[motorF] = 0;
		motor[motorG] = 0;
		motor[motorH] = 0;
		motor[motorI] = 0;
	}
	else
	{
		motor[motorF] = powR;
		motor[motorG] = powR;
		motor[motorH] = powL;
		motor[motorI] = powL;
	}
}

//Used to tilt the block manipulator while addressing weight distribution
void liftTo(int encTarget, int threshold, int startPower, int endPower, int tiltPower)
{
	motor[motorE] = 20;
	int encStart = nMotorEncoder[motorE];
	float rate = (startPower - endPower) / abs(encTarget - encStart);

	int encCurr = nMotorEncoder[motorE];
	int powCurr = startPower;

	bool forward = encTarget > encCurr;

	while (!(nMotorEncoder[motorE] < encTarget + threshold && !forward) && !(nMotorEncoder[motorE] > encTarget - threshold && forward))
	{

		if (nMotorEncoder[motorE] != encCurr)// && !passed) //Checks if encoder value moved and adjusts the power
		{
			powCurr += rate * abs(nMotorEncoder[motorE] - encCurr);
			encCurr = nMotorEncoder[motorE];
		}

		if (nMotorEncoder[motorE] > encTarget) //Sets the power based on direction
			motor[motorE] = powCurr * -1;
		else
			motor[motorE] = powCurr;

		if (abs(nMotorEncoder[motorE] - encStart) > 400)
		{
			motor[motorB] = tiltPower * -1;
			motor[motorC] = tiltPower * -1;
		}
		else
		{
			motor[motorB] = tiltPower / 5;
			motor[motorC] = tiltPower / 5;
		}
	}
}

void releaseBucket()
{
	nMotorEncoder[motorB] = 0;
	while(nMotorEncoder[motorB] < 52)
	{
		motor[motorB] = 67;
		motor[motorC] = 67;
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
}

task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.
  releaseBucket();
  forward(40, 19);
	nMotorEncoder[motorC] = 0;
	nMotorEncoder[motorE] = 0;
	Sleep(300);
	liftTo(460, 25, 82, 6, 15); //Lifts steadily to encoder value
	motor[motorE] = 21; //Continue into stopper
	wait10Msec(130);
	motor[motorE] = 0; //Stop the lift
	while (!(nMotorEncoder[motorC] < -18)) //Dump blocks
	{
		motor[motorC] = -20;
		motor[motorB] = -20;
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait10Msec(30);
	liftTo(300, 80, 50, 10, 1);
	motor[motorE] = 0;
	forward(-40, -8);//back up a few inches from scoring zone
	turn(-30, 50, 21.7);// turn to set up autoB (this will need to be adjusted to be a perfect 90 degree turn)
  //AutoB_R run
	forward(40, 20);
  while (SensorValue[SensorColor] > 10 || SensorValue[SensorColor] == 0)
		forward(40, 0);

  turn(50, -30, 50);

	nMotorEncoder[motorF] = 0;

	forward(70, 75);
}
