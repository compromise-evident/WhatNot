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
	
	//Table.
	int  header[ 8] = { 73, 73, 42,  0,  8,  0,  0,  0                }; // 0-7       Header
	int entries[ 2] = {  9,  0                                        }; // 8-9       Tag count                   (number of entries)
	int entry_1[12] = {  0,  1,  4,  0,  1,  0,  0,  0,  0,  0,  0,  0}; // 10-21     ImageWidth                  (width)
	int entry_2[12] = {  1,  1,  4,  0,  1,  0,  0,  0,  0,  0,  0,  0}; // 22-33     ImageLength                 (height)
	int entry_3[12] = {  2,  1,  4,  0,  1,  0,  0,  0,  8,  0,  0,  0}; // 34-45     BitsPerSample               (bits per sub-pixel)
	int entry_4[12] = {  3,  1,  4,  0,  1,  0,  0,  0,  1,  0,  0,  0}; // 46-57     Compression
	int entry_5[12] = {  6,  1,  4,  0,  1,  0,  0,  0,  2,  0,  0,  0}; // 58-69     PhotometricInterpretation   (RGB)
	int entry_6[12] = { 17,  1,  4,  0,  1,  0,  0,  0,122,  0,  0,  0}; // 70-81     StripOffsets                (byte index where pixel data begins)
	int entry_7[12] = { 21,  1,  4,  0,  1,  0,  0,  0,  3,  0,  0,  0}; // 82-93     SamplesPerPixel             (sub-pixels per pixel)
	int entry_8[12] = { 22,  1,  4,  0,  1,  0,  0,  0,  0,  0,  0,  0}; // 94-105    RowsPerStrip
	int entry_9[12] = { 23,  1,  4,  0,  1,  0,  0,  0,  0,  0,  0,  0}; // 106-117   StripByteCounts             (bytes of pixel data)
	int  footer[ 4] = {  0,  0,  0,  0                                }; // 118-121   Footer
	
	//Edits table.
	long long temp;
	temp =  width              ; for(int a = 8; a < 12; a++) {entry_1[a] = (temp % 256); temp /= 256;} //Entry 1: width.
	temp = height              ; for(int a = 8; a < 12; a++) {entry_2[a] = (temp % 256); temp /= 256;} //Entry 2: height.
	temp = height              ; for(int a = 8; a < 12; a++) {entry_8[a] = (temp % 256); temp /= 256;} //Entry 8: RowsPerStrip.
	temp = (width * height) * 3; for(int a = 8; a < 12; a++) {entry_9[a] = (temp % 256); temp /= 256;} //Entry 9: bytes of pixel data.
	
	//Writes table to file.
	out_stream.open("append_to_me.tiff");
	for(int a = 0; a <  8; a++) {out_stream.put( header[a]);}
	for(int a = 0; a <  2; a++) {out_stream.put(entries[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_1[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_2[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_3[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_4[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_5[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_6[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_7[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_8[a]);}
	for(int a = 0; a < 12; a++) {out_stream.put(entry_9[a]);}
	for(int a = 0; a <  4; a++) {out_stream.put( footer[a]);}
	out_stream.close();
	
	
	
	
	
	//Sample image (you may remove the following.)
	in_stream.open("append_to_me.tiff"); out_stream.open("sample_copy_with_random_bytes_appended.tiff"); char file_byte;          //Makes copy of header file.
	for(int a = 0; a < 122; a++) {in_stream.get(file_byte); out_stream.put(file_byte);} in_stream.close(); out_stream.close();
	
	out_stream.open("sample_copy_with_random_bytes_appended.tiff", ios::app);                                                     //Appends to copy of header file.
	srand(17); for(int a = 0; a < (width * height) * 3; a++) {out_stream.put((rand() % 256));} out_stream.close();
}
