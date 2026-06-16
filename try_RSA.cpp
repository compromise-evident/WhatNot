//YOUR CONTROLS:                                                                Run it: "apt install g++ geany libgmp-dev". Open the .cpp in Geany.
char semiprime[100001] = {"4095075870816883"};                                  //Append "-lgmp" to Geany's compile & build commands. Hit F9 once. F5 to run.
int candidate_factor_digit_length = 8;
char known_first_digits_of_a_factor[50001] = {""};
//You can put one or more digits between the quotes.



/*Attempt factorization of semiprimes up to 100k digits
long. You can provide n known first digits of a factor.*/

#include <fstream>
#include <gmp.h>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	srand(time(0));
	int semiprime_digit_length = 0; for(int a = 0;                      semiprime[a] != '\0'; a++) {semiprime_digit_length++;}
	int known_digits_length    = 0; for(int a = 0; known_first_digits_of_a_factor[a] != '\0'; a++) {known_digits_length   ++;}
	char candidate_factor[50001] = {'\0'};
	for(int a = 0; a < known_digits_length; a++) {candidate_factor[a] = known_first_digits_of_a_factor[a];}
	for(int a = known_digits_length; a < candidate_factor_digit_length; a++) {candidate_factor[a] = ((rand() % 10) + 48);}
	cout << "\nFactoring " << semiprime_digit_length << "-digit semiprime.\nLooking for " << candidate_factor_digit_length << "-digit prime.\n";
	
	mpz_t dividend        ; mpz_init(dividend        );
	mpz_t divisor         ; mpz_init(divisor         );
	mpz_t remainder       ; mpz_init(remainder       );
	mpz_t wanted_remainder; mpz_init(wanted_remainder);
	int zero = 0;
	mpz_set_si (wanted_remainder, zero );
	mpz_set_str(dividend, semiprime, 10);
	
	for(int temp = (candidate_factor_digit_length - 1);;)
	{	//Modifies candidate_factor and ensures it does not begin with 0, and that it ends in 1, 3, 7, or 9.
		//Only one randomly-chosen digit is changed at a time (on the candidate factor.)
		int random_index = (rand() % (candidate_factor_digit_length - known_digits_length)); random_index += known_digits_length;
		     if(random_index ==    0) {candidate_factor[           0] = ((rand() %  9) + 49);}
		else if(random_index  < temp) {candidate_factor[random_index] = ((rand() % 10) + 48);}
		else
		{	candidate_factor[temp] = (rand() % 4);
			if((candidate_factor[temp] % 2) == 0) {candidate_factor[temp] += 7;}
			candidate_factor[temp] += 48;
		}
		
		mpz_set_str(divisor, candidate_factor, 10); mpz_mod(remainder, dividend, divisor ); //Mod operation.
		int comparison_of_wanted_remainder_with_zero = mpz_cmp(wanted_remainder, remainder);
		if(comparison_of_wanted_remainder_with_zero == 0)
		{	out_stream.open("FACTOR", ios::app); out_stream << candidate_factor << "\n"; out_stream.close(); //Saves factor to file.
			cout << "\nDone! Prime appended to file \"FACTOR\":\n\n" << candidate_factor << "\n\n"; return 0;
		}
	}
}
