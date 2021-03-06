#pragma config(Sensor, in5,    basepot,        sensorPotentiometer)
#pragma config(Sensor, in6,    liftpot,        sensorPotentiometer)
#pragma config(Sensor, in7,    manippot,       sensorPotentiometer)
#pragma config(Motor,  port1,           mogoL,         tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           motomanipR,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           motomanipL,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           motoliftR1,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           motoliftL1,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           passive,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,            ,             tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           left,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           right,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          mogoR,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const unsigned short trueSpeed[128] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 21 , 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

//LINEAR DRIVE VARIABLES
int threshold = 10;
int speedLeft;
int speedRight;
string rightDrive= "rightDrive";
string leftDrive = "leftDrive";

//SETSPEED FUNCTION

void setSpeed()
{
	if(speedLeft > 127) speedLeft = 127;
	if(speedLeft < -127) speedLeft = -127;
	if(speedRight > 127) speedRight = 127;
	if(speedRight < -127) speedRight = -127;
	int absSpeedL = trueSpeed[abs(speedLeft)]*(speedLeft/abs(speedLeft+0.0001));
	int absSpeedR = trueSpeed[abs(speedRight)]*(speedRight/abs(speedRight+0.0001));
	motor[left] = absSpeedL;
	motor[right] = absSpeedR;
}



task main()
{
	int manippotval = 2350;
	int liftpotval = 1380;
	int basepotval = 4085;

	while(true)
		{

		// Arcade driving control
		if (abs(vexRT[Ch3]) + abs(vexRT[Ch4]) > 12)
		{
			speedLeft = vexRT[Ch4] + vexRT[Ch3];
			speedRight = vexRT[Ch4] -  vexRT[Ch3];
		}
		else
		{
			speedLeft = 0;
			speedRight = 0;
		}
		setSpeed();

		//mogo Block
			if (vexRT[Btn5D])
			{
				motor[mogoL] = 127 * vexRT[Btn5D];
				motor[mogoR] = 127 * vexRT[Btn5D];
			}
			else if (vexRT[Btn5U] && !(SensorValue[basepot] >= basepotval))
			{
				motor[mogoL] = -127 * vexRT[Btn5U];
				motor[mogoR] = -127 * vexRT[Btn5U];
			}
			else if (SensorValue[basepot] >= basepotval)
			{

				motor[mogoL] = -10;
				motor[mogoR] = -10;
			}
			else
			{
				motor[mogoL] = 0;
				motor[mogoR] = 0;
			}
			//	motor[mogoL] = (vexRT[Btn5U] * 127) + (vexRT[Btn5D] * -127);


		//block for potentiometer code for the lift
		if ((abs(vexRT[Ch2]) > 0 && !(SensorValue[liftpot] <= liftpotval)) || (vexRT[Ch2] > 0))
			{
				motor[motoliftL1] = vexRT[Ch2];
				motor[motoliftR1] = vexRT[Ch2];
			}

			else if (SensorValue[liftpot] <= liftpotval)
				{
						motor[motoliftL1] = 0;
						motor[motoliftR1] = 0;
					}
// Block for Manipulator Potentiometer code.
			if ((SensorValue[manippot] >= 4080) && (vexRT[Ch1] > 0))
			{
				motor[motomanipR] = 0;
				motor[motomanipL] = 0;


			}

			else if (((abs(vexRT[Ch1]) > 0) && !(SensorValue[manippot] <= manippotval)) || (vexRT[Ch1] > 0))
		{
				motor[motomanipL] = vexRT[Ch1];
				motor[motomanipR] = vexRT[Ch1];

			}
		  else if (SensorValue[manippot] <= manippotval)
				{
						motor[motomanipR] = 0;
						motor[motomanipL] = 0;

					}




	  //rest of motors operating lol
	motor[passive] = (127*vexRT[Btn6U]) + (-127 * vexRT[Btn6D]);
	}
}
