//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
bool merge_based_on_bit_occurrence = true;



/*Merge any files of any size & quantity based on most-occurring
bits or bytes. By merging copies of a file, you retrieve the
original file, even as the copies become increasingly corrupted.
 ______________________________________________________________________________
/                                                                              \
|                Most-occurring bits are final, else "1" bits.                 |
|                                                                              |
|                                                                              |
|                     byte 1     byte 2     byte 3     byte 4     byte 5       |
|                                                                              |
|      file 1        00000000   11111111   00000000   00000001   11111110      |
|      file 2        00000001   11111110   11111111   00000010   11111101      |
|      file 3        00000001   11111110   11111111   00000100   11111011      |
|      file 4        00000001   11111110   00000000   00001000   11110111      |
|      creates file  00000001   11111110   11111111   00000000   11111111      |
\______________________________________________________________________________/


 ______________________________________________________________________________
/                                                                              \
|    Most-occurring bytes are final, else the smallest most-occurring bytes.   |
|                                                                              |
|                                                                              |
|                     byte 1     byte 2     byte 3     byte 4     byte 5       |
|                                                                              |
|      file 1           a          x          !         200        115         |
|      file 2           a          y          &         199        012         |
|      file 3           a          x          ?         198        255         |
|      file 4           a          y          !         200        000         |
|      file 5           b          x          %         199        123         |
|      creates file     a          x          !         199        000         |
\______________________________________________________________________________/



Always merges bytes up to smallest file.
----------------------------------------
(Merges until "end of file" is reached in any file.) If you need to merge multi-
byte items in files,  simply make it read more bytes  before looping to the next
file; simply do "in_stream_n[a].get(file_byte);" multiple times.



Merge PyTorch models (.pth)
---------------------------
Preferably, merge models that are copies of one but trained in any way, or merge
models that are snapshots of a model being updated forever. This is fine because
PyTorch model training is nondeterministic by default. Make sure PyTorch creates
models with names of equal length, else model size differs.



DIY: github.com/compromise-evident/what-not/blob/main/open_n_files_and_read_from_any.cpp */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{	int raw_byte;
	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	//Gets path, fixes it if dropped.
	cout << "\nDrop/enter folder with any files:\n"; string path; getline(cin, path); if(path[0] == '\0') {getline(cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();}
	in_stream.open(path); if(in_stream.fail()) {cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Gets number of files.
	string ls = "ls -Av "; ls += path; ls += " > f"; system(ls.c_str());
	long long number_of_files = 0;
	in_stream.open("f"); in_stream.get(file_byte);
	for(; in_stream.eof() == false; in_stream.get(file_byte)) {if(file_byte == '\n') {number_of_files++;}}
	in_stream.close();
	if(number_of_files == 0) {cout << "No files.\n"; return 0;}
	
	//Opens all files.
	vector <ifstream> in_stream_n;
	bool ok = true;
	in_stream.open("f");
	for(long long a = 0; a < number_of_files; a++)
	{	char line[100000]; in_stream.getline(line, 100000);
		string name = path; name += "/"; name += line;
		in_stream_n.push_back(ifstream(name));
		if(in_stream_n[a].fail() == true) {cout << "CAN'T OPEN " << name << "\n"; ok = false;}
	}
	in_stream.close();
	if(ok == false) {return 0;} remove("f");
	
	//Merges based on bit occurrence.
	if(merge_based_on_bit_occurrence == true)
	{	int bytes_merged = 0; long long MB_merged = 0;
		out_stream.open("MERGED_based_on_bit_occurrence");
		for(;;)
		{	long long occur[8][2] = {0};
			for(long long a = 0; a < number_of_files; a++)
			{	in_stream_n[a].get(file_byte); if(in_stream_n[a].eof() == true) {out_stream.close(); cout << "Done.\n"; return 0;}       //Gets byte from each file.
				raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;} int place = 128;
				for(int b = 0; b < 8; b++) {if(raw_byte >= place) {occur[b][1]++; raw_byte -= place;} else {occur[b][0]++;} place /= 2;} //Tallies bit occurrence.
			}
			bool binary[8] = {0}; for(int a = 0; a < 8; a++) {if(occur[a][1] >= occur[a][0]) {binary[a] = 1;}}                           //Gets  most-occurring bits.
			raw_byte = 0; int place = 128; for(int a = 0; a < 8; a++) {if(binary[a] == 1) {raw_byte += place;} place /= 2;}              //Turns them into byte.
			if(raw_byte < 128) {out_stream.put(raw_byte);} else {out_stream.put(raw_byte - 256);}                                        //Saves that byte.
			bytes_merged++; if(bytes_merged == 1000000) {bytes_merged = 0; MB_merged++; cout << MB_merged << "MB merged...\n";}          //Keeps you posted.
		}
	}
	
	//Merges based on byte occurrence.
	else
	{	int bytes_merged = 0; long long MB_merged = 0;
		out_stream.open("MERGED_based_on_byte_occurrence");
		for(;;)
		{	long long occur[256] = {0};
			for(long long a = 0; a < number_of_files; a++)
			{	in_stream_n[a].get(file_byte); if(in_stream_n[a].eof() == true) {out_stream.close(); cout << "Done.\n"; return 0;}    //Gets byte from each file.
				raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;} occur[raw_byte]++;                                          //Tallies byte occurrence.
			}
			long long most_occur = 0; for(int a = 0; a < 256; a++) {if(occur[a] > most_occur) {most_occur = occur[a]; raw_byte = a;}} //Gets  most-occurring byte.
			if(raw_byte < 128) {out_stream.put(raw_byte);} else {out_stream.put(raw_byte - 256);}                                     //Saves most-occurring byte.
			bytes_merged++; if(bytes_merged == 1000000) {bytes_merged = 0; MB_merged++; cout << MB_merged << "MB merged...\n";}       //Keeps you posted.
		}
	}
}
