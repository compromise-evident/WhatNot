/// quick-file-renamer - makes copies and renames entire file name. You
///                      may add extensions, and interject on line 150.


#include <fstream>
#include <iostream>
using namespace std;

int main()
{	//                               user knobs

	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                  /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\                      ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	char renaming[10000] = {"Renamed_files/00000000000000001"}; //You may add an extension after the 1. For example: 00000000000000001.png
	//                                                          //All new files will have that extension.
	
	/*////////////////                                        \\\\\\\\\\\\\\\\\\
	///////////////////////                              \\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////                      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
	
	ifstream in_stream;
	ofstream out_stream;
	
	//Gets path to FOLDER from user.
	cout << "\nDrag & drop FOLDER into terminal or enter path:\n";
	
	//..........Gets path then fixes it if drag-n-dropped, regardless of single-quote presence and "enter"
	//..........not being cleared, meaning you can have options before this, where the user presses enter.
	char path_to_file[10000] = {'\0'};
	{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
		cin.getline(path_to_file, 10000);
		if(path_to_file[0] == '\0')
		{	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';}
			cin.getline(path_to_file, 10000);
		}
		if(path_to_file[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
		
		//..........Removes last space in path_to_file[].
		bool existence_of_last_space = false;
		for(int a = 9999; a > 0; a--)
		{	if(path_to_file[a] != '\0')
			{	if(path_to_file[a] == ' ') {path_to_file[a] = '\0'; existence_of_last_space = true;}
				break;
			}
		}
		
		//..........Removes encapsulating single-quotes in path_to_file[].
		bool existence_of_encapsulating_single_quotes = false;
		if(path_to_file[0] == '\'')
		{	for(int a = 0; a < 9999; a++)
			{	path_to_file[a] = path_to_file[a + 1];
				if(path_to_file[a] == '\0') 
				{	if(path_to_file[a - 1] != '\'') {cout << "\nBad path.\n"; return 0;}
					path_to_file[a - 1] = '\0';
					existence_of_encapsulating_single_quotes = true;
					break;
				}
			}
		}
		
		//..........Replaces all "'\''" with "'" in path_to_file[].
		int single_quote_quantity = 0;
		for(int a = 0; a < 10000; a++)
		{	if(path_to_file[a] == '\'') {single_quote_quantity++;}
		}
		
		if((single_quote_quantity                     >    0)
		&& (existence_of_last_space                  == true)
		&& (existence_of_encapsulating_single_quotes == true))
		{	if((single_quote_quantity % 3) != 0) {cout << "\nBad path.\n"; return 0;}
			
			for(int a = 0; a < 9997; a++)
			{	if(path_to_file[a] == '\'')
				{	int temp = (a + 1);
					for(; temp < 9997; temp++)
					{	path_to_file[temp] = path_to_file[temp + 3];
					}
				}
			}
		}
	}
	
	//Checks if FOLDER exists.
	in_stream.open(path_to_file);
	if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nNo such directory.\n"; return 0;}
	in_stream.close();
	
	//Gets location of the first encountered end-null coming from the left in path_to_file[].
	int path_to_file_null_bookmark;
	for(int a = 0; a < 10000; a++) {if(path_to_file[a] == '\0') {path_to_file_null_bookmark = a; break;}}
	
	//Gets list of file names from given directory.
	char ls[10000] = {"ls "};
	for(int a = 0; path_to_file[a] != '\0'; a++) {ls[a + 3] = path_to_file[a];} //..........Appends given path.
	ls[path_to_file_null_bookmark + 3] = ' '; //..........Appends commands.
	ls[path_to_file_null_bookmark + 4] = '>';
	ls[path_to_file_null_bookmark + 5] = ' ';
	ls[path_to_file_null_bookmark + 6] = 'f';
	system(ls);
	
	//Checks if FOLDER is empty.
	in_stream.open("f");
	char sniffed_one_file_character;
	in_stream.get(sniffed_one_file_character);
	if(in_stream.eof() == true) {in_stream.close(); cout << "\n\nNothing to process, the FOLDER is empty.\n"; return 0;}
	in_stream.close();
	
	//Counts number of files.
	long long number_of_files = 0;
	char garbage_byte;
	char temp_garbage_byte;
	in_stream.open("f");
	in_stream.get(garbage_byte);
	for(; in_stream.eof() == false;)
	{	if(garbage_byte == '\n') {number_of_files++;}
		temp_garbage_byte = garbage_byte;
		in_stream.get(garbage_byte);
	}
	in_stream.close();
	
	if(temp_garbage_byte != '\n') {number_of_files++;}
	
	//Begins.
	cout << "\n";
	path_to_file[path_to_file_null_bookmark] = '/';
	path_to_file_null_bookmark++;
	system("mkdir -p Renamed_files");
	long long file_name_bytes_read_bookmark = -1;
	long long renaming_arithmetic = 1000000000000000001;
	for(long long a = 0; a < number_of_files; a++)
	{	//..........Loads path_to_file[] with file name.
		in_stream.open("f");
		file_name_bytes_read_bookmark++;
		for(long long b = 0; b < file_name_bytes_read_bookmark; b++) {in_stream.get(garbage_byte);} //..........Skips name Bytes that have been read.
		
		int path_to_file_write_bookmark = path_to_file_null_bookmark;
		in_stream.get(garbage_byte);
		for(; garbage_byte != '\n';)
		{	path_to_file[path_to_file_write_bookmark] = garbage_byte;
			path_to_file_write_bookmark++;
			file_name_bytes_read_bookmark++;
			in_stream.get(garbage_byte);
			
			if(in_stream.eof() == true) {cout << "\nError 1\n"; return 0;}
		}
		in_stream.close();
		
		path_to_file[path_to_file_write_bookmark] = '\0';
		
		//..........Creates new name for the file.
		long long temp_renaming_arithmetic = renaming_arithmetic;
		for(int b = 30; b > 13; b--)
		{	renaming[b] = (temp_renaming_arithmetic % 10);
			renaming[b] += 48;
			
			temp_renaming_arithmetic /= 10;
		}
		
		renaming_arithmetic++;
		
		//..........Copies file to working directory and renames it.
		in_stream.open(path_to_file);
		out_stream.open(renaming);
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	
			/*####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*######
			##'                                         '##
			#         modify/sniff/count/redirect         #
			#              garbage_byte here              #
			##,                                         ,##
			####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/
			
			out_stream.put(garbage_byte);
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		out_stream.close();
		
		cout << (a + 1) << " of " << number_of_files << " done.\n";
	}
	
	remove("f");
}





/*#######*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                              TLDR: run it                              '###
##                                                                            ##
#,                                                                            ,#
#'                              apt install g++                               '#
##                           g++ /path/this_file.cpp                          ##
###,                          /path/resulting_file                          ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#######*/

/*How to alter this code - Software package repositories for GNU+Linux operating
systems have all the tools you can imagine. Open a terminal and use this command
as root to install Geany and g++ on your computer: apt install geany g++   Geany
is a fast & lightweight text editor and Integrated Development Environment where
you can write and run code. g++ is the GNU compiler for C++  (industry standard)
which creates an executable file out of written code. It also displays errors in
code as you will see in the lower Geany box. Make a new folder somewhere on your
machine. Paste this code into Geany. For clarity in auditing, enable indentation
guides: go to View >> Show Indentation Guides. Save the document as anything.cpp
within the newly-created folder. Use these shortcuts to run the program: F9, F5.
Once  F9  is used, it needs not be used again unless you had modified this code.
You may paste over this code with other  .cpp files, or open a new tab & repeat.
Additionally, executables created by the  F9  command can be drag & dropped into
terminals (lazy directory pasting) so the executable can run.  exe is in folder.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to make an executable with g++  -  Save this program as anything.cpp, open a
terminal, and type g++ then space. Drag & drop this saved file into the terminal
and its directory will be  appended to your pending entry. Click on the terminal
and press enter.   a.out now resides in the user directory, you may rename it to
anything.  To run that executable, simply drag and drop it into a terminal, then
click on the terminal and press enter.  Reminder:  executable's effect-directory
is /home/user or where you put the executable. Opening  .cpp  files in Geany and
hitting F9 creates the same executable--movable, renameable, drag & droppable.*/
