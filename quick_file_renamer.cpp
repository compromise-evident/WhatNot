//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
char extension[] = "";
/*Put things like ".png" between the quotes.
All renamed files will have that extension.



Copies files and renames them.*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	//Gets path, fixes it if dropped.
	cout << "\nDrop/enter folder:\n"; string path; getline(cin, path); if(path[0] == '\0') {getline(cin, path);}
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
	
	//Copies & renames.
	system("rm -r -f renamed");
	system("mkdir -p renamed");
	for(long long a = 0; a < number_of_files; a++)
	{	string new_name = "renamed/" + to_string(a + 1) + string(extension);
		out_stream.open(new_name);
		in_stream_n[a].get(file_byte); for(; in_stream_n[a].eof() == false; in_stream_n[a].get(file_byte)) {out_stream.put(file_byte);}
		out_stream.close();
	}
}
