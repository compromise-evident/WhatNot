/*Convert any file to text and back                                             Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
(bytes become their actual hexadecimal.)
Tired of forums prohibiting file uploads?
Share the file as text "0123456789abcdef".
Recipients can use this tool to undo it. */

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	int raw_byte;
	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(1) Bin to hex."
	     << "\n(2) Hex back to bin."
	     << "\n\nOption: "; int o; cin >> o;
	
	//Gets path, fixes it, tries it.
	cout << "Drop/enter file:\n";
	char path[100000] = {'\0'}; cin.getline(path, 100000); if(path[0] == '\0') {cin.getline(path, 100000);}
	if(path[0] == '\'') {for(int bm = 0, a = 0; a < 100000; a++) {if(path[a] != '\'') {path[bm] = path[a]; if(path[bm] == '\\') {path[bm] = '\'';} bm++;}}}
	for(int a = 99999; a >= 0; a--) {if(path[a] != '\0') {if(path[a] == ' ') {path[a] = '\0';} break;}}
	in_stream.open(path); if(in_stream.fail() == true) {cout << "\nNo path " << path << "\n"; return 0;} in_stream.close();
	
	//Bin to hex.
	if(o == 1)
	{	char symbols[17] = {"0123456789abcdef"};
		in_stream.open(path); out_stream.open("hex"); in_stream.get(file_byte);
		for(; in_stream.eof() == false; in_stream.get(file_byte))
		{	raw_byte = file_byte; if(raw_byte < 0) {raw_byte += 256;}
			out_stream << symbols[raw_byte >>  4];
			out_stream << symbols[raw_byte &  15];
		}
		in_stream.close(); out_stream.close();
	}
	
	//Hex back to bin.
	if(o == 2)
	{	in_stream.open(path); out_stream.open("bin"); in_stream.get(file_byte);
		for(; in_stream.eof() == false; in_stream.get(file_byte))
		{	if(file_byte < 58) {file_byte -= 48;} else {file_byte -= 87;}
			raw_byte = file_byte << 4;
			in_stream.get(file_byte);
			if(file_byte < 58) {file_byte -= 48;} else {file_byte -= 87;}
			out_stream.put(raw_byte + file_byte);
		}
		in_stream.close(); out_stream.close();
	}
}
