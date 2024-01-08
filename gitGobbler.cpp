/// gitGobbler - downloads, unzips, & de-folderizes GitHub repos.
///              Make a file "names" with 1 name per line.
///              Example: "username/repository".


#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	
	//Checks if file exists (failure can be bad path info as well.)
	in_stream.open("names");
	if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nFile \"names\" is missing.\n";              return 0;}
	char sniffed_one_file_character;
	in_stream.get(sniffed_one_file_character);
	if(in_stream.eof() == true) {in_stream.close();  cout << "\n\nNothing to process, \"names\" is empty.\n"; return 0;}
	in_stream.close();
	
	//Creates folder for the final downloads.
	char mkdir[10000] = "mkdir -p ";
	int skip_prepended_command_elements = 9;
	char garbage_byte;
	
	system("date --rfc-3339=seconds > last_time");
	in_stream.open("last_time");
	for(int a = 0; a < 19; a++)
	{	in_stream.get(garbage_byte);
		if(garbage_byte == 32) {mkdir[a + skip_prepended_command_elements] = '_'         ;}
		else                   {mkdir[a + skip_prepended_command_elements] = garbage_byte;}
	}
	in_stream.close();
	
	mkdir[19 + skip_prepended_command_elements] = '_';
	mkdir[20 + skip_prepended_command_elements] = '_';
	mkdir[21 + skip_prepended_command_elements] = '_';
	
	system("date > last_time");
	in_stream.open("last_time");
	for(int a = 22; a < 53; a++)
	{	in_stream.get(garbage_byte);
		if(garbage_byte == 32) {mkdir[a + skip_prepended_command_elements] = '_'         ;}
		else                   {mkdir[a + skip_prepended_command_elements] = garbage_byte;}
	}
	in_stream.close();
	
	system(mkdir);
	remove("last_time");
	
	//Counts number of repos.
	in_stream.open("names");
	long long number_of_repos = 0;
	char temp_garbage_byte;
	in_stream.get(garbage_byte);
	for(; in_stream.eof() == false;)
	{	if(garbage_byte == '\n') {number_of_repos++;}
		temp_garbage_byte = garbage_byte;
		in_stream.get(garbage_byte);
	}
	in_stream.close();
	
	if(temp_garbage_byte != '\n') {number_of_repos++;}
	
	
	
	
	
	//Begins.
	cout << "\n";
	long long repos_read_bookmark = -1;
	for(long long a = 0; a < number_of_repos; a++)
	{	//..........Loads a repo name.
		char temp_repo_name[10000] = {"\0"};
		int temp_repo_name_write_bookmark = 0;
		in_stream.open("names");
		repos_read_bookmark++;
		for(long long b = 0; b < repos_read_bookmark; b++) {in_stream.get(garbage_byte);} //..........Skips name Bytes that have been read.
		char wget[1000015] = {"wget -q -t 9 https://github.com/"};
		int wget_write_bookmark = 32;
		in_stream.get(garbage_byte);
		for(; garbage_byte != '\n';)
		{	wget[wget_write_bookmark] = garbage_byte;
			wget_write_bookmark++;
			repos_read_bookmark++;
			
			temp_repo_name[temp_repo_name_write_bookmark] = garbage_byte;
			temp_repo_name_write_bookmark++;
			
			in_stream.get(garbage_byte);
			if(in_stream.eof() == true) {break;}
		}
		in_stream.close();
		
		//..........Appends "/archive/refs/heads/main.zip".
		char appended_command_elements[10000] = {"/archive/refs/heads/main.zip"};
		for(int b = 0; b < 500; b++)
		{	wget[wget_write_bookmark] = appended_command_elements[b];
			wget_write_bookmark++;
		}
		
		//..........Downloads & prints the URL
		system(wget);
		for(int b = 21; b < wget_write_bookmark; b++) {cout << wget[b];}
		
		//..........Checks if downloaded.
		in_stream.open("main.zip");
		bool download_problem = false;
		if(in_stream.fail() == true) {download_problem = true;}
		in_stream.get(garbage_byte);
		if(in_stream.eof() == true)  {download_problem = true;}
		in_stream.close();
		
		//..........Reports on download.
		if(download_problem == true) {cout << "\n" << (a + 1) << "/" << number_of_repos << " FAILED!\n\n\n";}
		else                         {cout << "\n" << (a + 1) << "/" << number_of_repos <<         "\n\n\n";}
		
		//..........Extracts repo.
		char unzip[10000] = {"unzip -qq -j -d "};
		for(int b = 0; b < 500; b++) {unzip[b + 16] = mkdir[b + 9];}
		unzip[69] = '/';
		for(int b = 0; b < 500; b++)
		{	if(temp_repo_name[b] == '/') {unzip[b + 70] =               ':';}
			else                         {unzip[b + 70] = temp_repo_name[b];}
		}
		
		int unzip_null_bookmark; //..........Gets location of the first encountered end-null coming from the left in unzip[].
		for(int a = 0; a < 10000; a++) {if(unzip[a] == '\0') {unzip_null_bookmark = a; break;}}
		
		char appendix[10000] = {" main.zip"}; //..........Appends " main.zip" to unzip command.
		for(int b = 0; b < 500; b++)
		{	unzip[unzip_null_bookmark] = appendix[b];
			unzip_null_bookmark++;
		}
		
		//..........unzip[] looks like: unzip -qq -j -d 2023-12-03_22:38:22___Sun_03_Dec_2023_10:38:22_PM_MST/username:repository main.zip
		if(download_problem == false) {system(unzip);}
		remove("main.zip");
	}
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
