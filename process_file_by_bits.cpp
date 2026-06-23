/*Process any file bit-by-bit. Add lines of code                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
at the bottom for what to do with 1s and 0s...*/

#include <fstream>
#include <iostream>
#include <string>
int main()
{	int raw_byte;
	char file_byte;
	std::ifstream in_stream;
	
	//Gets path.
	std::cout << "\nDrop/enter file:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
	in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Begins.
	in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Begins).\n"; return 1;}
	for(; in_stream.get(file_byte);)
	{	raw_byte = file_byte & 0xFF; //0 to 255.
		
		//Makes binary 00000000 to 11111111.
		bool binary[8] = {0};
		int place_value = 128;
		for(int a = 0; a < 8; a++)
		{	if(raw_byte >= place_value)
			{	binary[a] = 1;
				raw_byte -= place_value;
			}
			place_value /= 2;
		}
		
		//Processes 8 bits.
		for(int a = 0; a < 8; a++)
		{	if(binary[a] == 0)
			{	/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
				##'                                         '##
				#                      if                     #
				#                 file bit = 0                #
				##,                                         ,##
				####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
			}
			else
			{	/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
				##'                                         '##
				#                      if                     #
				#                 file bit = 1                #
				##,                                         ,##
				####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
			}
		}
	}
	in_stream.close();
}
