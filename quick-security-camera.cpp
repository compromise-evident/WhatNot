/// quick-security-camera - webcam auto-capture (auto-detects.) Interject       Run it: "apt install g++ geany". Open this in Geany. Hit F9 once. F5 to run.
///                         with image manipulation and shutdown-triggers
///                         (best for pre-boot encrypted.) Input can be a
///                         smartphone via USB; use phone's webcam option.


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
	
	long long seconds_to_sleep_between_image_capture = 8; //Default: 8, min: 1, max: 10^18.
	
	long long number_of_images_to_capture = 1000000000000000000; //Default: 10^18, min: 1, max: 10^18.
	
	//You may edit these but don't change "a.jpg" and don't append. (Saves to folder "Images".)
	char fswebcam_primary  [10000] = {"fswebcam -q -r 1920x1080 --no-banner Images/a.jpg"                     }; //Command for on-board webcam.
	char fswebcam_secondary[10000] = {"fswebcam -q -r 1920x1080 --no-banner --device /dev/video2 Images/a.jpg"}; //Command for external webcam.
	
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
	
	in_stream.open("Primary.jpg"  ); if(in_stream.fail() == false) {presence_of_primary_webcam   = true;} in_stream.close();
	in_stream.open("Secondary.jpg"); if(in_stream.fail() == false) {presence_of_secondary_webcam = true;} in_stream.close();
	
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
	
	char final_command[10000];
	for(int a = 0; a < 10000; a++)
	{	if(presence_of_secondary_webcam == true) {final_command[a] = fswebcam_secondary[a];}
		else                                     {final_command[a] = fswebcam_primary  [a];}
	}
	
	int final_command_null_bookmark;
	for(int a = 0; a < 10000; a++)
	{	if(final_command[a] == '\0') {final_command_null_bookmark = a; break;}
	}
	final_command_null_bookmark -= 5;
	
	
	
	
	
	//Begins.
	long long unix_time_for_total_seconds_live = time(0);
	char garbage_byte;
	for(long long loop = 0; loop < number_of_images_to_capture; loop++)
	{	system("mkdir Images -p"                    );
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
		system(final_command); //Looks like: fswebcam -q -r 1920x1080 --no-banner Images/2024-11-19_19:02:03___Tue_Nov_19_07:02:03_PM_MST_2024.jpg
		
		//Takes its hash.
		char sha_command[10000] = "sha512sum Images/";
		int sha_command_write_bookmark = 17;
		for(int a = final_command_null_bookmark; final_command[a] != '\0'; a++)
		{	sha_command[sha_command_write_bookmark] = final_command[a];
			sha_command_write_bookmark++;
		}
		sha_command[sha_command_write_bookmark    ] = ' ';
		sha_command[sha_command_write_bookmark + 1] = '>';
		sha_command[sha_command_write_bookmark + 2] = '>';
		sha_command[sha_command_write_bookmark + 3] = ' ';
		sha_command[sha_command_write_bookmark + 4] = 's';
		sha_command[sha_command_write_bookmark + 5] = 'h';
		sha_command[sha_command_write_bookmark + 6] = 'a';
		sha_command[sha_command_write_bookmark + 7] ='\n';
		system(sha_command);
		
		system("date");
		out_stream.open("time_live");
		out_stream << (((time(0) - unix_time_for_total_seconds_live) / 60) / 60) / 24      << " days, "
		           << (((time(0) - unix_time_for_total_seconds_live) / 60) / 60)      % 24 << " hours, "
		           <<  ((time(0) - unix_time_for_total_seconds_live) / 60)            % 60 << " minutes, "
		           <<   (time(0) - unix_time_for_total_seconds_live)                  % 60 << " seconds\n\n";
		out_stream.close();
		
		cout       << (((time(0) - unix_time_for_total_seconds_live) / 60) / 60) / 24      << " days, "
		           << (((time(0) - unix_time_for_total_seconds_live) / 60) / 60)      % 24 << " hours, "
		           <<  ((time(0) - unix_time_for_total_seconds_live) / 60)            % 60 << " minutes, "
		           <<   (time(0) - unix_time_for_total_seconds_live)                  % 60 << " seconds\n\n";
		
		//Sleeps.
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
