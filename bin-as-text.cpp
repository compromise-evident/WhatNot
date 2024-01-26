/// bin-as-text - convert between bin & bin-as-text                             Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///               (actual representation.)


#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(1) Bin to Binary_text"
	     << "\n(2) Binary_text to Bin"
	
	     << "\n\nOption: ";
	
	char user_option;
	cin >> user_option;
	if((user_option != '1') && (user_option != '2')) {cout << "Invalid."; return 0;}
	cout << "Drag & drop file into terminal or enter path:\n";
	
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
	
	
	
	
	
	//Converts bin to bin-as-text.
	if(user_option == '1')
	{	in_stream.open(path_to_file);
		out_stream.open("binary_text");
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	//..........Converts file byte to (0 to 255.)
			int temp_file_byte_normal = garbage_byte;
			if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
			
			//..........Converts file byte to binary of 00000000 to 11111111.
			bool binary[8] = {0};
			int place_value = 128;
			for(int a = 0; a < 8; a++)
			{	if(temp_file_byte_normal >= place_value)
				{	binary[a] = 1;
					temp_file_byte_normal -= place_value;
				}
				
				place_value /= 2;
			}
			
			//..........Processing 8 bits at a time.
			for(int bit = 0; bit < 8; bit++)
			{	if(binary[bit] == 0) {out_stream << "0";}
				else                 {out_stream << "1";}
			}
			
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		out_stream.close();
	}
	
	
	
	
	
	//Converts bin-as-text to bin.
	if(user_option == '2')
	{	in_stream.open(path_to_file);
		out_stream.open("bin");
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	bool binary[8] = {0}; //..........Grabs 8 text-bits.
			for(int a = 0; a < 8; a++)
			{	if(garbage_byte == '0') {binary[a] = 0;}
				else                    {binary[a] = 1;}
				
				in_stream.get(garbage_byte);
			}
			
			int extracted_byte = 0; //..........Converts from 8 binary bits to an integer.
			int place_value = 128;
			for(int a = 0; a < 8; a++)
			{	if(binary[a] == 1) {extracted_byte += place_value;}
				
				place_value /= 2;
			}
			
			if(extracted_byte < 128) {out_stream.put(extracted_byte      );} //..........Writes byte to file.
			else                     {out_stream.put(extracted_byte - 256);}
		}
		in_stream.close();
		out_stream.close();
	}
}
