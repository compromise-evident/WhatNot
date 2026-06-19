/*Convert any file to text and back                                             Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
(bytes become their actual hexadecimal.)
Tired of forums prohibiting file uploads?
Share the file as text "0123456789abcdef".
Recipients can use this tool to undo it. */

#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main()
{	int raw_byte;
	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(1) Bin to hex."
	     << "\n(2) Hex back to bin."
	     << "\n\nOption: "; int o; cin >> o;
	
	//Gets path (files & folders).
	std::cout << "\nDrop/enter file:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
	in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Bin to hex.
	if(o == 1)
	{	in_stream.open(path); out_stream.open("hex"); in_stream.get(file_byte);
		for(; in_stream.eof() == false; in_stream.get(file_byte))
		{	static const char symbols[] = "0123456789abcdef";
			out_stream << symbols[(unsigned char)file_byte >> 4] << symbols[file_byte & 0xf];
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
