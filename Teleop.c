#pragma config(Hubs,  S1, HTMotor,  HTServo,  HTMotor,  HTMotor)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     SensorIR,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     SensorColor,    sensorCOLORFULL)
#pragma config(Sensor, S4,     SensorSonic,    sensorSONAR)
#pragma config(Motor,  motorB,           ,             tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, PIDControl, reversed, encoder)
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

//Motor F = Left Front
//Motor G = Left Back
//Motor H = Right Front
//Motor I = Right Back

//Motor D = Flag Manipulator Spin
//Motor E = Block Manipulator Lift

//Servo 1 = Flag Manipulator Tilt
//Servo 2 = Flag Manipulator Tilt

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                               DirectInput Button Notes
//
// Buttons 0=X 1=A 2=B 3=Y 4=LB 5=RB 6=LT 7=RT 8=Back 9=Start 10=LSD 11=RSD
// POV (D-Pad) -1=None 0-7=Positions (0=up, 1-7 +CW)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                           Tele-Operation Mode Code Template
//
// This file contains a template for simplified creation of an tele-op program for an FTC
// competition.
//
// You need to customize two functions with code unique to your specific robot.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.

void stopMotors()
{
	motor[motorB] = 0;
	motor[motorC] = 0;
	motor[motorD] = 0;
	motor[motorE] = 0;
	motor[motorF] = 0;
	motor[motorG] = 0;
	motor[motorH] = 0;
	motor[motorI] = 0;
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
	ClearTimer(T1);
	while ((time10[T1] < 15000)&&(nMotorEncoder[motorE] < encTarget + threshold && !forward) && !(nMotorEncoder[motorE] > encTarget - threshold && forward) && joy1Btn(3) && joy2Btn(3))
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
			motor[motorB] = tiltPower;
			motor[motorC] = tiltPower;
		}
		else
		{
			motor[motorB] = tiltPower / -5;
			motor[motorC] = tiltPower / -5;
		}
	}
}

