//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long number_of_gaps = 10;                                                  //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.

char n[50001] = {"528037116243879373684169704087111038557573838"};
//                Replace with a "2" to 50,000 digits





#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	//Makes n prime.
	mpz_t in, out; mpz_init(in); mpz_init(out); mpz_set_str(in, n, 10); mpz_nextprime(out, in); mpz_get_str(n, 10, out);
	cout << "\nPrime gaps after prime:\n" << n << "\n\n";
	
	//Dedicates.
	mpz_t prime, two; mpz_init(prime); mpz_init(two); mpz_set_str(prime, n, 10); mpz_set_ui(two, 2);
	
	//Generates. (Copy-pastable & loopable; continues where it left off.)
	for(long long gap = 2, a = 0; a < number_of_gaps;)
	{	mpz_add(prime, prime, two);
		int primality = mpz_probab_prime_p(prime, 25);
		if(primality == false) {gap += 2;}
		else {cout << gap << "\n"; mpz_get_str(n, 10, prime); cout << n << "\n\n"; gap = 2; a++;}
	}
}
