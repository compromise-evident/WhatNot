/// quick-security-camera - webcam auto-capture (auto-detects.) Interject       Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                         with image manipulation and shutdown-triggers
///                         (best for pre-boot encrypted.)


// Just do apt install fswebcam

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
	
	long long seconds_to_sleep_between_image_capture =        1; //Default:     1, min: 1, max: 10^18.
	
	long long number_of_images_to_capture = 1000000000000000000; //Default: 10^18, min: 1, max: 10^18.
	
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
	
	//Tests 2 possible webcams.
	system("clear");
	cout << "Detecting webcams...\n";
	system("fswebcam -q --no-banner Primary.jpg");
	system("clear");
	
	system("clear");
	cout << "Detecting webcams...\n";
	system("fswebcam -q --no-banner --device /dev/video2 Secondary.jpg");
	system("clear");
	
	bool presence_of_primary_webcam   = false;
	bool presence_of_secondary_webcam = false;
	
	in_stream.open("Primary.jpg");
	if(in_stream.fail() == false) {presence_of_primary_webcam   = true;}
	in_stream.close();
	
	in_stream.open("Secondary.jpg");
	if(in_stream.fail() == false) {presence_of_secondary_webcam = true;}
	in_stream.close();
	
	system("clear");
	if(presence_of_primary_webcam   == true) {cout << "  Primary webcam : present.\n";}
	else                                     {cout << "  Primary webcam : missing.\n";}
	
	if(presence_of_secondary_webcam == true) {cout << "Secondary webcam : present.\n";}
	else                                     {cout << "Secondary webcam : missing.\n";}
	
	cout << "        Priority : external.\n\n";
	
	if((presence_of_primary_webcam == false) && (presence_of_secondary_webcam == false))
	{	cout << "No webcams detected.\n\n"
		     << "Do \"apt install fswebcam\"\n\n"
		     << "Try plugging in the webcam half way into the USB port.\n\n";
		
		return 0;
	}
	
	remove("Primary.jpg"  );
	remove("Secondary.jpg");
	
	//Creates commands (you may edit these two, but do not modify the name "a.jpg".)
	char fswebcam_primary  [10000] = {"fswebcam -q --no-banner Images/a.jpg"                     }; //..........For on-board webcam.
	char fswebcam_secondary[10000] = {"fswebcam -q --no-banner --device /dev/video2 Images/a.jpg"}; //..........For external webcam.
	
	char final_command[10000];
	for(int a = 0; a < 10000; a++)
	{	if(presence_of_secondary_webcam == true) {final_command[a] = fswebcam_secondary[a];}
		else                                     {final_command[a] = fswebcam_primary  [a];}
	}
	
	int final_command_null_bookmark = 1;
	for(int a = 0; a < 10000; a++)
	{	if(final_command[a] != '\0') {final_command_null_bookmark++;}
	}
	final_command_null_bookmark -= 6;
	
	
	
	
	
	//Begins.
	char garbage_byte;
	for(long long loop = 1;; loop++)
	{	system("mkdir Images -p"                    );
		system("date"                               );
		system("date --rfc-3339=seconds > last_time");
		
		in_stream.open("last_time");
		int final_command_write_bookmark = final_command_null_bookmark;
		
		for(int a = 0; a < 19; a++)
		{	in_stream.get(garbage_byte);
			
			if(garbage_byte == 32) {final_command[final_command_write_bookmark] = '_'         ;}
			else                   {final_command[final_command_write_bookmark] = garbage_byte;}
			
			final_command_write_bookmark++;
		}
		in_stream.close();
		
		final_command[final_command_write_bookmark    ] = '_';
		final_command[final_command_write_bookmark + 1] = '_';
		final_command[final_command_write_bookmark + 2] = '_';
		final_command_write_bookmark += 3;
		
		system("date > last_time");
		
		in_stream.open("last_time");
		for(int a = 0; a < 31; a++)
		{	in_stream.get(garbage_byte);
			
			if(garbage_byte == 32) {final_command[final_command_write_bookmark] = '_'         ;}
			else                   {final_command[final_command_write_bookmark] = garbage_byte;}
			
			final_command_write_bookmark++;
		}
		in_stream.close();
		
		final_command[final_command_write_bookmark    ] = '.';
		final_command[final_command_write_bookmark + 1] = 'j';
		final_command[final_command_write_bookmark + 2] = 'p';
		final_command[final_command_write_bookmark + 3] = 'g';
		final_command[final_command_write_bookmark + 4] ='\0';
		
		//Captures image.
		system(final_command);
		
		if(loop == number_of_images_to_capture) {break;}
		for(long long a = 0; a < seconds_to_sleep_between_image_capture; a++) {system("sleep 1");}
	}
}

/*You can even retrieve / delete images via local network.

* The machine running this should have the Gnome DE.
  Go to Settings, Sharing. Enable sharing, then enable
  "File Sharing" without password. This creates the "Public"
  folder in /home/user/ if missing.
* Run this in a folder in /home/user/Public
* Now any machine on the network has full read / write access
  to that "Public" folder. Find it in your files browser
  in "Browse Network" / "Other Locations".         */
