//Process any file bit-by-bit. Add lines of code                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
//at the end for what to do with 1s and 0s...

#include <bitset>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
int main()
{	char file_byte;
	std::ifstream in_stream;
	std::ofstream out_stream;
	
	//Gets path (files & folders).
	std::cout << "\nDrop/enter file:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
	in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Checks if file is empty.
	unsigned long long size = std::filesystem::file_size(path);
	if(size == 0) {std::cout << "\nEmpty file.\n"; return 0;}
	
	//Processes bits.
	in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Processes bits).\n"; return 1;}
	for(; in_stream.get(file_byte);)
	{	std::bitset<8> bits(file_byte);
		for(int a = 7; a >= 0; a--)
		{	if(bits[a] == 0)
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
