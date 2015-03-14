// Created on Tue February 17 2015 
#include "constants.h"
#include "drive.h"

// Replace FILE with your file's name
#ifndef _LINK_ROUTINES_H_
#define _LINK_ROUTINES_H_

//SERVOS
//servo_off(int) is replaced with the KIPR library function disable_servo(int)

void move_until_et(float threshold)
{
	motor(MOT_LEFT, 100);
	motor(MOT_RIGHT, 100);
	while(1)
	{
		//printf("ET: %d", analog_et(ET));
		if(analog_et(ET) >= threshold)
		{
			break;
		}
		msleep(50);
	}
	ao();
}

void right_until_et(float threshold)
{
	motor(MOT_LEFT, 100);
	while(1)
	{
		printf("ET_TURN: %d", analog_et(ET_TURN));
		if(analog_et(ET_TURN) >= threshold)
		{
			break;
		}
		msleep(50);
	}
	off(MOT_LEFT);
}

void left_until_et(float threshold)
{
	motor(MOT_RIGHT, 100);
	while(1)
	{
		printf("ET_TURN: %d", analog_et(ET_TURN));
		if(analog_et(ET_TURN) >= threshold)
		{
			break;
		}
		msleep(50);
	}
	off(MOT_RIGHT);
}

void servo_set(int port,int end,float time)//,float increment)
{//position is from 0-2047
	float increment = .01;
	//printf("servo %d",port);
	float curr,start = get_servo_position(port);
	float i = ((end-start)/time)*increment;
	curr = start;
	if (start > end)
	{
		while(curr > end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	else if (start < end)
	{
		while(curr < end)
		{
			//printf("%f\n",curr);
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	set_servo_position(port,end);
}

void lift_arm() 
{
	servo_set(ARM_SERVO, 2047, 5);
}

void lower_arm()
{
	servo_set(ARM_SERVO, 0 ,5);
}

void drive_to_pole() {
	// Add touch sensor stuff after Charlie is done modifying it
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 60);
	msleep(3000);
}

/**
 * 	Get a ping pong ball from any of the heights.å
 */
void ping()
{
	thread tid;
	tid = thread_create(lift_arm);
	thread_start(tid);
	motor(MOT_LEFT, -30);
	motor(MOT_RIGHT, -30);
	msleep(3500);
	forward(15);
	thread_destroy(tid);
	lower_arm();
	backward(15);
}

void ball_right()
{
	//turn_until_et(1, 100);
	ping();
	left(90, 0);
}

void ball_left()
{
	//turn_until_et(0,100);
	ping();
	right(90, 0);
}

/**
 * Tunnel to the "cave"
 * PROP_SERVO must be enabled
*/
void tunnel()
{
	ssp(PROP_SERVO, PROP_UP);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(500);
	fd_with_time(MOT_LEFT, MOT_RIGHT, 2000);
	ao();
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(300);
	ssp(PROP_SERVO, PROP_UP);
	msleep(300);
	forward_with_speed(MOT_LEFT, MOT_RIGHT, 500, 50);
	ao();
	ssp(PROP_SERVO, PROP_DOWN);
	msleep(500);
	ssp(PROP_SERVO, PROP_UP);
	msleep(500);
}


/**
 *		When perpendicular to a black line, square up on it.
 */
void square_on_line()
{
	while(analog(TOP_HAT_RIGHT) <= DARKNESS_THRESHOLD || analog(TOP_HAT_LEFT) <= DARKNESS_THRESHOLD) 
	{
		if(analog(TOP_HAT_RIGHT) >= DARKNESS_THRESHOLD)
		{
			motor(MOT_LEFT, 300);
			motor(MOT_RIGHT,200);
		}
		else if(analog(TOP_HAT_LEFT) >= DARKNESS_THRESHOLD)
		{
			motor(MOT_RIGHT, 300);
			motor(MOT_LEFT, 200);
		}
		else
		{
			motor(MOT_RIGHT, 300);
			motor(MOT_LEFT, 300);
		}
		msleep(100);
	}
	ao();
}

/**
 * 	Drive along the middle black line and collect the golden poms.
 */
void drive_line()
{
	clear_motor_position_counter(MOT_LEFT);
	clear_motor_position_counter(MOT_RIGHT);
	
	while(get_motor_position_counter(MOT_LEFT)-100 < 19000 && get_motor_position_counter(MOT_RIGHT)-100 < 19000)
	{
				
		if(analog10(TOP_HAT_RIGHT) <= DARKNESS_THRESHOLD && analog10(TOP_HAT_LEFT) <= DARKNESS_THRESHOLD) 
		{
			motor(MOT_LEFT, 100);
			motor(MOT_RIGHT,100);
		}
		else {
			if(analog10(TOP_HAT_LEFT) >= DARKNESS_THRESHOLD)
			{
				printf("LEFT BLACK\n");
				motor(MOT_RIGHT, 100);
				motor(MOT_LEFT, 20);
			}
			if(analog10(TOP_HAT_RIGHT) >= DARKNESS_THRESHOLD)
			{
				printf("RIGHT BLACK\n");
				motor(MOT_LEFT, 100);
				motor(MOT_RIGHT, 20);
			}
		}
		msleep(50);
	}
}


void get_ping_pong_balls()
{
	int i;for(i = 0; i < 3; i++)
	{
		forward(15);
		move_until_et(400);
		ball_right();
		ball_left();
	}
}

void initialize() {
	enable_servo(ARM_SERVO);
	enable_servo(PROP_SERVO);
	ssp(ARM_SERVO, ARM_DOWN);
	ssp(PROP_SERVO, PROP_UP);
}

void test_et() {
	while(1) {
		printf("%d\n", analog_et(ET_TURN));
		msleep(500);
	}
}

void square_on_wall() {
	motor(MOT_LEFT, -80);
	motor(MOT_RIGHT, -80);
	msleep(3000);
	ao();
}

#endif
