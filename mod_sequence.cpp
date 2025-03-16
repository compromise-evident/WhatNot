//YOUR CONTROLS:                                                                //Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
unsigned long long    dividend = 1000000000000000000;
unsigned long long max_divisor = 100000000;
unsigned long long    quantity = 100000;

#include <iostream>
using namespace std;
int main()
{	unsigned long long wanted_remainder = 0;
	for(unsigned long long a = 0; a < quantity; a++, wanted_remainder++)
	{	for(unsigned long long divisor = 1;; divisor++)
		{	if((dividend % divisor) == wanted_remainder) {cout << wanted_remainder << " = " << dividend << " mod " << divisor << "\n"; break;}
			if (divisor  > max_divisor)                  {cout << wanted_remainder << " = " << dividend << " mod >max_divisor\n";      break;}
		}
	}
}

//Some of these sequences (sometimes every other value) I had searched for on OEIS and found matches!
//Additionally, this can be used for infosec and to ID or hash "dividend". If I want a remainder of
//80 and 81, do 1000000000000000000 mod 118 as well as mod 14925373. And dividend may not be known.
