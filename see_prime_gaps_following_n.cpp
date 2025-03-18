//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long number_of_gaps = 10;                                                  //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
char            n[50000] = {"528037116243879373684169704087111038557573838"};

//This makes secure randomness. But also secure difficulties;
//"near which private prime, will I find these public gaps?"

#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	//Makes n prime.
	mpz_t in; mpz_init(in); mpz_t out; mpz_init(out);
	mpz_set_str(in, n, 10); mpz_nextprime(out, in); mpz_get_str(n, 10, out);
	cout << "\nPrime gaps after prime:\n" << n << "\n\n";
	
	//Gets ready.
	mpz_t prime; mpz_init(prime); mpz_set_str(prime, n, 10);
	mpz_t two; mpz_init(two); mpz_set_ui(two, 2);
	
	//Prints prime gaps which follow n.
	for(long long gap = 2, a = 0; a < number_of_gaps;)
	{	mpz_add(prime, prime, two);                    //Adds 2 to value.
		int primality = mpz_probab_prime_p(prime, 25); //Checks it for primality.
		
		if(primality == false) {gap += 2;}
		else {cout << gap << "\n"; gap = 2; a++;}
	}
	
	//"prime" is currently prime; that "for-loop" always exits with "prime" being prime.
	//That "for-loop" can be run again or copied, to continue with the following new gaps.
	char just_see[50000] = {'\0'}; mpz_get_str(just_see, 10, prime);
	cout << "\nEnded on prime:\n" << just_see;
}
