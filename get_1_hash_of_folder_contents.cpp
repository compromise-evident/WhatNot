//Get hash of files in folder.                                                  Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Gets path to FOLDER from user.
	cout << "\nDrop/enter FOLDER containing only files:\n";
	
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
	
	//Checks if FOLDER exists.
	in_stream.open(path_to_file);
	if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nNo such directory.\n"; return 0;}
	in_stream.close();
	
	//Gets location of the first encountered end-null coming from the left in path_to_file[].
	int path_to_file_null_bookmark;
	for(int a = 0; a < 10000; a++) {if(path_to_file[a] == '\0') {path_to_file_null_bookmark = a; break;}}
	
	//Gets list of file names from given directory.
	char ls[10000] = {"ls "};
	for(int a = 0; path_to_file[a] != '\0'; a++) {ls[a + 3] = path_to_file[a];} //Appends given path.
	ls[path_to_file_null_bookmark +  3] = ' '; //Appends commands.
	ls[path_to_file_null_bookmark +  4] = '>';
	ls[path_to_file_null_bookmark +  5] = ' ';
	ls[path_to_file_null_bookmark +  6] = 'a';
	ls[path_to_file_null_bookmark +  7] = 'l';
	ls[path_to_file_null_bookmark +  8] = 'l';
	ls[path_to_file_null_bookmark +  9] = '_';
	ls[path_to_file_null_bookmark + 10] = 'f';
	ls[path_to_file_null_bookmark + 11] = 'i';
	ls[path_to_file_null_bookmark + 12] = 'l';
	ls[path_to_file_null_bookmark + 13] = 'e';
	ls[path_to_file_null_bookmark + 14] = '_';
	ls[path_to_file_null_bookmark + 15] = 'n';
	ls[path_to_file_null_bookmark + 16] = 'a';
	ls[path_to_file_null_bookmark + 17] = 'm';
	ls[path_to_file_null_bookmark + 18] = 'e';
	ls[path_to_file_null_bookmark + 19] = 's';
	system(ls);
	
	//Checks if FOLDER is empty.
	in_stream.open("all_file_names");
	char sniffed_one_file_character;
	in_stream.get(sniffed_one_file_character);
	if(in_stream.eof() == true) {in_stream.close(); cout << "\n\nNothing to process, the FOLDER is empty.\n"; return 0;}
	in_stream.close();
	
	//Counts number of files.
	long long number_of_files = 0;
	char file_byte;
	char temp_file_byte;
	in_stream.open("all_file_names");
	in_stream.get(file_byte);
	for(; in_stream.eof() == false;)
	{	if(file_byte == '\n') {number_of_files++;}
		temp_file_byte = file_byte;
		in_stream.get(file_byte);
	}
	in_stream.close();
	
	if(temp_file_byte != '\n') {number_of_files++;}
	
	//Begins.
	out_stream.open("all_file_bytes");
	cout << "\n";
	path_to_file[path_to_file_null_bookmark] = '/';
	path_to_file_null_bookmark++;
	long long file_name_bytes_read_bookmark = -1;
	for(long long a = 0; a < number_of_files; a++)
	{	//Loads path_to_file[] with file name.
		in_stream.open("all_file_names");
		file_name_bytes_read_bookmark++;
		in_stream.seekg(file_name_bytes_read_bookmark, std::ios::beg); //Skips name Bytes that have been read.
		
		int path_to_file_write_bookmark = path_to_file_null_bookmark;
		in_stream.get(file_byte);
		for(; file_byte != '\n';)
		{	path_to_file[path_to_file_write_bookmark] = file_byte;
			path_to_file_write_bookmark++;
			file_name_bytes_read_bookmark++;
			in_stream.get(file_byte);
			
			if(in_stream.eof() == true) {cout << "\nError 1\n"; return 0;}
		}
		in_stream.close();
		
		path_to_file[path_to_file_write_bookmark] = '\0';
		
		//Writes file bytes to file "all_file_bytes".
		in_stream.open(path_to_file);
		in_stream.get(file_byte);
		for(; in_stream.eof() == false;) {out_stream.put(file_byte); in_stream.get(file_byte);}
		in_stream.close();
		
		cout << (a + 1) << " of " << number_of_files << " done.\n";
	}
	out_stream.close();
	
	system("sha256sum all_file_bytes >> hash");
	cout << "\n\nHash appended to file \"hash\".\n\n";
}
