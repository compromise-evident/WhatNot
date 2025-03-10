//YOUR CONTROLS:                                                                Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
bool black_digits_on_white_background = true; //(false = opposite)

//Needs both files "train.txt" and "test.txt" from extracted
//"training-data.tar.bz2" found on github.com/compromise-evident/ML

#include <fstream>
#include <iostream>
using namespace std;
int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Exits if missing needed files.
	int problems = 0;
	in_stream.open("train.txt"); if(in_stream.fail() == true) {cout << "\nMissing train.txt"; problems++;} in_stream.close();
	in_stream.open( "test.txt"); if(in_stream.fail() == true) {cout << "\nMissing  test.txt"; problems++;} in_stream.close();
	if(problems > 0) {return 0;}
	
	//Creates folders.
	system("mkdir -p hand_written_digits_images_and_labels");
	system("mkdir -p hand_written_digits_images_and_labels/60k_images");
	system("mkdir -p hand_written_digits_images_and_labels/10k_images");
	char file_byte;
	
	//Creates 60k_labels.txt.
	in_stream.open("train.txt");
	out_stream.open("hand_written_digits_images_and_labels/60k_labels.txt");
	for(int a = 0; a < 60000; a++)
	{	in_stream.get(file_byte); out_stream.put(file_byte); out_stream << "\n";
		for(int b = 0; b < 786; b++) {in_stream.get(file_byte);}
	}
	in_stream.close();
	out_stream.close();
	
	//Creates 10k_labels.txt.
	in_stream.open("test.txt");
	out_stream.open("hand_written_digits_images_and_labels/10k_labels.txt");
	for(int a = 0; a < 10000; a++)
	{	in_stream.get(file_byte); out_stream.put(file_byte); out_stream << "\n";
		for(int b = 0; b < 786; b++) {in_stream.get(file_byte);}
	}
	in_stream.close();
	out_stream.close();
	
	//Prepares for images.
	long long  width = 28;
	long long height = 28;
	
	int bytes[122] =
	{	73,73,      42,0,       8,0,0,0,        9,0,            //Number of entries                                   0-9
		0,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 1: width                                     10-21
		1,1,        4,0,        1,0,0,0,        0,0,0,0,        //Entry 2: height                                    22-33
		2,1,        4,0,        1,0,0,0,        8,0,0,0,        //Entry 3: bits per sub-pixel                        34-45
		3,1,        4,0,        1,0,0,0,        1,0,0,0,        //Entry 4: compression                               46-57
		6,1,        4,0,        1,0,0,0,        1,0,0,0,        //Entry 5: RGB                                       58-69                  was 2
		17,1,       4,0,        1,0,0,0,        122,0,0,0,      //Entry 6: byte index where pixel data begins        70-81
		21,1,       4,0,        1,0,0,0,        1,0,0,0,        //Entry 7: sub-pixels per pixel                      82-93                  was 3
		22,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 8: load                                      94-105
		23,1,       4,0,        1,0,0,0,        0,0,0,0,        //Entry 9: bytes of pixel data                      106-117
		0,0,0,0                                                 //End                                               118-121
	};
	
	long long temp;
	temp =  width              ; for(int a =  18; a <=  21; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 1: width
	temp = height              ; for(int a =  30; a <=  33; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 2: height
	temp = height              ; for(int a = 102; a <= 105; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 8: load
	temp =  width * height     ; for(int a = 114; a <= 117; a++) {bytes[a] = (temp % 256); temp /= 256;} //Entry 9: bytes of pixel data     was (width * height) * 3
	
	char path_to_train[10000] = {"hand_written_digits_images_and_labels/60k_images/00001.tiff"};
	char path_to_test [10000] = {"hand_written_digits_images_and_labels/10k_images/00001.tiff"};
	long long renaming_arithmetic;
	
	//Creates 60k_images.
	in_stream.open("train.txt");
	renaming_arithmetic = 1000000000000000001;
	for(int a = 0; a < 60000; a++)
	{	//Creates new name.
		long long temp_renaming_arithmetic = renaming_arithmetic;
		for(int b = 53; b > 48; b--)
		{	path_to_train[b] = (temp_renaming_arithmetic % 10) + 48;
			temp_renaming_arithmetic /= 10;
		}
		renaming_arithmetic++;
		
		//Creates file.
		out_stream.open(path_to_train);
		for(int b = 0; b < 122; b++) {out_stream.put(bytes[b]);}
		in_stream.get(file_byte); in_stream.get(file_byte);
		for(int b = 0; b < 784; b++)
		{	in_stream.get(file_byte);
			if(black_digits_on_white_background == true)
			{	if(file_byte == '-') {out_stream.put(255);}
				else                 {out_stream.put(  0);}
			}
			else
			{	if(file_byte == '-') {out_stream.put(  0);}
				else                 {out_stream.put(255);}
			}
		}
		in_stream.get(file_byte);
		out_stream.close();
	}
	in_stream.close();
	
	//Creates 10k_images.
	in_stream.open("test.txt");
	renaming_arithmetic = 1000000000000000001;
	for(int a = 0; a < 10000; a++)
	{	//Creates new name.
		long long temp_renaming_arithmetic = renaming_arithmetic;
		for(int b = 53; b > 48; b--)
		{	path_to_test[b] = (temp_renaming_arithmetic % 10) + 48;
			temp_renaming_arithmetic /= 10;
		}
		renaming_arithmetic++;
		
		//Creates file.
		out_stream.open(path_to_test);
		for(int b = 0; b < 122; b++) {out_stream.put(bytes[b]);}
		in_stream.get(file_byte); in_stream.get(file_byte);
		for(int b = 0; b < 784; b++)
		{	in_stream.get(file_byte);
			if(black_digits_on_white_background == true)
			{	if(file_byte == '-') {out_stream.put(255);}
				else                 {out_stream.put(  0);}
			}
			else
			{	if(file_byte == '-') {out_stream.put(  0);}
				else                 {out_stream.put(255);}
			}
		}
		in_stream.get(file_byte);
		out_stream.close();
	}
	in_stream.close();
}
