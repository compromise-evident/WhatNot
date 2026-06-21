//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
unsigned long long max_strip_length = 5000;
//# of 2-digit hex per line of file content in archive.txt



/*The world's first deterministic archiver. Turn any folder
into a REPRODUCIBLE text file and back. Yes, a text file--
another world's first! It's clean, readable, and editable.

archive.txt is fully editable;
* Edit folder names
* Delete / insert folders
* Edit file names
* Delete / insert files
* Make files empty
* Edit files (2-digit hex per byte,
  don't worry about line length) */

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
	
	std::cout << "\n(1) Create archive"
	          << "\n(2) Unpack archive"
	
	          << "\n\nOption: ";
	
	int user_option; std::cin >> user_option;
	if((user_option != 1) && (user_option != 2)) {std::cout << "\nInvalid.\n"; return 1;}
	
	//Create archive.___________________________________________________________________________________________________________________
	if(user_option == 1)
	{	//Gets path.
		std::cout << "\nDrop/enter folder:\n";
		std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
		if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
		in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
		
		//Gets list of ALL files & folders from a folder.
		std::vector <std::string>   file_list;
		std::vector <std::string> folder_list;
		for(const auto& entry : std::filesystem::recursive_directory_iterator(path))
		{	     if(entry.is_regular_file()) {  file_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of   files to RAM as relative paths.
			else if(entry.is_directory   ()) {folder_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of folders to RAM as relative paths.
		}
		std::sort(  file_list.begin(),   file_list.end()); //Sorts list of   files in RAM.
		std::sort(folder_list.begin(), folder_list.end()); //Sorts list of folders in RAM.
		
		//Creates archive (writes list of folders).
		out_stream.open("archive.txt"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Writes list of folders).\n"; return 1;} //Writes list of folders.
		for(unsigned long long a = 0; a < folder_list.size(); a++) {out_stream << folder_list[a] << "\n\n";}
		out_stream.close();
		
		//Appends files to archive.
		out_stream.open("archive.txt", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Appends files to archive).\n"; return 1;}
		for(unsigned long long a = 0; a < file_list.size(); a++)
		{	//Adds file name.
			out_stream << file_list[a] << "\n";
			
			//If empty file.
			std::string full_path = path; full_path += "/"; full_path += file_list[a];
			unsigned long long size = std::filesystem::file_size(full_path);
			if(size == 0) {out_stream << "EMPTY FILE\n\n"; continue;}
			
			//Adds file content.
			in_stream.open(full_path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Adds file content).\n"; return 1;}
			unsigned long long strip = 0;
			for(; in_stream.get(file_byte);)
			{	static const char symbols[] = "0123456789abcdef";
				out_stream << symbols[(unsigned char)file_byte >> 4] << symbols[file_byte & 0xf];
				strip++; if(strip == max_strip_length) {out_stream << "\n"; strip = 0;}
			}
			if(strip == 0) {out_stream << "\n";} else {out_stream << "\n\n";}
			in_stream.close();
		}
		out_stream.close();
	}
	
	//Unpack archive.___________________________________________________________________________________________________________________
	if(user_option == 2)
	{	//Gets path.
		std::cout << "\nDrop/enter archive file:\n";
		std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
		if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
		in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
		
		//Creates empty folder "unpacked".
		std::filesystem::remove_all("unpacked"); std::filesystem::create_directories("unpacked");
		
		//Exits if empty archive.
		unsigned long long size = std::filesystem::file_size(path); if(size == 0) {return 0;}
		
		//Unpacks.
		in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Unpacks).\n"; return 1;}
		for(std::string line; std::getline(in_stream, line);)
		{	if(line.empty()) {continue;}
			
			//Creates folder.
			if(in_stream.peek() == '\n')
			{	std::string dir = "unpacked/"; dir += line; std::filesystem::create_directories(dir);
				continue;
			}
			
			//Creates empty file.
			std::string name = "unpacked/"; name += line;
			out_stream.open(name); if(!out_stream) {std::cout << "\nCan't open file for writing. (Creates empty file).\n"; return 1;}
			out_stream.close();
			if(in_stream.peek() == 'E')
			{	std::getline(in_stream, line);
				continue;
			}
			
			//Adds file content.
			out_stream.open(name, std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Adds file content).\n"; return 1;}
			for(; std::getline(in_stream, line);)
			{	//One strip.
				for(int a = 0; line[a] != '\0'; a += 2)
				{	int first  = line[a    ];
					int second = line[a + 1];
					if(first  < 58) {first  -= 48;} else {first  -= 87;}
					if(second < 58) {second -= 48;} else {second -= 87;}
					first <<= 4;
					out_stream.put(first + second);
				}
				
				if(in_stream.peek() == '\n') {break;}
			}
			out_stream.close();
		}
		in_stream.close();
	}
}
