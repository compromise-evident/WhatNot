//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long number_of_gaps = 10;                                                  //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
char            n[50000] = {"529047615243859473684669704987111038557573838"};

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
	
	//Prints prime gaps following that n.
	mpz_t prime; mpz_init(prime); mpz_set_str(prime, n, 10);
	mpz_t one; mpz_init(one); mpz_set_ui(one, 1);
	for(long long gap = 1, a = 0; a < number_of_gaps;)
	{	mpz_add(prime, prime, one);                    //Adds 1 to value.
		int primality = mpz_probab_prime_p(prime, 25); //Checks for primality.
		
		if(primality == 0) {gap++;}
		else {cout << gap << "\n"; gap = 1; a++;}
	}
}
