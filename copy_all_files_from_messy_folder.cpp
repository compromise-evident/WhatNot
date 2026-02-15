//Makes a copy of only files in any                                             Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
//folder, with duplicate-name safety.

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int main()
{	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	//Gets path, fixes it, tries it.
	cout << "\nDrop/enter folder:\n";
	char path[100000] = {'\0'}; cin.getline(path, 100000); if(path[0] == '\0') {cin.getline(path, 100000);}
	if(path[0] == '\'') {for(int bm = 0, a = 0; a < 100000; a++) {if(path[a] != '\'') {path[bm] = path[a]; if(path[bm] == '\\') {path[bm] = '\'';} bm++;}}}
	for(int a = 99999; a >= 0; a--) {if(path[a] != '\0') {if(path[a] == ' ') {path[a] = '\0';} break;}}
	in_stream.open(path); if(in_stream.fail() == true) {cout << "\nNo path " << path << "\n"; return 0;} in_stream.close();
	
	//Gets number of files.
	string find = "find "; find += path; find += " -type f | sort -V > f"; system(find.c_str()); //find /path/to/FOLDER -type f | sort -V > f
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
	{	char name[100000]; in_stream.getline(name, 100000); in_stream_n.push_back(ifstream(name));
		if(in_stream_n[a].fail() == true) {cout << "CAN'T OPEN " << name << "\n"; ok = false;}
	}
	in_stream.close();
	if(ok == false) {return 0;}
	
	//Performs.
	system("mkdir ALL_FILES -p");
	in_stream.open("f");
	for(long long a = 0; a < number_of_files; a++)
	{	char name[100000]; in_stream.getline(name, 100000);
		for(int b = 0; b < 100000; b++) {if(name[b] == '/') {name[b] = '\\';}}
		
		string out = "ALL_FILES/"; out += name;
		out_stream.open(out);
		in_stream_n[a].get(file_byte);
		for(; in_stream_n[a].eof() == false; in_stream_n[a].get(file_byte)) {out_stream.put(file_byte);}
		out_stream.close();
		
		cout << a + 1 << " of " << number_of_files << "\n";
	}
	in_stream.close();
	remove("f");
}
