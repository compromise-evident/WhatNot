//Open n files and read 1+ bytes from any file.                                 Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main()
{	char file_byte;
	std::ifstream in_stream;
	std::ofstream out_stream;
	
	//Gets path (files & folders).
	std::cout << "\nDrop/enter folder:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
	in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Gets list of ALL files.
	std::vector <std::string> file_list;
	for(const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{	if(entry.is_regular_file()) {file_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of files to RAM as relative paths.
	}
	std::sort(file_list.begin(), file_list.end()); //Sorts list of files in RAM.
	if(file_list.size() == 0) {std::cout << "\nNo files.\n"; return 0;} //Exits if no files.
	
	//Opens all files.
	std::vector <std::ifstream> in_stream_n;
	for(unsigned long long a = 0; a < file_list.size(); a++)
	{	std::string name = path; name += "/"; name += file_list[a];
		in_stream_n.push_back(std::ifstream(name));
		if(!in_stream_n[a]) {std::cout << "CAN'T OPEN " << name << "\n"; return 0;}
	}
	
	//EXAMPLE.
	for(unsigned long long a = 0; a < file_list.size(); a++) {in_stream_n[a].get(file_byte); std::cout << file_byte;} //Prints 1st byte from each file.
	for(unsigned long long a = 0; a < file_list.size(); a++) {in_stream_n[a].get(file_byte); std::cout << file_byte;} //Prints 2nd byte from each file.
}
