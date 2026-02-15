//Works by doing ((file_1_hash[0] + file_2_hash[0] + ...) mod 94) + 33          Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
//          then ((file_1_hash[1] + file_2_hash[1] + ...) mod 94) + 33
//          then ((file_1_hash[2] + file_2_hash[2] + ...) mod 94) + 33...

#include <fstream>
#include <iostream>
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
	
	//Gets sha512sum of each file.
	remove("sha512sum_of_each");
	in_stream.open("f");
	for(long long a = 0; a < number_of_files; a++)
	{	char name[100000]; in_stream.getline(name, 100000);
		string sha = "sha512sum "; sha += name; sha += " >> sha512sum_of_each"; system(sha.c_str()); //sha512sum /path/to/file >> sha512sum_of_each
	}
	in_stream.close();
	
	//Combines sha512sum of each file.
	long long hash[128] = {0};
	in_stream.open("sha512sum_of_each");
	for(long long a = 0; a < number_of_files; a++)
	{	char temp[100000]; in_stream.getline(temp, 100000);
		for(int b = 0; b < 128; b++) {hash[b] += temp[b];}
	}
	in_stream.close();
	
	//Prints & saves.
	out_stream.open("hash");
	cout << "\n";
	for(int a = 0; a < 128; a++) {hash[a] %= 94; hash[a] += 33; cout << char(hash[a]); out_stream << char(hash[a]);}
	cout << "\n";
	out_stream.close();
	remove("f");
}
