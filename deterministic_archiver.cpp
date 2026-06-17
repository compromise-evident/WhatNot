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
	
	std::string SHA_256_input;
	std::string SHA_256_output;
	
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
		
		//Takes SHA-256 hash of archive.txt and saves it to file "SHA-256_history".
		long long size = std::filesystem::file_size("archive.txt"); SHA_256_input.resize(size);
		in_stream.open("archive.txt"); if(!in_stream) {std::cout << "\nCan't open file \"archive.txt\" for hashing.\n"; return 1;}
		in_stream.read(&SHA_256_input[0], size);
		in_stream.close();
		
		{SHA_256_output = ""; std::string msg = SHA_256_input; unsigned int H[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19}; const unsigned int K[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2}; unsigned long long bit_len = (unsigned long long)msg.length() * 8; msg.push_back((char)0x80); for(; (msg.length() % 64) != 56;) {msg.push_back((char)0x00);} for(int a = 7; a >= 0; a--) {msg.push_back((char)((bit_len >> (a * 8)) & 0xFF));} for(unsigned long long block_offset = 0; block_offset < msg.length(); block_offset += 64) {unsigned int W[64]; for(int t = 0; t < 16; t++) {W[t] = ((unsigned char)msg[block_offset + t * 4 + 0] << 24) | ((unsigned char)msg[block_offset + t * 4 + 1] << 16) | ((unsigned char)msg[block_offset + t * 4 + 2] <<  8) | ((unsigned char)msg[block_offset + t * 4 + 3]);} for(int t = 16; t < 64; t++) {unsigned int x1 = W[t - 2]; unsigned int s1 = ((x1 >> 17) | (x1 << 15)) ^ ((x1 >> 19) | (x1 << 13)) ^ (x1 >> 10); unsigned int x0 = W[t - 15]; unsigned int s0 = ((x0 >> 7) | (x0 << 25)) ^ ((x0 >> 18) | (x0 << 14)) ^ (x0 >> 3); W[t] = s1 + W[t - 7] + s0 + W[t - 16];} unsigned int a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7]; for(int t = 0; t < 64; t++) {unsigned int S1  = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7)); unsigned int ch  = (e & f) ^ (~e & g); unsigned int T1  = h + S1 + ch + K[t] + W[t]; unsigned int S0  = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10)); unsigned int maj = (a & b) ^ (a & c) ^ (b & c); unsigned int T2  = S0 + maj; h = g; g = f; f = e; e = d + T1; d = c; c = b; b = a; a = T1 + T2;} H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;} const char symbols[] = "0123456789abcdef"; for(int a = 0; a < 8; a++) {for(int b = 7; b >= 0; b--) {int nibble = (H[a] >> (b * 4)) & 0xF; SHA_256_output += symbols[nibble];}}}
		
		out_stream.open("SHA-256_history", ios::app); if(!out_stream) {std::cout << "\nCan't open file \"SHA-256_history\" for writing.\n"; return 1;}
		out_stream << SHA_256_output << " " << path << "\n";
		out_stream.close();
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
