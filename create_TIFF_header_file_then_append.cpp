//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
long long  width = 500; // (image  width in pixels)
long long height = 500; // (image height in pixels)

//Creates 122-byte TIFF header file, to which you may append
//pixel values (3 bytes per pixel for red, green, and blue.)
//It's OK to append too many bytes. Each byte must be 0-255.
//Image viewers render TIFF pixels left-to-right, top-down.
//Each row is (width * 3) bytes long. No compression here.

//Red    pixel: bytes 255,0,0
//Green  pixel: bytes 0,255,0
//Blue   pixel: bytes 0,0,255

//White  pixel: bytes 255,255,255
//Black  pixel: bytes 0,0,0
//Grey   pixel: bytes n,n,n
//Purple pixel: bytes 255,0,255

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Bytes.
	int bytes[122] =
	{	73,73,      42,0,       8,0,0,0,        9,0,            //Number of entries                                   0-9
		0,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 1: width                                     10-21
		1,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 2: height                                    22-33
		2,1,        4,0,        1,0,0,0,        8,0,0,0,        //Entry 3: bits per sub-pixel                        34-45
		3,1,        4,0,        1,0,0,0,        1,0,0,0,        //Entry 4: compression                               46-57
		6,1,        4,0,        1,0,0,0,        2,0,0,0,        //Entry 5: RGB                                       58-69
		17,1,       4,0,        1,0,0,0,        122,0,0,0,      //Entry 6: byte index where pixel data begins        70-81
		21,1,       4,0,        1,0,0,0,        3,0,0,0,        //Entry 7: sub-pixels per pixel                      82-93
		22,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 8: load                                      94-105
		23,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 9: bytes of pixel data                      106-117
		0,0,0,0                                                 //End                                               118-121
	};
	
	//To add an entry:
	//Add 1 to the "9".
	//Add 12 to the "122".
	//Place your 12-byte entry after "Entry 9".
	//Optional: code another line as below so it can automatically apply a number to that entry.
	
	//Edits bytes.
	long long temp;
	temp =  width              ; for(int a =  18; a <=  21; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 1: width
	temp = height              ; for(int a =  30; a <=  33; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 2: height
	temp = height              ; for(int a = 102; a <= 105; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 8: load
	temp = (width * height) * 3; for(int a = 114; a <= 117; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 9: bytes of pixel data
	
	//Writes bytes to file.
	out_stream.open("append_to_me.tiff");
	for(int a = 0; a < 122; a++) {out_stream.put(bytes[a]);}
	out_stream.close();
	
	
	
	
	
	//Sample image (remove this.)
	out_stream.open("sample_copy_with_random_bytes_appended.tiff");
	for(int a = 0; a <                  122; a++) {out_stream.put(    bytes[a]);}
	for(int a = 0; a < (width * height) * 3; a++) {out_stream.put(rand() % 256);}
	out_stream.close();
}
