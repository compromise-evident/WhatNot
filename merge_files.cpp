/*Merge any files based on most-occurring bits.                                 Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
By merging copies of a file, you recreate the original
file, even as the copies become increasingly corrupted.

Most-occurring bits are final, else 1.  Always merges bytes up to smallest file.
(Merges until "end of file" is reached in any file.) If you need to merge multi-
byte items in files,  simply make it read more bytes  before looping to the next
file; simply do "in_stream_n[a].get(file_byte);" multiple times.

Merge PyTorch models (.pth)
Preferably, merge models that are copies of one but trained in any way, or merge
models that are snapshots of a model being updated forever. This is fine because
PyTorch model training is nondeterministic by default. Make sure PyTorch creates
models with names of equal length, else model size differs.

DIY: github.com/compromise-evident/what-not/blob/main/open_n_files_and_read_from_any.cpp */

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
	
	//Merges.
	out_stream.open("MERGED"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Merges).\n"; return 1;}
	int bytes_merged = 0; unsigned long long MB_merged = 0;
	for(;;)
	{	//Gets byte from all files.
		unsigned long long occur[8] = {0};
		for(unsigned long long a = 0; a < file_list.size(); a++)
		{	if(!in_stream_n[a].get(file_byte)) {out_stream.close(); std::cout << "Done.\n"; return 0;} //Gets byte from a file.
			unsigned char raw_byte = file_byte & 0xFF;                                                 //Converts byte to 0-255.
			
			//Tallies only the 1 bits.
			occur[0] += (raw_byte >> 7) & 1;
			occur[1] += (raw_byte >> 6) & 1;
			occur[2] += (raw_byte >> 5) & 1;
			occur[3] += (raw_byte >> 4) & 1;
			occur[4] += (raw_byte >> 3) & 1;
			occur[5] += (raw_byte >> 2) & 1;
			occur[6] += (raw_byte >> 1) & 1;
			occur[7] +=  raw_byte       & 1;
		}
		
		//Writes 8 bits as a byte.
		unsigned char write_byte = 0;
		unsigned long long majority_threshold = ((file_list.size() + 1) / 2);
		for(int a = 0; a < 8; a++)
		{	write_byte <<= 1;
			if(occur[a] >= majority_threshold) {write_byte |= 1;}
		}
		out_stream.put(write_byte);
		
		//Keeps you posted.
		bytes_merged++; if(bytes_merged == 1000000) {bytes_merged = 0; MB_merged++; std::cout << MB_merged << "MB merged...\n";}
	}
}
