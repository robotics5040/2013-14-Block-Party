#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  none,     none,     none)
#pragma config(Sensor, S2,     SensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     SensorColor,    sensorI2CHiTechnicColor)
#pragma config(Sensor, S4,     SensorSonic,    sensorNone)
#pragma config(Motor,  motorB,           ,             tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S4_C1_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S4_C1_6,    servo6,               tServoNone)
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
  return;
}

//For condensed code, this function serves as an easy way to move all motors forward/backwards. Distance is in cm
void forward(int power, int distance)
{
	if(distance != 0)
	{
		nMotorEncoder[motorH] = 0;
		while (69 * distance > nMotorEncoder[motorH])
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
		while (69 * distance > nMotorEncoder[motorH])
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

task main()
{
  initializeRobot();
	waitForStart();
 	// Wait for the beginning of autonomous phase.
  bool dump = false;
  Sleep(0); //this tells te robot to delay 1000 = 1 second

	motor[motorF] = 40;
	motor[motorG] = 40;
	motor[motorH] = 40;
	motor[motorI] = 40;
 	while(nMotorEncoder[motorH]/69 < 110 && !dump) //go to position 4 if it has not dumped yet
	{

		if(SensorValue(S2) == 5 && !dump)
		{
			motor[motorF] = 0;
			motor[motorG] = 0;
			motor[motorH] = 0;
			motor[motorI] = 0;
			while(nMotorEncoder[motorA] < 100)
			{
				motor[motorA] = 50;
			}
			motor[motorA] = 0;
			dump = true;
			motor[motorF] = 40;
			motor[motorG] = 40;
			motor[motorH] = 40;
			motor[motorI] = 40;
		}
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	if(!dump)
	{
			motor[motorF] = 0;
			motor[motorG] = 0;
			motor[motorH] = 0;
			motor[motorI] = 0;
			while(nMotorEncoder[motorA] < 100)
			{
				motor[motorA] = 50;
			}
			motor[motorA] = 0;
	}
	while(nMotorEncoder[motorH]/69 > 10)
	{
		motor[motorF] = -40;
		motor[motorG] = -40;
		motor[motorH] = -40;
		motor[motorI] = -40;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	  nMotorEncoder[motorH] = 0;
  while(nMotorEncoder(motorH)/69 > -20)
	{
  	motor[motorF] = 40;
		motor[motorG] = 40;
		motor[motorH] = -60;
		motor[motorI] = -60;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	nMotorEncoder[motorH] = 0;
  while(nMotorEncoder(motorH)/69 > -14)
	{
  	motor[motorF] = -40;
		motor[motorG] = -40;
		motor[motorH] = -40;
		motor[motorI] = -40;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	nMotorEncoder[motorH] = 0;
  while(nMotorEncoder(motorH)/69 > -20)
	{
  	motor[motorF] = 40;
		motor[motorG] = 40;
		motor[motorH] = -60;
		motor[motorI] = -60;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	while(SensorValue[SensorColor] > 10 || SensorValue[SensorColor] == 0)//auto b just backwards
	{
  	motor[motorF] = -20;
		motor[motorG] = -20;
		motor[motorH] = -20;
		motor[motorI] = -20;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	nMotorEncoder[motorH] = 0;
  while(nMotorEncoder(motorH)/69 < 24)
	{
  	motor[motorF] = -40;
		motor[motorG] = -40;
		motor[motorH] = 40;
		motor[motorI] = 40;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;

	nMotorEncoder[motorH] = 0;
  while(nMotorEncoder(motorH)/69 < 110)
	{
  	motor[motorF] = 40;
		motor[motorG] = 40;
		motor[motorH] = 40;
		motor[motorI] = 40;
	}
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;
}
