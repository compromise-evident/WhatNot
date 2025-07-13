//Open n files and read from any.                                               Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
int main()
{	char file_byte;
	ifstream in_stream;
	
	//Gets path, fixes it, tries it.
	cout << "\nDrop/enter folder:\n";
	char path[100000] = {'\0'}; cin.getline(path, 100000); if(path[0] == '\0') {cin.getline(path, 100000);}
	if(path[0] == '\'') {for(int bm = 0, a = 0; a < 100000; a++) {if(path[a] != '\'') {path[bm] = path[a]; if(path[bm] == '\\') {path[bm] = '\'';} bm++;}}}
	for(int a = 99999; a >= 0; a--) {if(path[a] != '\0') {if(path[a] == ' ') {path[a] = '\0';} break;}}
	in_stream.open(path); if(in_stream.fail() == true) {cout << "\nNo path " << path << "\n"; return 0;} in_stream.close();
	
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
	
	
	
	
	
	//EXAMPLE.
	for(long long a = 0; a < number_of_files; a++) {in_stream_n[a].get(file_byte); cout << file_byte;} //Prints 1st byte from each file.
	for(long long a = 0; a < number_of_files; a++) {in_stream_n[a].get(file_byte); cout << file_byte;} //Prints 2nd byte from each file.
}
