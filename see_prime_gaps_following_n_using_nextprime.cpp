//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
long long number_of_gaps = 10;                                                  //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.

char n[50001] = {"528037116243879373684169704087111038557573838"};
//                Replace with 1 to 50,000 digits




//This variant is slightly faster for n BELOW ~400 digits.
#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	//Makes n prime.
	mpz_t in, out; mpz_init(in); mpz_init(out);
	mpz_set_str(in, n, 10); mpz_nextprime(out, in); mpz_get_str(n, 10, out);
	cout << "\nPrime gaps after prime:\n" << n << "\n\n";
	
	//Prepares.
	mpz_t prime_1, prime_2, diff; mpz_init(prime_1); mpz_init(prime_2); mpz_init(diff); mpz_set_str(prime_1, n, 10);
	char gap[100] = {'\0'}; bool alternator;
	
	//Prints gaps.
	//(This block is loopable & copy-pasteable, always continues where it left off.)
	alternator = 0;
	for(long long a = 0; a < number_of_gaps; a++)
	{	if(alternator == 0) {mpz_nextprime(prime_2, prime_1); mpz_sub(diff, prime_2, prime_1); alternator = 1;}
		else                {mpz_nextprime(prime_1, prime_2); mpz_sub(diff, prime_1, prime_2); alternator = 0;}
		mpz_get_str(gap, 10, diff); cout << gap << "\n";
	}
	if(alternator == 1) {mpz_set(prime_1, prime_2);}
	
	//Extracts last prime.
	//(This block can always coexist with the "Prints gaps" block.)
	mpz_get_str(n, 10, prime_1);
	cout << "\nEnded on prime:\n" << n << "\n";
	
	
	
	
	
	/*It appears that both "mpz_probab_prime_p()" and "mpz_nextprime()" perform operations
	then call to Miller-Rabin, which uses random witnesses; there are negligible chances
	of non-deterministic classification. So I refuse to use this in rolling-code.cpp.
	If this was deterministic, it would have been also great for secure cryptographic
	difficulty; "near which private prime, will I find these public gaps?" */
}
