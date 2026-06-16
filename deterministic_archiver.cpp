//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
long long max_strip_length = 5000;
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
using namespace std;
int main()
{	char file_byte;
	ifstream in_stream;
	ofstream out_stream;
	
	cout << "\n(1) Create archive"
	     << "\n(2) Unpack archive"
	
	     << "\n\nOption: ";
	
	int user_option; cin >> user_option;
	if((user_option != 1) && (user_option != 2)) {cout << "\nInvalid.\n"; return 1;}
	
	//Gets path, fixes it if dropped.
	if(user_option == 1) {cout << "Drop/enter folder:\n"      ;}
	if(user_option == 2) {cout << "Drop/enter archive file:\n";}
	string path; getline(cin, path); if(path[0] == '\0') {getline(cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();}
	in_stream.open(path); if(in_stream.fail()) {cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Create archive.___________________________________________________________________________________________________________________
	if(user_option == 1)
	{	vector <string>   file_list;
		vector <string> folder_list;
		for(const auto& entry : filesystem::recursive_directory_iterator(path))
		{	     if(entry.is_regular_file()) {  file_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of   files to RAM as relative paths.
			else if(entry.is_directory   ()) {folder_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of folders to RAM as relative paths.
		}
		
		sort(  file_list.begin(),   file_list.end()); //Sorts list of   files in RAM.
		sort(folder_list.begin(), folder_list.end()); //Sorts list of folders in RAM.
		
		out_stream.open("/tmp/dar_relative_paths");
		for(const auto& file_path : file_list)   {out_stream << file_path << "\n";} //Writes list of files to /tmp.
		out_stream.close();
		
		out_stream.open("archive.txt");
		for(const auto& file_path : folder_list) {out_stream << file_path << "\n";} //Writes list of folders to empty archive.
		out_stream.close();
		
		//Adds files to archive.
		ifstream in_stream_relative_paths;
		in_stream_relative_paths.open("/tmp/dar_relative_paths"); if(in_stream_relative_paths.fail()) {cout << "\nERROR 1\n"; return 1;}
		string line; getline(in_stream_relative_paths, line);
		if(line[0] != '\0')
		{	out_stream.open("archive.txt", ios::app); out_stream << "\n";
			for(; line[0] != '\0'; getline(in_stream_relative_paths, line))
			{	out_stream << line << "\n"; //Adds file name.
				string full_path = path; full_path += "/"; full_path += line;
				in_stream.open(full_path); if(in_stream.fail()) {cout << "\nERROR 2\n"; return 1;}
				in_stream.get(file_byte); if(in_stream.eof()) {out_stream << "EMPTY FILE\n\n"; in_stream.close(); continue;}
				long long strip = 0;
				for(; !in_stream.eof(); in_stream.get(file_byte))
				{	static const char symbols[] = "0123456789abcdef";
					out_stream << symbols[(unsigned char)file_byte >> 4] << symbols[file_byte & 0xf];
					strip++; if(strip == max_strip_length) {out_stream << "\n"; strip = 0;}
				}
				if(strip == 0) {out_stream << "\n";} else {out_stream << "\n\n";}
				in_stream.close();
			}
			out_stream.close();
		}
		in_stream_relative_paths.close();
	}
	
	//Unpack archive.___________________________________________________________________________________________________________________
	if(user_option == 2)
	{	//Creates empty folder "unpacked".
		filesystem::remove_all("unpacked"); filesystem::create_directories("unpacked");
		
		//If empty archive.
		in_stream.open(path); if(in_stream.fail()) {cout << "\nERROR 3\n"; return 1;}
		in_stream.get(file_byte); if(in_stream.eof()) {in_stream.close(); return 0;} in_stream.close();
		
		//If folders.
		if(file_byte != '\n')
		{	in_stream.open(path); if(in_stream.fail()) {cout << "\nERROR 4\n"; return 1;}
			string name; getline(in_stream, name);
			for(; name[0] != '\0'; getline(in_stream, name))
			{	string dir = "unpacked/"; dir += name; filesystem::create_directories(dir); //Creates folder.
			}
			getline(in_stream, name); if(name[0] == '\0') {in_stream.close(); return 0;}
			in_stream.close();
		}
		
		//If files.
		in_stream.open(path); if(in_stream.fail()) {cout << "\nERROR 5\n"; return 1;}
		string line; getline(in_stream, line);
		if(file_byte != '\n') {for(; line[0] != '\0'; getline(in_stream, line)) {}}
		for(;;)
		{	//Creates empty file.
			getline(in_stream, line); if(line[0] == '\0') {in_stream.close(); return 0;}
			string name = "unpacked/"; name += line; out_stream.open(name); out_stream.close();
			
			//Adds file content.
			getline(in_stream, line);
			if(line[0] != 'E')
			{	out_stream.open(name);
				//All strips.
				for(;;)
				{	//One strip.
					for(int a = 0; line[a] != '\0'; a += 2)
					{	int first  = line[a    ];
						int second = line[a + 1];
						if(first  < 58) {first  -= 48;} else {first  -= 87;}
						if(second < 58) {second -= 48;} else {second -= 87;}
						first <<= 4;
						out_stream.put(first + second);
					}
					getline(in_stream, line);
					if(line[0] == '\0') {break;}
				}
				out_stream.close();
			}
			else {getline(in_stream, line);}
		}
		in_stream.close();
	}
}
