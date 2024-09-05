//Creates small 1782-byte BMP, 576 pixels, 24x24, 3 bytes per pixel.            Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
//Total pixels: 1728.

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ofstream out_stream;
	out_stream.open("custom.bmp");
	
	//54-byte BMP header.
	out_stream.put( 66); //  1    file type ("B")
	out_stream.put( 77); //  2    file type ("M")
	out_stream.put(246); //  3    BMP size in bytes (bytes 0,0,6,246 = 00000000000000000000011011110110 = 1782-byte BMP)     MODIFY THIS!
	out_stream.put(  6); //  4    BMP size in bytes
	out_stream.put(  0); //  5    BMP size in bytes
	out_stream.put(  0); //  6    BMP size in bytes
	out_stream.put(  0); //  7    reserved
	out_stream.put(  0); //  8    reserved
	out_stream.put(  0); //  9    reserved
	out_stream.put(  0); // 10    reserved
	out_stream.put( 54); // 11    total bytes before data
	out_stream.put(  0); // 12    total bytes before data
	out_stream.put(  0); // 13    total bytes before data
	out_stream.put(  0); // 14    total bytes before data
	out_stream.put( 40); // 15    size of header part 2
	out_stream.put(  0); // 16    size of header part 2
	out_stream.put(  0); // 17    size of header part 2
	out_stream.put(  0); // 18    size of header part 2
	out_stream.put( 24); // 19    width in pixels (not sub-pixels) (bytes 0,0,0,24 = 00000000000000000000000000011000 = 24)     MODIFY THIS!
	out_stream.put(  0); // 20    width in pixels (not sub-pixels)
	out_stream.put(  0); // 21    width in pixels (not sub-pixels)
	out_stream.put(  0); // 22    width in pixels (not sub-pixels)
	out_stream.put( 24); // 23    height in pixels (not sub-pixels) (bytes 0,0,0,24 = 00000000000000000000000000011000 = 24)     MODIFY THIS!
	out_stream.put(  0); // 24    height in pixels (not sub-pixels)
	out_stream.put(  0); // 25    height in pixels (not sub-pixels)
	out_stream.put(  0); // 26    height in pixels (not sub-pixels)
	out_stream.put(  1); // 27    color planes (must be 1)
	out_stream.put(  0); // 28    color planes
	out_stream.put( 24); // 29    bits per pixel (can be 1 or 24)
	for(int a = 0; a < 25; a++) {out_stream.put(0);} // 25 zeros
	
	
	
	
	
	//Appends pixel data (1728 bytes; 1728 = 576 pixels x 3.) Note, despite the red, green, blue order, the image starts from the bottom.
	for(int a = 0; a < 192; a++) {out_stream.put(  0); out_stream.put(  0); out_stream.put(255);} //Red    (left   sub-pixel)
	for(int a = 0; a < 192; a++) {out_stream.put(  0); out_stream.put(255); out_stream.put(  0);} //Green  (middle sub-pixel)
	for(int a = 0; a < 192; a++) {out_stream.put(255); out_stream.put(  0); out_stream.put(  0);} //Blue   (right  sub-pixel)
	//On a typical laptop screen, take a closer look at the image. Red box appears shifted left, blue box appears shifted right.
	//They're not shifted; for example, a red pixel has 3 sub-pixels; red, green, and blue, where green and blue are 0 (no light.)
	out_stream.close();
}
