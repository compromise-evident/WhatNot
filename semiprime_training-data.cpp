//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
int  p_length = 10; //50k  max (smaller prime)                                  Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
int  q_length = 10; //50k  max (larger  prime)
int pq_length = 20; //100k max (semiprime)
int  quantity = 100000;

//Generates a list of semiprimes and their
//factors. Format: "pq = p * q" where p < q.

#include <fstream>
#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	ofstream out_stream;
	
	srand(time(0));
	char  p[ 50001] = {'\0'};
	char  q[ 50001] = {'\0'};
	char pq[200001] = {'\0'};
	mpz_t randomness; mpz_init(randomness);
	mpz_t prime_p   ; mpz_init(prime_p   );
	mpz_t prime_q   ; mpz_init(prime_q   );
	mpz_t product   ; mpz_init(product   );
	
	out_stream.open("pq");
	for(int loops = 0; loops < quantity;)
	{	p[0] = ((rand() % 9) + 49); for(int a = 1; a < p_length; a++) {p[a] = ((rand() % 10) + 48);}          //Random p.
		mpz_set_str(randomness, p, 10); mpz_nextprime(prime_p, randomness); mpz_get_str( p, 10, prime_p);     //p made prime.
		if(p[p_length] != '\0') {p[p_length] = '\0'; continue;}                                               //Restarts if p too long.
		for(;;)
		{	q[0] = ((rand() % 9) + 49); for(; q[0] < p[0];) {q[0] = ((rand() % 9) + 49);}                     //q digit 1 >= p digit 1.
			for(int a = 1; a < q_length; a++) {q[a] = ((rand() % 10) + 48);}                                  //Random q.
			mpz_set_str(randomness, q, 10); mpz_nextprime(prime_q, randomness); mpz_get_str( q, 10, prime_q); //q made prime.
			if(q[q_length] != '\0') {q[q_length] = '\0'; continue;} else {break;}                             //Restarts locally if q too long.
		}
		if(mpz_cmp(prime_p, prime_q) != -1) {continue;}                                                       //Restarts if q <= p.
		mpz_mul(product, prime_p, prime_q); mpz_get_str(pq, 10, product);                                     //pq made.
		int length = 0; for(int a = 0; pq[a] != '\0'; a++) {length++;} if(length != pq_length) {continue;}    //Restarts if pq not pq_length.
		loops++; cout << loops << " of " << quantity << "\n";                                                 //Proceeds only if successful.
		
		//Saves to file.
		//###################################################
		out_stream << pq << " = " << p << " * " << q << "\n";
		//###################################################
	}
	out_stream.close();
}
