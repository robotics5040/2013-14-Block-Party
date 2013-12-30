#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
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

  //waitForStart(); // Wait for the beginning of autonomous phase.
	forward(40, 20);
  while (SensorValue[SensorColor] > 10 || SensorValue[SensorColor] == 0)
  	forward(40, 0);

  turn(50, -30, 50);

	nMotorEncoder[motorF] = 0;

	forward(70, 100);
}
