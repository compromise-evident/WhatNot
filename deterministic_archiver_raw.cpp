/*The world's second deterministic archiver. Turn                               Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
any folder into a REPRODUCIBLE file and back. */

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
		out_stream.open("archive"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Writes list of folders).\n"; return 1;} //Writes list of folders.
		for(unsigned long long a = 0; a < folder_list.size(); a++) {out_stream << "FOLDER: " << folder_list[a] << "\n";}
		out_stream.close();
		
		//Appends files to archive.
		out_stream.open("archive", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Appends files to archive).\n"; return 1;}
		for(unsigned long long a = 0; a < file_list.size(); a++)
		{	//Adds file name.
			out_stream << "FILE: " << file_list[a] << "\n";
			
			//Adds file size.
			std::string full_path = path; full_path += "/"; full_path += file_list[a];
			unsigned long long size = std::filesystem::file_size(full_path);
			out_stream << size << "\n";
			if(size == 0) {continue;}
			
			//Adds file content.
			in_stream.open(full_path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Adds file content).\n"; return 1;}
			for(; in_stream.get(file_byte);) {out_stream.put(file_byte);}
			out_stream << "\n";
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
		{	//Creates folder.
			if(line.rfind("FOLDER: ", 0) == 0) //If line starts with "FOLDER: ".
			{	line.erase(0, 8);
				std::string dir = "unpacked/"; dir += line; std::filesystem::create_directories(dir);
				continue;
			}
			
			//Creates empty file.
			std::string name = "unpacked/";
			if(line.rfind("FILE: ", 0) == 0) //If line starts with "FILE: ".
			{	line.erase(0, 6); name += line;
				out_stream.open(name); if(!out_stream) {std::cout << "\nCan't open file for writing. (Creates empty file).\n"; return 1;}
				out_stream.close();
			}
			
			//Gets number of bytes to read.
			unsigned long long bytes_to_read = 0;
			if(std::getline(in_stream, line)) {bytes_to_read = std::stoull(line);}
			if(bytes_to_read == 0) {continue;}
			
			//Adds file content.
			out_stream.open(name, std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Adds file content).\n"; return 1;}
			for(unsigned long long a = 0; a < bytes_to_read; a++)
			{	if(in_stream.get(file_byte)) {out_stream.put(file_byte);}
			}
			if(in_stream.get(file_byte)) {}
			out_stream.close();
		}
		in_stream.close();
	}
}
