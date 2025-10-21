//YOUR CONTROLS:                                                                Run it: "apt install g++ geany fswebcam". Open the .cpp in Geany. Hit F9 once. F5 to run.
long long seconds_to_sleep_between_image_capture = 3;
long long number_of_images_to_capture = 1000000000000000000;

/*Webcam auto-capture. Input can also be a smartphone via USB; use phone's
webcam option in "more USB options" when connecting phone to computer.*/

//Just do "apt install fswebcam".

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	ofstream out_stream;
	
	//Detects webcams (priority: external.)
	system("mkdir temp -p");
	system("fswebcam -q -r 1920x1080 --no-banner                      temp/on_board_webcam_test.jpg");
	system("fswebcam -q -r 1920x1080 --no-banner --device /dev/video2 temp/external_webcam_test.jpg");
	
	system("clear"); system("clear");
	bool presence_of_on_board_webcam = false;
	bool presence_of_external_webcam = false;
	in_stream.open("temp/on_board_webcam_test.jpg"); if(in_stream.fail() == false) {presence_of_on_board_webcam = true;} in_stream.close();
	in_stream.open("temp/external_webcam_test.jpg"); if(in_stream.fail() == false) {presence_of_external_webcam = true;} in_stream.close();
	
	remove("temp/on_board_webcam_test.jpg");
	remove("temp/external_webcam_test.jpg");
	
	if((presence_of_on_board_webcam == false) && (presence_of_external_webcam == false))
	{	cout << "\nNo webcams detected. Try running this again.\n\n"
		     << "Do \"apt install fswebcam\"\n\n"
		     << "Try plugging in the webcam half way into the USB port.\n\n";
		
		return 0;
	}
	
	string command = "fswebcam -q -r 1920x1080 --no-banner ";
	if(presence_of_external_webcam == true) {command += " --device /dev/video2 ";}
	
	
	
	
	
	//Begins.
	system("mkdir Images -p");
	long long unix_time = time(0);
	for(long long loop = 0; loop < number_of_images_to_capture; loop++)
	{	//Makes file name, such as "2025-10-19_20:34:55___Sun_Oct_19_08:34:55_PM_MDT_2025".
		system("date --rfc-3339=seconds > temp/military_time");
		in_stream.open("temp/military_time");
		char military_time[20] = {'\0'}; for(int a = 0; a < 19; a++) {in_stream.get(military_time[a]);}
		in_stream.close();
		military_time[10] = '_';
		
		system("date > temp/civilian_time");
		in_stream.open("temp/civilian_time");
		char civilian_time[32] = {'\0'}; for(int a = 0; a < 31; a++) {in_stream.get(civilian_time[a]);}
		in_stream.close();
		for(int a = 0; a < 31; a++) {if(civilian_time[a] == ' ') {civilian_time[a] = '_';}}
		
		string str = command; str += "Images/"; str += military_time; str += "___"; str += civilian_time; str += ".jpg";
		
		//Takes a photo.
		system(str.c_str());
		
		//Keeps you posted.
		system("date");
		cout << (((time(0) - unix_time) / 60) / 60) / 24      << " days, "
		     << (((time(0) - unix_time) / 60) / 60)      % 24 << " hours, "
		     <<  ((time(0) - unix_time) / 60)            % 60 << " minutes, "
		     <<   (time(0) - unix_time)                  % 60 << " seconds\n\n";
		
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
