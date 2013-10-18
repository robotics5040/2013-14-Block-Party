#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     SensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     SensorColor,    sensorCOLORFULL)
#pragma config(Sensor, S4,     SensorSonic,    sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     motorF,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorG,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorH,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorI,        tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
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
//                                 Autonomous A - Right
//
// Position robot so it is parallel to the creates, go forward sensing IR is 9 at all, if found,
// back up and position robot for dumping cube in create. If not found within certain rotation, back
// up put in last create and attempt to drive up ramp using white line.
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

  return;
}

//For condensed code, this function serves as an easy way to move all motors forward/backwards. Distance is in cm
void forward(int power, int distance)
{
	if(distance != 0)
	{
		nMotorEncoder[motorF] = 0;
		while (69 * distance > nMotorEncoder[motorF] * -1)
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
		nMotorEncoder[motorF] = 0;
		while (69 * distance > nMotorEncoder[motorF] * -1)
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
  nMotorEncoder[motorG] = 0;

  //Find IR
	while(SensorValue(SensorIR) != 9)
	{
		forward(60, 0);
	}
	forward(0, 0);

	//int rotated = nMotorEncoder[motorG];

	PlaySound(soundFastUpwardTones); // Just for showing off during faire

/* DEPRICATED TEMPORARILLY FOR MINI MAKER FAIRE
  //Align and drop
	while(SensorValue(SensorIR) != 5)
		turn(70, -70, 0);
	wait10Msec(15);
	forward(50, 10);
	forward(0, 0);
	wait10Msec(50);

	//Retrace steps
	forward(-50, -13);
	forward(0, 0);
	if(rotated > -6500)
		while(SensorValue(SensorIR) != 1)
			turn(-70, 70, 0);
	else
		while(SensorValue(SensorIR) != 9)
			turn(70, -70, 0);

  //Get to ramp
	//MAKE AUTONOMOUS B FIRST THEN COMBINE
*/
}
