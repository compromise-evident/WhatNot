//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
long long  width = 500; //image  width in pixels
long long height = 500; //image height in pixels

/*Creates 122-byte TIFF header file,
to which you may append 3 bytes per pixel:
1st byte: intensity of red   sub-pixel.
2nd byte: intensity of green sub-pixel.
3rd byte: intensity of blue  sub-pixel.
From this, you get all the colors.
256 total intensities per sub-pixel;
byte 0 = no power, byte 255 = full power.
It's OK to append too many bytes. Pixels
will be rendered left-to-right, top-down.
Red    pixel: bytes 255,0,0
Green  pixel: bytes 0,255,0
Blue   pixel: bytes 0,0,255
Black  pixel: bytes 0,0,0
White  pixel: bytes 255,255,255
Gray   pixel: bytes n,n,n
Purple pixel: bytes 255,0,255

Creates also 122-byte TIFF header file,
to which you may append 1 byte per pixel:
one intensity for red, green, and blue.
From this, you get the full grayscale.
256 total intensities per pixel;
byte 0 = no power, byte 255 = full power.
It's OK to append too many bytes. Pixels
will be rendered left-to-right, top-down.
Black pixel: byte 0
White pixel: byte 255
Gray  pixel: byte n */

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ofstream out_stream;
	long long temp;
	
	//Header bytes.
	int bytes[122] =
	{	73,73,      42,0,       8,0,0,0,        9,0,            //Number of entries                                   0-9
		0,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 1: width                                     10-21
		1,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 2: height                                    22-33
		2,1,        4,0,        1,0,0,0,        8,0,0,0,        //Entry 3: bits per sub-pixel                        34-45
		3,1,        4,0,        1,0,0,0,        1,0,0,0,        //Entry 4: compression (1 = none)                    46-57
		6,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 5: RGB/grayscale                             58-69
		17,1,       4,0,        1,0,0,0,        122,0,0,0,      //Entry 6: byte index where pixel data begins        70-81
		21,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 7: sub-pixels per pixel                      82-93
		22,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 8: load                                      94-105
		23,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 9: bytes of pixel data                      106-117
		0,0,0,0                                                 //End                                               118-121
	};
	
	//Edits header bytes for 3B/p.
	bytes[66] = 2;                                                                                       //Entry 5: RGB/grayscale
	bytes[90] = 3;                                                                                       //Entry 7: sub-pixels per pixel
	temp =  width              ; for(int a =  18; a <=  21; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 1: width
	temp = height              ; for(int a =  30; a <=  33; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 2: height
	temp = height              ; for(int a = 102; a <= 105; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 8: load
	temp = (width * height) * 3; for(int a = 114; a <= 117; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 9: bytes of pixel data
	out_stream.open("append_to_me_3_bytes_per_pixel.tiff"); for(int a = 0; a < 122; a++) {out_stream.put(bytes[a]);} out_stream.close();
	
	//Edits header bytes for 1B/p.
	bytes[66] = 1;                                                                                       //Entry 5: RGB/grayscale
	bytes[90] = 1;                                                                                       //Entry 7: sub-pixels per pixel
	temp =  width              ; for(int a =  18; a <=  21; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 1: width
	temp = height              ; for(int a =  30; a <=  33; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 2: height
	temp = height              ; for(int a = 102; a <= 105; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 8: load
	temp =  width * height     ; for(int a = 114; a <= 117; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 9: bytes of pixel data
	out_stream.open("append_to_me_1_byte_per_pixel.tiff"); for(int a = 0; a < 122; a++) {out_stream.put(bytes[a]);} out_stream.close();
}
