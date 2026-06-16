//projecteuler.net/problem=104

/*100% brute force, using only basic variables, loops, and arrays.
Finds the index of the first Fibonacci whose first and last
nine digits contain digits 1-9, but not necessarily in order.

Prints answer: 329468
Fibonacci size: 68,855 digits.
Solves it in 1m28s @2.8GHz. */

#include <iostream>
int main()
{	int    top_term[70000] = {0};    top_term[69999] = 1;
	int bottom_term[70000] = {0}; bottom_term[69999] = 1;
	
	int Fibonacci_index = 2;
	int marker = 69998; //Where digits begin to the right.
	
	for(;;)
	{	//Generates Fibonacci number (69999 is the ones place.)
		for(int temp, a = 69999; a >= marker; a--)
		{	temp = top_term[a];
			top_term[a] += bottom_term[a];
			bottom_term[a] = temp;
			
			if(top_term[a] > 9) //If sum > 9, carries the one.
			{	top_term[a] %= 10;
				bottom_term[a - 1]++;
			}
		}
		Fibonacci_index++;
		if(top_term[marker] != 0) {marker--;}
		
		//Checks right Fibonacci end.
		int pan[10] = {0}, approve_left = 0, approve_right = 0;
		for(int temp, a = 69991; a <= 69999; a++) //Gives pan[] right digits.
		{	temp = top_term[a];
			pan[temp]++;
		}
		if(pan[0] != 0) {continue;}
		
		for(int a = 1; a < 10; a++) //Checks right if pandigital.
		{	if(pan[a] == 1) {approve_right++;}
		}
		
		//Checks left Fibonacci end.
		if((approve_right != 9) || ((marker + 1) > 69981)) {continue;}
		for(int a = 0; a < 10; a++) {pan[a] = 0;} //Resets pan[].
		for(int temp, a = (marker + 1); a <= (marker + 9); a++) //Gives pan[] left digits.
		{	temp = top_term[a];
			pan[temp]++;
		}
		if(pan[0] != 0) {continue;}
		
		for(int a = 1; a < 10; a++) //Checks left if pandigital.
		{	if(pan[a] == 1) {approve_left++;}
		}
		
		if((approve_left == 9) && (approve_right == 9)) {break;}
	}
	
	std::cout << "The Fibonacci number:\n\n"; for(int a = (marker + 1); a < 70000; a++) {std::cout << top_term[a];}
	std::cout << "\n\nAnd its index: " << Fibonacci_index;
}
