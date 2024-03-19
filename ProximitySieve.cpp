/// ProximitySieve - keeps generating 310-digit primes                          Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                  checked with p<1B and preceded by
///                  713+ verified consecutive composites.


/* Using rolling-code 3.1.0
#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                             Eats ~2GB RAM!                             '###
##                                                                            ##
#,         You'll need the GNU Multiple Precision Arithmetic Library.         ,#
#'       Do apt install libgmp-dev then append "-lgmp" to both compile &      '#
##        build commands. Or then compile: g++ /path_to_this.cpp -lgmp        ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

Encryption - after random_digits[] is filled with randomness, write your message
onto it in base 10, but ONLY in the middle  e.g. if you set prime_length to 300,
your message can be branded between elements 100 & 200.  It will be adjusted for
primality and written to file. Multiply that prime by another of similar length.
Now you have a semiprime difficult to  "un-multiply".  This is not a very strong 
primality test.  But large numbers of preceding composites  will up the chances.
However, try searching this file for   "Here's your chance to brand each n".  */

#include <fstream>
#include <gmp.h> //For GMP.
#include <iostream>
using namespace std;
int main()
{	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\       your       /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\       controls       ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	int prime_length = 310; //DEFAULT = 310. Only smaller is allowed.
	
	int minimum_preceding_composites = 713; //DEFAULT = 713.
	
	/*////////////////                                        \\\\\\\\\\\\\\\\\\
	///////////////////////                              \\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////                      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
	
	ifstream in_stream;
	ofstream out_stream;
	
	long long code_length_in_thousands = 1;
	bool RAM_Unix_time_supplement = true; //Set to true for codes of unique randomness, even with the same seeds file. DEFAULT = true.
	
	//The following block verbatim from rolling-code.cpp, except for cout & PS_seeds.
	//Creates seeds file if missing.
	const char seeds_file_name[50] = {"PS_seeds"};
	char garbage_byte_for_seeds_file;
	{	//..........Checks if seeds file exists.
		in_stream.open(seeds_file_name);
		bool existence_of_seeds_file = true;
		if(in_stream.fail() == true) {existence_of_seeds_file = false;}
		in_stream.close();
		
		if(existence_of_seeds_file == false)
		{	//..........Gets path to file from user.
			cout << "\nJust once, drop/enter any file"
			     << "\nof 1,000+ random first bytes:\n";
			
			//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
			//..........not being cleared, meaning you can have options before this, where the user presses enter.
			char path_to_file_for_seeds[10000] = {'\0'};
			{	for(int a = 0; a < 10000; a++) {path_to_file_for_seeds[a] = '\0';}
				cin.getline(path_to_file_for_seeds, 10000);
				if(path_to_file_for_seeds[0] == '\0')
				{	for(int a = 0; a < 10000; a++) {path_to_file_for_seeds[a] = '\0';}
					cin.getline(path_to_file_for_seeds, 10000);
				}
				if(path_to_file_for_seeds[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
				
				//..........Removes last space in path_to_file_for_seeds[].
				bool existence_of_last_space = false;
				for(int a = 9999; a > 0; a--)
				{	if(path_to_file_for_seeds[a] != '\0')
					{	if(path_to_file_for_seeds[a] == ' ') {path_to_file_for_seeds[a] = '\0'; existence_of_last_space = true;}
						break;
					}
				}
				
				//..........Removes encapsulating single-quotes in path_to_file_for_seeds[].
				bool existence_of_encapsulating_single_quotes = false;
				if(path_to_file_for_seeds[0] == '\'')
				{	for(int a = 0; a < 9999; a++)
					{	path_to_file_for_seeds[a] = path_to_file_for_seeds[a + 1];
						if(path_to_file_for_seeds[a] == '\0') 
						{	if(path_to_file_for_seeds[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
							path_to_file_for_seeds[a - 1] = '\0';
							existence_of_encapsulating_single_quotes = true;
							break;
						}
					}
				}
				
				//..........Replaces all "'\''" with "'" in path_to_file_for_seeds[].
				int single_quote_quantity = 0;
				for(int a = 0; a < 10000; a++)
				{	if(path_to_file_for_seeds[a] == '\'') {single_quote_quantity++;}
				}
				
				if((single_quote_quantity                     >    0)
				&& (existence_of_last_space                  == true)
				&& (existence_of_encapsulating_single_quotes == true))
				{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
					
					for(int a = 0; a < 9997; a++)
					{	if(path_to_file_for_seeds[a] == '\'')
						{	int temp = (a + 1);
							for(; temp < 9997; temp++)
							{	path_to_file_for_seeds[temp] = path_to_file_for_seeds[temp + 3];
							}
						}
					}
				}
			}
			
			//..........Loads seeds[] with given file's 1,000 Bytes.
			in_stream.open(path_to_file_for_seeds);
			if(in_stream.fail() == true) {cout << "\nNo such file.\n"; in_stream.close(); return 0;}
			unsigned int seeds[1000];
			for(int a = 0; a < 1000; a++)
			{	in_stream.get(garbage_byte_for_seeds_file);
				if(in_stream.eof() == true)
				{	for(int b = 0; b < 1000; b++) {seeds[b] = 0; seeds[b] = 4294967295;} //..........Overwrites RAM of array unsigned int seeds[1000].
					cout << "\n\nFile too small.\n\n"; in_stream.close(); return 0;
				}
				
				int normal_byte = garbage_byte_for_seeds_file;
				if(normal_byte < 0) {normal_byte += 256;}
				seeds[a] = normal_byte;
			}
			in_stream.close();
			
			//..........Creates seeds file (digits, and better distributed.)
			out_stream.open(seeds_file_name);
			srand(seeds[0]);
			for(int a = 0; a < 1000; a++)
			{	long long temp = ((seeds[a] + rand()) % 10);
				out_stream << char(temp + 48);
			}
			out_stream << "\n\n\n\nPRIVATE! DO NOT SHARE!\n";
			out_stream.close();
			
			//..........Overwrites RAM of array unsigned int seeds[1000].
			for(int a = 0; a < 1000; a++) {seeds[a] = 0; seeds[a] = 4294967295;}
		}
	}
	
	//Boolean sieve of Eratosthenes. Zeros are mapped to prime elements. Laughably, bool[] & char[] both consume 1 Byte.
	static bool sieve[1000000000] = {1, 1};
	for(int prime = 2; prime < 31623; prime++) //..........31,623 is sqrt(1,000,000,000). There are 50,847,534 primes. 
	{	for(; sieve[prime] == 1;) {prime++;} //..........Moves up the list if number already marked off.
		for(int a = prime + prime; a < 1000000000; a += prime) {sieve[a] = 1;} //..........Marks multiples (composites.)
	}
	
	
	
	
	
	//Begins.
	cout << "\nGenerating " << prime_length << "-digit primes."
	     << "\nOnly those preceded by " << minimum_preceding_composites << "+"
	     << "\ncomposites are saved to file...\n";
	
	char random_digits[311] = {'\0'};
	static bool proximity_sieve[1000000000] = {0}; //..........Billion-element segment "in front of random n", to be marked by p<1B.
	for(;;)
	{	//Creates random n (first 310 items of random_digits[] become digits) based on file "PS_seeds" (overwritten per prime.)
		//The following block verbatim from rolling-code.cpp, except for random_digits[], cout, Code, & absurd_protection_against_cryptanalysis.
		//Generates randomness.
		{	long long temp_overflow_for_randomness;
			
			//..........Loads seeds[] with seeds file.
			in_stream.open(seeds_file_name);
			unsigned int seeds[1000];
			for(int a = 0; a < 1000; a++)
			{	in_stream.get(garbage_byte_for_seeds_file);
				int normal_byte = garbage_byte_for_seeds_file;
				if(normal_byte < 0) {normal_byte += 256;}
				seeds[a] = normal_byte;
				
				seeds[a] -= 48;
				if((in_stream.eof() == true) || (seeds[a] > 9))
				{	for(int b = 0; b < 1000; b++) {seeds[b] = 0; seeds[b] = 4294967295;} //..........Overwrites RAM of array unsigned int seeds[1000].
					cout << "\n\nBad seeds file.\n\n"; in_stream.close(); return 0;
				}
			}
			in_stream.close();
			
			//..........Makes 100 10-digit actual seeds based on seeds[]. (Strings together 10 contiguous digits, 100 times.)
			unsigned int actual_seeds[100] = {0};
			int seeds_read_bookmark = 0;
			for(int a = 0; a < 100; a++)
			{	temp_overflow_for_randomness = 0;
				for(int b = 0; b < 10; b++)
				{	temp_overflow_for_randomness += seeds[seeds_read_bookmark];
					if(b < 9) {temp_overflow_for_randomness *= 10;}
					seeds_read_bookmark++;
				}
				
				actual_seeds[a] = (temp_overflow_for_randomness % 4294967296);
			}
			
			/*..........Supplements actual_seeds[] for unique randomness. (100 10-digit values
			            created from garbage RAM are added to the 100 10-digit actual_seeds[].)
			            Even if all zeros as supplement, actual_seeds[] take the weight (seeds file.)
			            Declare 100k or 1M unsigned int array; there will be ~628 garbage items at end.*/
			if(RAM_Unix_time_supplement == true)
			{	unsigned int RAM_garbage[100000];
				temp_overflow_for_randomness = (time(0) % 4294967296); //..........Adds Unix time to actual_seeds[0]. (temp_overflow_for_randomness is never reset; each actual_seed[] is supplemented with incremental, and unique.)
				
				for(int a = 0; a < 100; a++) //..........Adds sum of every RAM_garbage[] to actual_seeds[0], then sum of every other to actual_seeds[1], then sum of every third to actual_seeds[2], and so on.
				{	int skip = (a + 1);
					for(int b = 0; b < 100000; b += skip) {temp_overflow_for_randomness += RAM_garbage[b]; temp_overflow_for_randomness %= 4294967296;}
					
					temp_overflow_for_randomness += actual_seeds[a];
					actual_seeds[a] = (temp_overflow_for_randomness % 4294967296);
				}
				
				for(int a = 0; a < 100000; a++) {RAM_garbage[a] = 0; RAM_garbage[a] = 4294967295;} //..........Overwrites RAM of array unsigned int RAM_garbage[100000].
			}
			
			
			
			
			
			//..........Generator house.
			unsigned int randomness[1000] = {0};
			for(long long a = 0; a < code_length_in_thousands; a++)
			{	
				//..........Generator powerhouse.
				for(int b = 0; b < 100; b++)
				{	srand(actual_seeds[b]);
					/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
					#####'`                                                                  `'#####
					###'             You may freely replace the following few items.            '###
					##            Here, randomness is generated  1,000 bytes per round.           ##
					#,         What happens here, must happen 100 times.  For each time,          ,#
					#'        continue scrambling the unsigned int randomness[1000] array.        '#
					##        srand() will use a different seed for you, each time  (100.)        ##
					###,       Leave randomness[] with at least values  0 to 9  when done.      ,###
					#####,.                                                                  .,#####
					##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/
					for(int c = 0; c < 1000; c++) {randomness[c] += rand(); randomness[c] %= 256;} //..........Fills randomness[] (100x per 1,000-char code.)
					temp_overflow_for_randomness = (actual_seeds[99 - b] + rand()); //..........Modifies inverse actual_seeds[].
					actual_seeds[99 - b] = (temp_overflow_for_randomness % 4294967296);
					
					srand(actual_seeds[99 - b]);  //..........Now using that inverse seed.
					for(int c = 0; c < 1000; c++) //..........Swaps EACH & EVERY element in randomness[] with randomly chosen (100,000x per 1,000-char code.)
					{	int random_element = (rand() % 1000);
						for(; random_element == c;) {random_element = (rand() % 1000);}
						
						unsigned int temp_element = randomness[random_element];
						randomness[random_element] = randomness[c];
						randomness[c] = temp_element;
					}
					temp_overflow_for_randomness = (actual_seeds[b] + rand()); //..........Modifies current actual_seeds[].
					actual_seeds[b] = (temp_overflow_for_randomness % 4294967296);
				}
				
				//..........Makes 100 10-digit new actual seeds based on randomness[]. (!!! Adds to current actual_seeds. !!! The generated Code is NOT alone responsible for new actual_seeds. !!!) (Strings together 10 contiguous digits, 100 times.)
				int randomness_read_bookmark = 0;
				for(int b = 0; b < 100; b++)
				{	temp_overflow_for_randomness = 0;
					for(int c = 0; c < 10; c++)
					{	temp_overflow_for_randomness += (randomness[randomness_read_bookmark] % 10);
						if(c < 9) {temp_overflow_for_randomness *= 10;}
						randomness_read_bookmark++;
					}
					
					temp_overflow_for_randomness += actual_seeds[b];
					actual_seeds[b] = (temp_overflow_for_randomness % 4294967296);
				}
				
				/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
				#####'`                                                                  `'#####
				###'               Append-writes randomness[] to file "Code".               '###
				##                                                                            ##
				#,      Extract rand here!  unsigned int randomness[1000]  here-contains      ,#
				#'      1,000 random values 0 to 255. This array gets all new randomness      '#
				##       every time the program is here. And how many times is it here?       ##
				###,      That's equal to the direct value of code_length_in_thousands.     ,###
				#####,.                                                                  .,#####
				##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/
				for(int b = 0; b < prime_length; b++) {random_digits[b] = ((randomness[b] % 10) + 48);}
			}
			
			
			
			
			
			//..........Overwrites seeds file.
			out_stream.open(seeds_file_name);
			for(int a = 0; a < 100; a++)
			{	unsigned int place = 10;
				for(int b = 0; b < 9; b++)
				{	if(actual_seeds[a] < place) {out_stream << "0";}
					place *= 10;
				}
				out_stream << actual_seeds[a];
			}
			out_stream << "\n\n\n\nPRIVATE! DO NOT SHARE!\n";
			out_stream.close();
			
			//..........Overwrites RAM of variable long long temp_overflow_for_randomness.
			temp_overflow_for_randomness = 0; temp_overflow_for_randomness = -9223372036854775807; temp_overflow_for_randomness = 9223372036854775807;
			
			//..........Overwrites RAM of arrays unsigned int seeds[1000] and unsigned int randomness[1000].
			for(int a = 0; a < 1000; a++) {seeds[a] = 0; seeds[a] = 4294967295; randomness[a] = 0; randomness[a] = 4294967295;}
			
			//..........Overwrites RAM of array unsigned int actual_seeds[100].
			for(int a = 0; a < 100; a++) {actual_seeds[a] = 0; actual_seeds[a] = 4294967295;}
		}
		
		//..........Ensures first digit is not zero.
		if(random_digits[0] == '0') {random_digits[0] = '1';}
		
		
		
		
		
		/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
		#####'`                                                                  `'#####
		###'                Here's your chance to brand each n with                 '###
		##                 your message, before that n is made prime.                 ##
		#,                                                                            ,#
		#'                    Example:  random_digits[100] = '5';                     '#
		##                   Just don't disturb the last 20 digits                    ##
		###,                       such as random_digits[279].                      ,###
		#####,.                                                                  .,#####
		##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/
		
		
		
		
		
		//Operates on proximity_sieve[].
		mpz_t dividend ; mpz_init (dividend );
		mpz_t divisor  ; mpz_init (divisor  );
		mpz_t remainder; mpz_init (remainder);
		
		mpz_set_str(dividend, random_digits, 10);
		for(int a = 0; a < 1000000000; a++)
		{	if(sieve[a] == 0)
			{	//..........Mod operation.
				int prime = a;
				mpz_set_si(divisor, prime              );
				mpz_mod   (remainder, dividend, divisor);
				int extracted_remainder = mpz_get_si(remainder);
				
				//..........Proximity sieve operation.
				int natural_prime_position = (a - extracted_remainder);
				for(; natural_prime_position < 1000000000;)
				{	proximity_sieve[natural_prime_position] = 1;
					natural_prime_position += a;
				}
			}
		}
		
		//Finds prime element (having maximum verified consecutive composites in negative direction.)
		int prime_element;
		int largest_negative_gap = 0;
		for(int temp_ones_counter = 0, a = 0; a < 1000000000; a++)
		{	if(proximity_sieve[a] == 1) {temp_ones_counter++;}
			else
			{	if(temp_ones_counter > largest_negative_gap)
				{	largest_negative_gap = temp_ones_counter;
					prime_element = a;
				}
				
				temp_ones_counter = 0;
			}
		}
		
		//Append-writes to file: n + prime_element which adjusts n for primality.
		mpz_t n     ; mpz_init(n     );
		mpz_t addend; mpz_init(addend);
		mpz_t sum   ; mpz_init(sum   );
		
		char char_sum[1000];
		mpz_set_str(n, random_digits,  10);
		mpz_set_si (addend, prime_element);
		mpz_set_str(sum, char_sum,     10);
		
		//..........Sum operation.
		mpz_add    (sum, n, addend       );
		mpz_get_str(char_sum, 10, sum    );
		
		//..........Append-Writes prime to file "prime_values".
		if(largest_negative_gap >= minimum_preceding_composites)
		{	out_stream.open("prime_values", ios::app);
			for(int a = 0; char_sum[a] != '\0'; a++) {out_stream.put(char_sum[a]);} //..........Appends just the prime.
			out_stream << " (" << largest_negative_gap << " preceding composites)"; //..........Appends to prime: # of preceding composites.
			out_stream << "\n";
			out_stream.close();
		}
		
		//Resets proximity_sieve[].
		for(int a = 0; a < 1000000000; a++) {proximity_sieve[a] = 0;}
	}
}
