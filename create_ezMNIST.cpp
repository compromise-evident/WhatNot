/// Creates ezMNIST from MNIST.


//Needs all MNIST files:   t10k-labels.idx1-ubyte
//                         t10k-images.idx3-ubyte
//                        train-labels.idx1-ubyte
//                        train-images.idx3-ubyte

//Creates 2 text files: > test-ezMNIST.txt has 10,000 lines.
//                        Each line has a  "label"  digit,
//                        then 784 characters representing
//                        28x28 image of handwritten digit.
//                        You can manually stack every 28
//                        and an image will show up, or
//                        see visual_for_you.txt where
//                        that's already done for you.
//                      > train-ezMNIST.txt has 60,000 such
//                        lines not found among the 10k.
//                        This "pixel data" from both
//                        files can be used directly
//                        by ML handling MNIST.

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
	
	system("mkdir ezMNIST -p");
	char file_byte;
	
	//Grabs & holds 10k labels.
	cout << "Creating  test-ezMNIST.txt\n";
	in_stream.open("t10k-labels.idx1-ubyte");
	char labels_10k[10000] = {'\0'};
	for(int a = 0; a <     8; a++) {in_stream.get(labels_10k[0])                     ;} //Skips 8-byte header.
	for(int a = 0; a < 10000; a++) {in_stream.get(labels_10k[a]); labels_10k[a] += 48;}
	in_stream.close();
	
	//Creates test-ezMNIST.txt.
	in_stream.open ("t10k-images.idx3-ubyte"  );
	out_stream.open("ezMNIST/test-ezMNIST.txt");
	for(int a = 0; a < 16; a++) {in_stream.get(file_byte);} //Skips 16-byte header.
	for(int total = 0; total < 10000; total++)
	{	out_stream << labels_10k[total] << " ";
		for(int a = 0; a < 784; a++)
		{	in_stream.get(file_byte);
			
			/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
			##'                                         '##
			#         These  bytes  can  be  used         #
			#        directly by ML handling MNIST        #
			##,                                         ,##
			####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
			if(file_byte < 0) {out_stream << "ÿ";} //Tokenized as high in pqML, different from tokenizing user's training-data. This is byte 255 = 11111111.
			else              {out_stream << "-";} //Tokenized as low  in pqML, different from tokenizing user's training-data. This is byte  45 = 00101101.
		}
		out_stream << "\n";
	}
	in_stream.close();
	out_stream.close();
	
	//Grabs & holds 60k labels.
	cout << "Creating train-ezMNIST.txt\n";
	in_stream.open("train-labels.idx1-ubyte");
	char labels_60k[60000] = {'\0'};
	for(int a = 0; a <     8; a++) {in_stream.get(labels_60k[0])                     ;} //Skips 8-byte header.
	for(int a = 0; a < 60000; a++) {in_stream.get(labels_60k[a]); labels_60k[a] += 48;}
	in_stream.close();
	
	//Creates train-ezMNIST.txt.
	in_stream.open ("train-images.idx3-ubyte"  );
	out_stream.open("ezMNIST/train-ezMNIST.txt");
	for(int a = 0; a < 16; a++) {in_stream.get(file_byte);} //Skips 16-byte header.
	for(int total = 0; total < 60000; total++)
	{	out_stream << labels_60k[total] << " ";
		for(int a = 0; a < 784; a++)
		{	in_stream.get(file_byte);
			
			/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
			##'                                         '##
			#         These  bytes  can  be  used         #
			#        directly by ML handling MNIST        #
			##,                                         ,##
			####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
			if(file_byte < 0) {out_stream << "ÿ";} //Tokenized as high in pqML, different from tokenizing user's training-data. This is byte 255 = 11111111.
			else              {out_stream << "-";} //Tokenized as low  in pqML, different from tokenizing user's training-data. This is byte  45 = 00101101.
		}
		out_stream << "\n";
	}
	in_stream.close();
	out_stream.close();
	
	
	
	
	
	//Creates visual_for_you.txt.
	cout << "Creating a visual\n";
	in_stream.open ("t10k-images.idx3-ubyte"    );
	out_stream.open("ezMNIST/visual_for_you.txt");
	for(int a = 0; a < 16; a++) {in_stream.get(file_byte);} //Skips 16-byte header.
	for(int total = 0; total < 10000; total++)
	{	for(int a = 0; a < 28; a++)
		{	for(int b = 0; b < 28; b++)
			{	in_stream.get(file_byte);
				if(file_byte < 0) {out_stream << "ÿ";}
				else              {out_stream << "-";}
			}
			
			//Info for each.
			if(a == 0) {out_stream << " " << labels_10k[total] << "     test " << (total + 1);}
			
			out_stream << "\n";
		}
		out_stream << "\n\n";
	}
	in_stream.close();
	out_stream.close();
	
	//Appends to visual_for_you.txt.
	in_stream.open ("train-images.idx3-ubyte"             );
	out_stream.open("ezMNIST/visual_for_you.txt", ios::app);
	out_stream << "\n\n\n\n\n\n\n";
	for(int a = 0; a < 16; a++) {in_stream.get(file_byte);} //Skips 16-byte header.
	for(int total = 0; total < 60000; total++)
	{	for(int a = 0; a < 28; a++)
		{	for(int b = 0; b < 28; b++)
			{	in_stream.get(file_byte);
				if(file_byte < 0) {out_stream << "ÿ";}
				else              {out_stream << "-";}
			}
			
			//Info for each.
			if(a == 0) {out_stream << " " << labels_60k[total] << "     train " << (total + 1);}
			
			out_stream << "\n";
		}
		out_stream << "\n\n";
	}
	in_stream.close();
	out_stream.close();
}
