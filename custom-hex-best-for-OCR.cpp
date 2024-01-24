/// custom-hex-best-for-OCR - convert between bin and a kind of hex             Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                           best for Optical Character Recognition.
///                           Hex: 0-9, RST, XYZ.


#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(1) Bin-to-Hex"
	     << "\n(2) Hex-to-Bin"
	
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
	
	
	
	
	
	//Converts bin to custom hex.
	if(user_option == '1')
	{	in_stream.open(path_to_file);
		out_stream.open("hex");
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	int temp_file_byte_normal = garbage_byte; //..........Converts file byte to int (0 to 255.)
			if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
			
			bool binary[8] = {0}; //..........Converts file byte to bin.
			int place_value = 128;
			for(int a = 0; a < 8; a++)
			{	if(temp_file_byte_normal >= place_value)
				{	binary[a] = 1;
					temp_file_byte_normal -= place_value;
				}
				place_value /= 2;
			}
			
			int first_nibble = 0; //..........Converts first 4 bits to int.
			place_value = 8;
			for(int a = 0; a < 4; a++)
			{	if(binary[a] == 1) {first_nibble += place_value;}
				place_value /= 2;
			}
			
			int second_nibble = 0; //..........Converts last 4 bits to int.
			place_value = 8;
			for(int a = 4; a < 8; a++)
			{	if(binary[a] == 1) {second_nibble += place_value;}
				place_value /= 2;
			}
			
			if     (first_nibble < 10) {first_nibble += 48;} //..........0-9
			else if(first_nibble < 13) {first_nibble += 72;} //..........RST
			else                       {first_nibble += 75;} //..........XYZ
			
			if(first_nibble < 128)  {out_stream.put(first_nibble       );} //..........Writes hex byte to file.
			else                    {out_stream.put(first_nibble  - 256);}
			
			if     (second_nibble < 10) {second_nibble += 48;} //..........0-9
			else if(second_nibble < 13) {second_nibble += 72;} //..........RST
			else                        {second_nibble += 75;} //..........XYZ
			
			if(second_nibble < 128) {out_stream.put(second_nibble      );} //..........Writes hex byte to file.
			else                    {out_stream.put(second_nibble - 256);}
			
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		out_stream.close();
	}
	
	
	
	
	
	//Converts custom hex to bin.
	if(user_option == '2')
	{	in_stream.open(path_to_file);
		out_stream.open("bin");
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	int temp_file_byte_normal = garbage_byte; //..........Converts file byte to int (0 to 255.)
			if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
			
			if     (temp_file_byte_normal < 58) {temp_file_byte_normal -= 48;} //..........0-9
			else if(temp_file_byte_normal < 85) {temp_file_byte_normal -= 72;} //..........RST
			else                                {temp_file_byte_normal -= 75;} //..........XYZ
			int first_nibble = temp_file_byte_normal;
			
			in_stream.get(garbage_byte);
			temp_file_byte_normal = garbage_byte; //..........Converts its pair byte to int (0 to 255.)
			if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
			
			if     (temp_file_byte_normal < 58) {temp_file_byte_normal -= 48;} //..........0-9
			else if(temp_file_byte_normal < 85) {temp_file_byte_normal -= 72;} //..........RST
			else                                {temp_file_byte_normal -= 75;} //..........XYZ
			int second_nibble = temp_file_byte_normal;
			
			bool binary[8] = {0}; //..........Converts first nibble to bin.
			int place_value = 128;
			for(int a = 0; a < 8; a++)
			{	if(first_nibble >= place_value)
				{	binary[a] = 1;
					first_nibble -= place_value;
				}
				place_value /= 2;
			}
			
			bool binary_first_nibble_copy[8]; for(int a = 0; a < 8; a++) {binary_first_nibble_copy[a] = binary[a];}
			for(int a = 0; a < 8; a++) {binary[a] = 0;} //..........Converts second nibble to bin.
			place_value = 128;
			for(int a = 0; a < 8; a++)
			{	if(second_nibble >= place_value)
				{	binary[a] = 1;
					second_nibble -= place_value;
				}
				place_value /= 2;
			}
			for(int a = 0; a < 4; a++) {binary[a] = binary_first_nibble_copy[a + 4];}
			
			int extracted_byte = 0; //..........Converts from 8 binary bits to int.
			place_value = 128;
			for(int a = 0; a < 8; a++)
			{	if(binary[a] == 1) {extracted_byte += place_value;}
				
				place_value /= 2;
			}
			
			if(extracted_byte < 128) {out_stream.put(extracted_byte      );} //..........Writes byte to file.
			else                     {out_stream.put(extracted_byte - 256);}
			
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		out_stream.close();
	}
}
