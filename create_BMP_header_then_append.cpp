//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
long long  width_in_pixels = 500;
long long height_in_pixels = 500;

//Creates 54-byte BMP header file, to which you may append
//pixel values (3 bytes per pixel; for red, green, and blue.
//Each byte: 0 to 255. It's OK if too many or too few bytes.
//You may append data over time, not necessarily all at once.

//Image viewers render BMP pixels left-to-right, bottom-up.
//Each row is (width_in_pixels * 3) bytes long.

//No compression! File size will be: 54-byte header + (width_in_pixels * height_in_pixels * 3-byte pixel)

//Bytes 0,0,255 make red   pixel.
//Bytes 0,255,0 make green pixel.
//Bytes 255,0,0 make blue  pixel.

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Creates header file.
	long long temp;
	out_stream.open("append_to_me.bmp");
	out_stream <<   "B";                                    //  0    File type
	out_stream <<   "M";                                    //  1    File type
	temp = ((width_in_pixels * height_in_pixels) * 3) + 54;
	out_stream.put(temp % 256); temp /= 256;                //  2    BMP size with header
	out_stream.put(temp % 256); temp /= 256;                //  3    BMP size with header
	out_stream.put(temp % 256); temp /= 256;                //  4    BMP size with header
	out_stream.put(temp % 256); temp /= 256;                //  5    BMP size with header
	out_stream.put(  0);                                    //  6
	out_stream.put(  0);                                    //  7
	out_stream.put(  0);                                    //  8
	out_stream.put(  0);                                    //  9
	out_stream.put( 54);                                    // 10
	out_stream.put(  0);                                    // 11
	out_stream.put(  0);                                    // 12
	out_stream.put(  0);                                    // 13
	out_stream.put( 40);                                    // 14
	out_stream.put(  0);                                    // 15
	out_stream.put(  0);                                    // 16
	out_stream.put(  0);                                    // 17
	temp = width_in_pixels;
	out_stream.put(temp % 256); temp /= 256;                // 18    Width
	out_stream.put(temp % 256); temp /= 256;                // 19    Width
	out_stream.put(temp % 256); temp /= 256;                // 20    Width
	out_stream.put(temp % 256); temp /= 256;                // 21    Width
	temp = height_in_pixels;
	out_stream.put(temp % 256); temp /= 256;                // 22    Height
	out_stream.put(temp % 256); temp /= 256;                // 23    Height
	out_stream.put(temp % 256); temp /= 256;                // 24    Height
	out_stream.put(temp % 256); temp /= 256;                // 25    Height
	out_stream.put(  1);                                    // 26
	out_stream.put(  0);                                    // 27
	out_stream.put( 24);                                    // 28
	out_stream.put(  0);                                    // 29
	out_stream.put(  0);                                    // 30
	out_stream.put(  0);                                    // 31
	out_stream.put(  0);                                    // 32
	out_stream.put(  0);                                    // 33
	temp = (width_in_pixels * height_in_pixels) * 3;
	out_stream.put(temp % 256); temp /= 256;                // 34    BMP size without header
	out_stream.put(temp % 256); temp /= 256;                // 35    BMP size without header
	out_stream.put(temp % 256); temp /= 256;                // 36    BMP size without header
	out_stream.put(temp % 256); temp /= 256;                // 37    BMP size without header
	out_stream.put(  0);                                    // 38
	out_stream.put(  0);                                    // 39
	out_stream.put(  0);                                    // 40
	out_stream.put(  0);                                    // 41
	out_stream.put(  0);                                    // 42
	out_stream.put(  0);                                    // 43
	out_stream.put(  0);                                    // 44
	out_stream.put(  0);                                    // 45
	out_stream.put(  0);                                    // 46
	out_stream.put(  0);                                    // 47
	out_stream.put(  0);                                    // 48
	out_stream.put(  0);                                    // 49
	out_stream.put(  0);                                    // 50
	out_stream.put(  0);                                    // 51
	out_stream.put(  0);                                    // 52
	out_stream.put(  0);                                    // 53
	out_stream.close();
	
	
	
	
	
	//Sample image (you may remove the following.)
	
	//Makes copy of header file.
	in_stream.open("append_to_me.bmp"); out_stream.open("sample_copy_with_random_bytes_appended.bmp"); char file_byte;
	for(int a = 0; a < 54; a++) {in_stream.get(file_byte); out_stream.put(file_byte);} in_stream.close(); out_stream.close();
	
	//Appends to copy of header file.
	out_stream.open("sample_copy_with_random_bytes_appended.bmp", ios::app);
	srand(17); for(int a = 0; a < (width_in_pixels * height_in_pixels) * 3; a++) {out_stream.put((rand() % 256));}
	out_stream.close();
}
