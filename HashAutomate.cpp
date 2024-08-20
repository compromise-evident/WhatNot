/// HashAutomate - detect if file hosts changed something. Downloads            Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                from links in a file, saves sha256sum of individual
///                and 1 big hash of all, regardless of link order.


/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                         Have a text file ready with                        ,#
#'                          1 download link per line.                         '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Gets path to file from user.
	cout << "\nDrop/enter file with 1 download link per line:\n";
	
	//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
	//..........not being cleared, meaning you can have options before this, where the user presses enter.
	char path_to_file[10000] = {'\0'};
	{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
		cin.getline(path_to_file, 10000);
		if(path_to_file[0] == '\0')
		{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
			cin.getline(path_to_file, 10000);
		}
		if(path_to_file[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
		
		//..........Removes last space in path_to_file[].
		bool existence_of_last_space = false;
		for(int a = 9999; a > 0; a--)
		{	if(path_to_file[a] != '\0')
			{	if(path_to_file[a] == ' ') {path_to_file[a] = '\0'; existence_of_last_space = true;}
				break;
			}
		}
		
		//..........Removes encapsulating single-quotes in path_to_file[].
		bool existence_of_encapsulating_single_quotes = false;
		if(path_to_file[0] == '\'')
		{	for(int a = 0; a < 9999; a++)
			{	path_to_file[a] = path_to_file[a + 1];
				if(path_to_file[a] == '\0') 
				{	if(path_to_file[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
					path_to_file[a - 1] = '\0';
					existence_of_encapsulating_single_quotes = true;
					break;
				}
			}
		}
		
		//..........Replaces all "'\''" with "'" in path_to_file[].
		int single_quote_quantity = 0;
		for(int a = 0; a < 10000; a++)
		{	if(path_to_file[a] == '\'') {single_quote_quantity++;}
		}
		
		if((single_quote_quantity                     >    0)
		&& (existence_of_last_space                  == true)
		&& (existence_of_encapsulating_single_quotes == true))
		{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
			
			for(int a = 0; a < 9997; a++)
			{	if(path_to_file[a] == '\'')
				{	int temp = (a + 1);
					for(; temp < 9997; temp++)
					{	path_to_file[temp] = path_to_file[temp + 3];
					}
				}
			}
		}
	}
	
	//Checks if file exists (failure can be bad path info as well.)
	in_stream.open(path_to_file);
	if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nNo such file or directory.\n";             return 0;}
	char sniffed_one_file_character;
	in_stream.get(sniffed_one_file_character);
	if(in_stream.eof() == true) {in_stream.close();  cout << "\n\nNothing to process, the file is empty.\n"; return 0;}
	in_stream.close();
	
	//Gets location of the first encountered end-null coming from the left in path_to_file[].
	int path_to_file_null_bookmark;
	for(int a = 0; a < 10000; a++) {if(path_to_file[a] == '\0') {path_to_file_null_bookmark = a; break;}}
	
	//Prepares out file stream based on given directory.
	path_to_file[path_to_file_null_bookmark    ] = '-'; //..........Appending -saved to file name in path to file.
	path_to_file[path_to_file_null_bookmark + 1] = 's';
	path_to_file[path_to_file_null_bookmark + 2] = 'a';
	path_to_file[path_to_file_null_bookmark + 3] = 'v';
	path_to_file[path_to_file_null_bookmark + 4] = 'e';
	path_to_file[path_to_file_null_bookmark + 5] = 'd';
	out_stream.open(path_to_file);
	path_to_file[path_to_file_null_bookmark    ] ='\0'; //..........Reverts.
	
	//Counts number of links.
	in_stream.open(path_to_file);
	long number_of_links = 0;
	char garbage_byte;
	char temp_garbage_byte;
	in_stream.get(garbage_byte);
	for(; in_stream.eof() == false;)
	{	if(garbage_byte == '\n') {number_of_links++;}
		temp_garbage_byte = garbage_byte;
		in_stream.get(garbage_byte);
	}
	in_stream.close();
	
	if(temp_garbage_byte != '\n') {number_of_links++;}
	
	
	
	
	
	//Begins.
	cout << "\n\n";
	int hash_of_all_files[1280] = {0};
	long links_read_bookmark = -1;
	bool at_least_1_download_problem = false;
	for(long a = 0; a < number_of_links; a++)
	{	//..........Loads a link.
		in_stream.open(path_to_file);
		links_read_bookmark++;
		for(long b = 0; b < links_read_bookmark; b++) {in_stream.get(garbage_byte);} //..........Skips link Bytes that have been read.
		char wget[1000015] = {"wget -q -t 9 "};
		int wget_write_bookmark = 13;
		in_stream.get(garbage_byte);
		for(; garbage_byte != '\n';)
		{	wget[wget_write_bookmark] = garbage_byte;
			wget_write_bookmark++;
			links_read_bookmark++;
			in_stream.get(garbage_byte);
			
			if(in_stream.eof() == true) {break;}
		}
		in_stream.close();
		
		//..........Appends " -O temp" then null.
		wget[wget_write_bookmark    ] = ' ';
		wget[wget_write_bookmark + 1] = '-';
		wget[wget_write_bookmark + 2] = 'O';
		wget[wget_write_bookmark + 3] = ' ';
		wget[wget_write_bookmark + 4] = 't';
		wget[wget_write_bookmark + 5] = 'e';
		wget[wget_write_bookmark + 6] = 'm';
		wget[wget_write_bookmark + 7] = 'p';
		wget[wget_write_bookmark + 8] ='\0';
		
		//..........Downloads & prints the URL
		system(wget);
		for(int b = 13; b < wget_write_bookmark; b++)
		{	cout       << wget[b];
			out_stream << wget[b];
		}
		
		cout       << "\n";
		out_stream << "\n";
		
		//..........Checks if downloaded.
		in_stream.open("temp");
		bool download_problem = false;
		if(in_stream.fail() == true) {download_problem = true;}
		in_stream.get(garbage_byte);
		if(in_stream.eof() == true)  {download_problem = true;}
		in_stream.close();
		
		//..........Gets sha256sum.
		if(download_problem == true)
		{	at_least_1_download_problem = true;
			cout       << "FAILED!\n\n\n";
			out_stream << "FAILED!\n\n\n";
		}
		else
		{	system("sha256sum temp > temp_256");
			in_stream.open("temp_256");
			cout       << "sha256sum = ";
			out_stream << "sha256sum = ";
			for(int a = 0; a < 64; a++)
			{	in_stream.get(garbage_byte);
				cout       << char(garbage_byte);
				out_stream << char(garbage_byte);
			}
			in_stream.close();
			
			cout       << "\n(" << (a + 1) << " of " << number_of_links << " OK)\n\n\n";
			out_stream << "\n(" << (a + 1) << " of " << number_of_links << " OK)\n\n\n";
		}
		
		//..........Continues adding to the big hash.
		if(at_least_1_download_problem == false)
		{	system("sha512sum temp > temp_512");
			int hash_of_individual_file[1280] = {0};
			
			in_stream.open("temp_256"); //..........First, applies sha256sum to hash_of_individual_file[].
			if(in_stream.fail() == true) {cout << "\n\n\nFAILED! (1)\n\n\n"; in_stream.close(); return 0;}
			in_stream.get(garbage_byte);
			if(in_stream.eof() == true)  {cout << "\n\n\nFAILED! (2)\n\n\n"; in_stream.close(); return 0;}
			for(; in_stream.eof() == false;)
			{	srand(garbage_byte);
				
				if((garbage_byte % 2) == 0) //..........Left-to-right.
				{	for(int b = 0; b < 1280; b++)
					{	hash_of_individual_file[b] += (rand() % 95);
						hash_of_individual_file[b] %= 95;
					}
				}
				else
				{	for(int b = 1279; b >= 0; b--) //..........Right-to-left.
					{	hash_of_individual_file[b] += (rand() % 95);
						hash_of_individual_file[b] %= 95;
					}
				}
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			
			in_stream.open("temp_512"); //..........Additionally, applies sha512sum to hash_of_individual_file[].
			if(in_stream.fail() == true) {cout << "\n\n\nFAILED! (3)\n\n\n"; in_stream.close(); return 0;}
			in_stream.get(garbage_byte);
			if(in_stream.eof() == true)  {cout << "\n\n\nFAILED! (4)\n\n\n"; in_stream.close(); return 0;}
			for(; in_stream.eof() == false;)
			{	srand(garbage_byte);
				
				if((garbage_byte % 2) == 0) //..........Left-to-right.
				{	for(int b = 0; b < 1280; b++)
					{	hash_of_individual_file[b] += (rand() % 95);
						hash_of_individual_file[b] %= 95;
					}
				}
				else
				{	for(int b = 1279; b >= 0; b--) //..........Right-to-left.
					{	hash_of_individual_file[b] += (rand() % 95);
						hash_of_individual_file[b] %= 95;
					}
				}
				
				in_stream.get(garbage_byte);
			}
			in_stream.close();
			
			//..........Constructively combines hash.
			for(int b = 0; b < 1280; b++)
			{	hash_of_all_files[b] += hash_of_individual_file[b];
				hash_of_all_files[b] %= 95;
			}
		}
		
		remove("temp");
	}
	
	remove("temp_256");
	remove("temp_512");
	system("sleep 1" );
	if(at_least_1_download_problem == true)
	{	cout       << "\n\nAt least 1 download failed; the big hash is useless.";
		out_stream << "\n\nAt least 1 download failed; the big hash is useless.";
	}
	else
	{	//..........Prints big hash.
		cout       << "\n-------------1,280-character hash of all files REGARDLESS OF ORDER:-------------\n";
		out_stream << "\n-------------1,280-character hash of all files REGARDLESS OF ORDER:-------------\n";
		for(int a = 0; a < 1280; a++)
		{	cout       << char(hash_of_all_files[a] + 32);
			out_stream << char(hash_of_all_files[a] + 32);
		}
	}
	
	cout       << "\n\n(all saved to given directory)";
	out_stream << "\n";
	out_stream.close();
}
