#include <stdio.h>
#include <math.h>

#include "link_routines.h"

int main() {	
	initialize();
	
	printf("Getting ping pong balls 2-3\n");
	int i; 
	for(i = 0; i < 2; i++) {
		move_until_et(300);
		forward(2);
		left(75, 0);
		drive_to_pole();
		ping();
		left(-75, 0);
		forward(20);
	}
	
	printf("Move across center\n");
	move_until_et(300);
	forward(10);
	move_until_et(300);
	forward(10);
	
	printf("Getting ping pong balls 4-5\n");
	for(i = 0; i < 2; i++) {
		move_until_et(300);
		left(75, 0);
		ping();
		drive_to_pole();
		left(-75, 0);
		forward(10);
	}
	
	/*
	printf("Getting over the middle...\n");
	tunnel();
	square_on_wall();
	forward(10);
	
	printf("Steal a tribble from the other team...\n");
	right(60, 0);
	drive_to_pole();
	ping();
	
	backward(10);
	lower_arm();
	
	backward(10);
	left(40, 0);
	square_on_wall();
	forward(10);
	left(180, 0);
	square_on_wall();
	*/
}