task eStop()
{
	while(true)
	{
		getJoystickSettings(joystick);
		if(joy1Btn(10) && joy2Btn(10)) //Program will pause everything when E-Stop button (start) hit on both controllers
		{
			stopMotors();
			while (joy1Btn(10) && joy2Btn(10)) //Wait until the buttons are released
			{
				getJoystickSettings(joystick);
			}
			while (!(joy1Btn(10) && joy2Btn(10))) //Wait until they are pressed again
			{
				getJoystickSettings(joystick);
			}
			getJoystickSettings(joystick);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
  // Place code here to sinitialize servos to starting positions.
  // Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

  return;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// The following is the main code for the tele-op robot operation. Customize as appropriate for
// your specific robot.
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot. Most tele-op programs will follow the following
// logic:
//   1. Loop forever repeating the following actions:
//   2. Get the latest game controller / joystick settings that have been received from the PC.
//   3. Perform appropriate actions based on the joystick + buttons settings. This is usually a
//      simple action:
//      *  Joystick values are usually directly translated into power levels for a motor or
//         position of a servo.
//      *  Buttons are usually used to start/stop a motor or cause a servo to move to a specific
//         position.
//   4. Repeat the loop.
//
// Your program needs to continuously loop because you need to continuously respond to changes in
// the game controller settings.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////


task main()
{
  initializeRobot();

  waitForStart();   // wait for start of tele-op phase

  bool esMotors = false; //Toggled state of Motor E-Stop mode
	bool esmHold = false; //If the Motor E-Stop button (B) is being held
	bool pressedLB = false;
	bool pressedLT = false;

	StartTask(eStop);

  while (true)
  {
	  getJoystickSettings(joystick);

	  //Controller 1 - Motors

		if (joy1Btn(9) && !esmHold) //Will toggle motor e-stop when Motor E-Stop button hit on controller 1 - Back
		{
			if (esMotors)
			{
				esMotors = false;
				esmHold = true;
				motor[motorG] = 0;
				motor[motorF] = 0;
				motor[motorH] = 0;
				motor[motorI] = 0;
			}
			else
			{
				esMotors = true;
				esmHold = true;
			}
		}
		else
		{
			esmHold = false;
		}

	  if (joy1Btn(11) || (joystick.joy1_y2 < 5 && joystick.joy1_y2 > -5) || esMotors) //Threshold & Preset Speed Button - RSD - 0
	  {
	  	motor[motorH] = 0;
	  	motor[motorI] = 0;
		}
		else
		{
			if (joy1Btn(8) && joystick.joy1_y2 > 0) //Preset Speed Button - RT - 75
		  {
		  	motor[motorH] = 75;
		  	motor[motorI] = 75;
			}
			else if (joy1Btn(6) && joystick.joy1_y2 > 0) //Preset Speed Button - RB - 30
		  {
		  	motor[motorH] = 30;
		  	motor[motorI] = 30;
			}
			else if (joy1Btn(8) && joystick.joy1_y2 < 0) //Preset Speed Button - RT - -75
		  {
		  	motor[motorH] = -75;
		  	motor[motorI] = -75;
			}
			else if (joy1Btn(6) && joystick.joy1_y2 < 0) //Preset Speed Button - RB - -30
		  {
		  	motor[motorH] = -30;
		  	motor[motorI] = -30;
			}
			else //No Presets - RS
			{
				motor[motorH] = joystick.joy1_y2;
			  motor[motorI] = joystick.joy1_y2;
			}
		}

		if (joy1Btn(12) || (joystick.joy1_y1 < 5 && joystick.joy1_y1 > -5) || esMotors) //Threshold & Preset Speed Button - LSD - 0
		{
			motor[motorF] = 0;
			motor[motorG] = 0;
		}
		else
		{
		  if (joy1Btn(7) && joystick.joy1_y1 > 0) //Preset Speed Button - LT - 75
		  {
		  	motor[motorF] = 75;
		  	motor[motorG] = 75;
			}
			else if (joy1Btn(5) && joystick.joy1_y1 > 0) //Preset Speed Button - LB - 30
		  {
		  	motor[motorF] = 30;
		  	motor[motorG] = 30;
			}
			else if (joy1Btn(7) && joystick.joy1_y1 < 0) //Preset Speed Button - LT - -75
		  {
		  	motor[motorF] = -75;
		  	motor[motorG] = -75;
			}
			else if (joy1Btn(5) && joystick.joy1_y1 < 0) //Preset Speed Button - LB - -30
		  {
		  	motor[motorF] = -30;
		  	motor[motorG] = -30;
			}
			else //No Presets - LS
			{
				motor[motorF] = joystick.joy1_y1;
			  motor[motorG] = joystick.joy1_y1;
			}
		}

		//Controller 2 - Block Manipulator & Flag Manipulator

		int tilt = 2; //Potential power for tilting the block manipulator
		int lift = 3; //Potential power for lifting the block manipulator

		if(joy2Btn(12)) //Increased potential power for lifting the block manipulator - LSD
			lift = 0;
		if(joy2Btn(11)) //Increased potential power for tilting the block manipulator - RSD
			tilt = 0;

		if (joystick.joy2_y1 < 5 && joystick.joy2_y1 > -5) //Threshold
		{
			motor[motorC] = 0;
			motor[motorB] = 0;
		}
		else if(joystick.joy2_y1 < -10) //Tilt Block Manipulator - LS
		{
			motor[motorC] = -100;
			motor[motorB] = -100;
		}
		else
		{
			motor[motorC] = 100;
			motor[motorB] = 100;
		}

		if (joystick.joy2_y2 < 5 && joystick.joy2_y2 > -5) //Threshold
		{
			motor[motorE] = 0;
		}
		else //Lift Block Manipulator - RS
		{
			motor[motorE] = joystick.joy2_y2 / lift;
		}

		if(joy2Btn(4)) //Autonomous velcro release - Y
		{
			nMotorEncoder[motorB] = 0;
			while(nMotorEncoder[motorB] < 60 && joy1Btn(3) && joy2Btn(3))
			{
				motor[motorB] = 70;
				motor[motorC] = 70;
			}
			motor[motorB] = 0;
			motor[motorC] = 0;
		}

		if(joy2Btn(2)) //Autonomous Dumping for 1-2 Blocks - A
		{
			stopMotors();
			liftTo(700, 25, 60, 15, 15); //Lifts steadily to encoder value 700
			motor[motorE] = 15; //Continue into stopper
			wait10Msec(90);
			motor[motorE] = 0; //Stop the lift
			while (!(nMotorEncoder[motorC] < -10) && joy1Btn(3) && joy2Btn(3)) //Dump blocks
			{
				motor[motorC] = -20;
				motor[motorB] = -20;
			}
			motor[motorB] = 0;
			motor[motorC] = 0;
			wait10Msec(30);
			liftTo(500, 80, 50, 10, 1);
			motor[motorE] = 2;
		}
		if(joy2Btn(1)) //Autonomous Dumping for 3-4 Blocks - X
		{
			stopMotors();
			liftTo(475, 25, 82, 6, 15); //Lifts steadily to encoder value 700
			motor[motorE] = 15; //Continue into stopper
			wait10Msec(90);
			motor[motorE] = 0; //Stop the lift
			while (!(nMotorEncoder[motorC] < -10) && joy1Btn(3) && joy2Btn(3)) //Dump blocks
			{
				motor[motorC] = -20;
				motor[motorB] = -20;
			}
			motor[motorB] = 0;
			motor[motorC] = 0;
			wait10Msec(30);
			liftTo(500, 80, 50, 10, 1);
			motor[motorE] = 2;
		}
		if(!joy2Btn(5)&&pressedLB)
		{
				pressedLB = false;
		}
		if(!joy2Btn(7)&&pressedLT)
		{
				pressedLT = false;
		}
		if(joy2Btn(5)) //Tilt Flag Manipulator down - LB
		{
			if(!pressedLB)
			{
				servo[servo2] -= 10;
				pressedLB = true;
			}
		}
		else if(joy2Btn(7)) //Tilt Flag Manipulator up - LT
		{
			if(!pressedLT)
			{
				servo[servo2] += 19;
				pressedLT = true;
			}
		}

		if(joy2Btn(6)) //Spin Flag Manipulator counter-clockwise - RB
			motor[motorD] = -75;
		else if(joy2Btn(8)) //Spin Flag Manipulator clockwise - RT
			motor[motorD] = 75;
		else
			motor[motorD] = 0;

		if(joystick.joy2_TopHat == 0) //Set tilt of Flag Manipulator to ready position - D-Pad Up
		{
			servo[servo2] = 90;
		}
		if(joystick.joy2_TopHat == 4) //Set tilt of Flag Manipulator to idle position - D-Pad Down
		{
			servo[servo2] = 0;
		}
  }
}
