/// Creates MNIST actual images and textual labels, by transforming MNIST.


//Needs all MNIST files:   t10k-labels.idx1-ubyte
//                         t10k-images.idx3-ubyte
//                        train-labels.idx1-ubyte
//                        train-images.idx3-ubyte

//Creates 2 text files:   10k-labels.txt
//                        60k-labels.txt

//Creates 2 folders:    > 10k-test  (folder with
//                        10,000 actual BMP images:
//                        54-byte header, then bytes
//                        0 or 255 for 3 bytes per
//                        pixel. 28x28 images.)
//                      > 60k-train (folder with
//                        60,000 such images not
//                        found among the 10k.)

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Checks if MNIST files present. (Download them from "tinygrad/teenygrad" on GitHub.)
	bool all_4 = true; cout << "\n";
	in_stream.open( "t10k-labels.idx1-ubyte"); if(in_stream.fail() == true) {all_4 = false; cout << " t10k-labels.idx1-ubyte  missing\n";} in_stream.close();
	in_stream.open( "t10k-images.idx3-ubyte"); if(in_stream.fail() == true) {all_4 = false; cout << " t10k-images.idx3-ubyte  missing\n";} in_stream.close();
	in_stream.open("train-labels.idx1-ubyte"); if(in_stream.fail() == true) {all_4 = false; cout << "train-labels.idx1-ubyte  missing\n";} in_stream.close();
	in_stream.open("train-images.idx3-ubyte"); if(in_stream.fail() == true) {all_4 = false; cout << "train-images.idx3-ubyte  missing\n";} in_stream.close();
	if(all_4 == false) {return 0;}
	
	system("mkdir imgMNIST           -p");
	system("mkdir imgMNIST/10k-test  -p");
	system("mkdir imgMNIST/60k-train -p");
	char file_byte;
	
	//Creates 10k-labels.txt.
	cout << "Creating 10k-labels.txt\n";
	in_stream.open ("t10k-labels.idx1-ubyte" );
	out_stream.open("imgMNIST/10k-labels.txt");
	for(int a = 0; a <     8; a++) {in_stream.get(file_byte)                                                    ;} //Skips 8-byte header.
	for(int a = 0; a < 10000; a++) {in_stream.get(file_byte); out_stream.put(file_byte + 48); out_stream << "\n";} //Copies & corrects 10,000 bytes.
	in_stream.close();
	out_stream.close();
	
	//Creates 60k-labels.txt.
	cout << "Creating 60k-labels.txt\n";
	in_stream.open ("train-labels.idx1-ubyte");
	out_stream.open("imgMNIST/60k-labels.txt");
	for(int a = 0; a <     8; a++) {in_stream.get(file_byte)                                                    ;} //Skips 8-byte header.
	for(int a = 0; a < 60000; a++) {in_stream.get(file_byte); out_stream.put(file_byte + 48); out_stream << "\n";} //Copies & corrects 60,000 bytes.
	in_stream.close();
	out_stream.close();
	
	//Creates images in folder 10k-test.
	cout << "Creating 10k-test\n";
	in_stream.open("t10k-images.idx3-ubyte");
	for(int a = 0; a < 16; a++) {in_stream.get(file_byte);} //Skips 16-byte header.
	int name_arithmetic_10k = 1000000001;
	char file_name_10k[100] = {"imgMNIST/10k-test/00001.bmp"};
	for(int total = 0; total < 10000; total++)
	{	//Makes file name.
		int temp_name_arithmetic = name_arithmetic_10k;
		for(int a = 22; a >= 18; a--) {file_name_10k[a] = ((temp_name_arithmetic % 10) + 48); temp_name_arithmetic /= 10;}
		name_arithmetic_10k++;
		out_stream.open(file_name_10k);
		
		//Writes 54-byte BMP header.
		out_stream.put( 66); //  1    file type ("B")
		out_stream.put( 77); //  2    file type ("M")
		out_stream.put(102); //  3    BMP size in bytes (bytes 0,0,9,102 = 00000000000000000000100101100110 = 2406-byte BMP)     MODIFY THIS!
		out_stream.put(  9); //  4    BMP size in bytes
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
		out_stream.put( 28); // 19    width in pixels (not sub-pixels)  (bytes 0,0,0,28 = 00000000000000000000000000011100 = 28)     MODIFY THIS!
		out_stream.put(  0); // 20    width in pixels (not sub-pixels)
		out_stream.put(  0); // 21    width in pixels (not sub-pixels)
		out_stream.put(  0); // 22    width in pixels (not sub-pixels)
		out_stream.put( 28); // 23    height in pixels (not sub-pixels) (bytes 0,0,0,28 = 00000000000000000000000000011100 = 28)     MODIFY THIS!
		out_stream.put(  0); // 24    height in pixels (not sub-pixels)
		out_stream.put(  0); // 25    height in pixels (not sub-pixels)
		out_stream.put(  0); // 26    height in pixels (not sub-pixels)
		out_stream.put(  1); // 27    color planes (must be 1)
		out_stream.put(  0); // 28    color planes
		out_stream.put( 24); // 29    bits per pixel (can be 1 or 24)
		for(int a = 0; a < 25; a++) {out_stream.put(0);} // 25 zeros
		
		char input[784] = {0}; for(int a = 0; a < 784; a++) {in_stream.get(input[a]);}                       //Gets 784 bytes.
		char flip[784] = {0}; for(int normal = 0, a = 783; a >= 0; a--, normal++) {flip[normal] = input[a];} //Flips order.
		
		//Writes pixel data, flipping each 28--on top of it already being flipped, because BMPs are a mess.
		for(int a = 27; a < 784; a += 28)
		{	int temp_a = a;
			for(int b = 0; b < 28; b++)
			{	if(flip[temp_a] < 0) {out_stream.put(  0); out_stream.put(  0); out_stream.put(  0);}
				else                 {out_stream.put(255); out_stream.put(255); out_stream.put(255);}
				temp_a--;
			}
		}
		
		out_stream.close();
	}
	in_stream.close();
	
	//Creates images in folder 60k-train.
	cout << "Creating 60k-train\n";
	in_stream.open("train-images.idx3-ubyte");
	for(int a = 0; a < 16; a++) {in_stream.get(file_byte);} //Skips 16-byte header.
	int name_arithmetic_60k = 1000000001;
	char file_name_60k[100] = {"imgMNIST/60k-train/00001.bmp"};
	for(int total = 0; total < 60000; total++)
	{	//Makes file name.
		int temp_name_arithmetic = name_arithmetic_60k;
		for(int a = 23; a >= 19; a--) {file_name_60k[a] = ((temp_name_arithmetic % 10) + 48); temp_name_arithmetic /= 10;}
		name_arithmetic_60k++;
		out_stream.open(file_name_60k);
		
		//Writes 54-byte BMP header.
		out_stream.put( 66); //  1    file type ("B")
		out_stream.put( 77); //  2    file type ("M")
		out_stream.put(102); //  3    BMP size in bytes (bytes 0,0,9,102 = 00000000000000000000100101100110 = 2406-byte BMP)     MODIFY THIS!
		out_stream.put(  9); //  4    BMP size in bytes
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
		out_stream.put( 28); // 19    width in pixels (not sub-pixels)  (bytes 0,0,0,28 = 00000000000000000000000000011100 = 28)     MODIFY THIS!
		out_stream.put(  0); // 20    width in pixels (not sub-pixels)
		out_stream.put(  0); // 21    width in pixels (not sub-pixels)
		out_stream.put(  0); // 22    width in pixels (not sub-pixels)
		out_stream.put( 28); // 23    height in pixels (not sub-pixels) (bytes 0,0,0,28 = 00000000000000000000000000011100 = 28)     MODIFY THIS!
		out_stream.put(  0); // 24    height in pixels (not sub-pixels)
		out_stream.put(  0); // 25    height in pixels (not sub-pixels)
		out_stream.put(  0); // 26    height in pixels (not sub-pixels)
		out_stream.put(  1); // 27    color planes (must be 1)
		out_stream.put(  0); // 28    color planes
		out_stream.put( 24); // 29    bits per pixel (can be 1 or 24)
		for(int a = 0; a < 25; a++) {out_stream.put(0);} // 25 zeros
		
		char input[784] = {0}; for(int a = 0; a < 784; a++) {in_stream.get(input[a]);}                       //Gets 784 bytes.
		char flip[784] = {0}; for(int normal = 0, a = 783; a >= 0; a--, normal++) {flip[normal] = input[a];} //Flips order.
		
		//Writes pixel data, flipping each 28--on top of it already being flipped, because BMPs are a mess.
		for(int a = 27; a < 784; a += 28)
		{	int temp_a = a;
			for(int b = 0; b < 28; b++)
			{	if(flip[temp_a] < 0) {out_stream.put(  0); out_stream.put(  0); out_stream.put(  0);}
				else                 {out_stream.put(255); out_stream.put(255); out_stream.put(255);}
				temp_a--;
			}
		}
		
		out_stream.close();
	}
	in_stream.close();
}
