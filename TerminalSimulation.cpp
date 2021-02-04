//Cheap physics simulation of bouncing balls in a tube.
//Object location history is "graphed" time vs. location.

#include <iostream>
using namespace std;

int main()
{	char tube[82]; //Width of terminal + 2 (must be even.)
	int blank =  32; // ' '
	int wall  = 119; // 'w'
	int plus  =  43; // '+' (bouncing object)
	int minus =  45; // '-' (bouncing object)
	
	//Fills tube with air and inserts a stopper on each end.
	for(int a = 0; a < 82; a++) {tube[a] = blank;}
	tube[ 0] = wall;
	tube[81] = wall;
	
	//Creates two objects in the tube and tracks their location (separated by even number of elements.)
	tube[14] = plus;
	tube[17] = minus;
	int left_loc  = 14;
	int right_loc = 17;
	
	//Points objects in opposite directions (go left = -1, go right = 1.)
	int left_state  = -1;
	int right_state =  1;
	
	//Sets objects into motion.
	for(int a = 0; a < 1000; a++)
	{	//Displays the tube one frame at a time, a thousand times.
		for(int b = 1; b < 81; b++) {cout << tube[b];} cout << "\n";
		
		// '+' moves normally.
		if(tube[left_loc + left_state] == blank)
		{	tube[left_loc] = blank;
			tube[left_loc + left_state] = plus;
			left_loc += left_state;
		}
		
		// '+' bounces off the wall.
		if(tube[left_loc + left_state] == wall) {left_state *= -1;}
		
		// '-' moves normally.
		if(tube[right_loc + right_state] == blank)
		{	tube[right_loc] = blank;
			tube[right_loc + right_state] = minus;
			right_loc += right_state;
		}
		
		// '-' bounces off the wall.
		if(tube[right_loc + right_state] == wall) {right_state *= -1;}
		
		//Objects collide.
		if(tube[left_loc +  1] == minus)
		{	left_state  *= -1;
			right_state *= -1;
		}
		
		//Wastefully consumes time between each frame.
		for(int waste = 0; waste <= 60000000; waste++) {}
	}
}
