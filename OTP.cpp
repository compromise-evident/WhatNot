/// OTP - fast & plentiful One-time pad.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net)


/* Version 4.2, plausibility ratio = 1:95, plausible messages per ciphertext =
95^79. This is communication with ciphertext of unlimited plausible deniability.
Any key tried is not rejected and successfully decrypts any ciphertext into some
random or plausible message. Get 7MB of keys in 20s and 20,000 outgoing messages
per user -OR- get 512MB of keys in 20m and 1,600,000 outgoing messages per user.
Generate and share multiple folders privately to have spare keys. These keys are
truncated upon use and written back after overwriting their locations. Plaintext
is 79 characters max. 80th char holds message length. Reserved randomness within
key files is appended to all plaintext. Then, both that randomness and plaintext
are encrypted, along with message length information. This prevents key fragment
exposure and size-based file analytics. All ciphertext is 80 characters. OTP has
dual-channel symmetry--two OTPs in one. Alice & Bob may encrypt in simultaneity.
 ______________________________________________________________________________
/                                                                              \
|     Alice makes keys:      * incoming                   * outgoing           |
|                                                                              |
|      Bob gets copies:      * incoming                   * outgoing           |
|                               (copy)                       (copy)            |
|                                                                              |
|                           Bob encrypts,               Alice encrypts,        |
|                          Alice decrypts!               Bob decrypts!         |
\______________________________________________________________________________/

If you happen to encrypt n messages in a row and send them disordered or did not
send them at all, send the other party a new message where they decrypt it until
the output makes sense. If you send encrypted messages with seeds for generating
new symmetric keys, perfect secrecy is then reduced to decryption difficulty and
plausible messages per cipher narrows. See  Perfect secrecy and P!=NP proof.pdf.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to run the program  -  Software package repositories for GNU+Linux operating
systems have all the tools you can imagine. Open a terminal and use this command
as root to install Geany and g++ on your computer: apt install geany g++   Geany
is a fast & lightweight text editor and Integrated Development Environment where
you can write and run code. g++ is the GNU compiler for C++ which allows written
code to run. The compiler operates in the background and displays errors in your
code as you will see in the lower Geany box. Make a new folder somewhere on your
machine. Paste this code into Geany. For clarity in auditing, enable indentation
guides: go to View >> Show Indentation Guides. Save the document as anything.cpp
within the newly-created folder. Use these shortcuts to run the program: F9, F5.
You may paste over this code with other  .cpp files, or open a new tab & repeat.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to make an executable with g++  -  Save this program as anything.cpp, open a
terminal, and type g++ then space. Drag & drop this saved file into the terminal
and its directory will be  appended to your pending entry. Click on the terminal
and press enter.   a.out now resides in the user directory, you may rename it to
anything.  To run that executable, simply drag and drop it into a terminal, then
click on the terminal and press enter.  Reminder:  executable's effect-directory
is the user directory on your machine, for example:  /home/nikolay    Enjoy. */

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	cout << "\n(One-time pad)\n\n"
	
	     << "(1) Encrypt\n"
	     << "(2) Decrypt\n"
	     << "(3) Get keys in 20s (20,000 msg/user.)\n"
	     << "(4) Get keys in 20m (1.6 million msg/user.)\n\n"
	
	     << "Enter option: ";
	
	int user_option;
	cin >> user_option;
	ifstream in_stream;
	ofstream out_stream;
	
	
	
	
	
	//__________________________________________________________________________________________________________________
	//______________________________________________________Encrypt____________________________________________________/
	if(user_option == 1)
	{	//Checks that messages left to encrypt is not zero.
		char remaining_encrypt[7];
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nCan't encrypt without keys.\n"; return 0;}
		for(int a = 0; a < 7; a++) {in_stream >> remaining_encrypt[a];}
		in_stream.close();
		
		for(int a = 0; a < 7; a++) {remaining_encrypt[a] -= 48;} //Fixes input.
		int remaining_encrypt_decimal = 0;
		if(remaining_encrypt[0] > 0) {remaining_encrypt_decimal += (remaining_encrypt[0] * 1000000);}
		if(remaining_encrypt[1] > 0) {remaining_encrypt_decimal += (remaining_encrypt[1] *  100000);}
		if(remaining_encrypt[2] > 0) {remaining_encrypt_decimal += (remaining_encrypt[2] *   10000);}
		if(remaining_encrypt[3] > 0) {remaining_encrypt_decimal += (remaining_encrypt[3] *    1000);}
		if(remaining_encrypt[4] > 0) {remaining_encrypt_decimal += (remaining_encrypt[4] *     100);}
		if(remaining_encrypt[5] > 0) {remaining_encrypt_decimal += (remaining_encrypt[5] *      10);}
		if(remaining_encrypt[6] > 0) {remaining_encrypt_decimal +=  remaining_encrypt[6]           ;}
		if(remaining_encrypt_decimal == 0)     {cout << "\n\nEncryption keys depleted.\n"; return 0;}
		
		cout << "79 characters max (width of terminal -1.) Enter message:\n\n";
		
		char nothing_to_see_here[1]; //This is here to catch the cached new line.
		cin.getline(nothing_to_see_here, 1);
		
		char plaintext[80];
		for(int a = 0; a < 80; a++) {plaintext[a] = '\0';} //Fills plaintext[] with null.
		cin.getline(plaintext, 80);
		plaintext[79] = '\0'; //Message is cut down to 79 characters.
		
		if(plaintext[0] == '\0') {cout << "No input given.\n"; return 0;}
		
		int ciphertext[80];
		for(int a = 0; a < 80; a++) //Prepares initial ciphertext[]. Pressing arrow/other keys WILL TRIGGER THE FOLLOWING ELSE!
		{	     if(plaintext[a] == ' ') {ciphertext[a] =  0;}	else if(plaintext[a] == 'P') {ciphertext[a] = 48;}
			else if(plaintext[a] == '!') {ciphertext[a] =  1;}	else if(plaintext[a] == 'Q') {ciphertext[a] = 49;}
			else if(plaintext[a] == '"') {ciphertext[a] =  2;}	else if(plaintext[a] == 'R') {ciphertext[a] = 50;}
			else if(plaintext[a] == '#') {ciphertext[a] =  3;}	else if(plaintext[a] == 'S') {ciphertext[a] = 51;}
			else if(plaintext[a] == '$') {ciphertext[a] =  4;}	else if(plaintext[a] == 'T') {ciphertext[a] = 52;}
			else if(plaintext[a] == '%') {ciphertext[a] =  5;}	else if(plaintext[a] == 'U') {ciphertext[a] = 53;}
			else if(plaintext[a] == '&') {ciphertext[a] =  6;}	else if(plaintext[a] == 'V') {ciphertext[a] = 54;}
			else if(plaintext[a] =='\'') {ciphertext[a] =  7;}	else if(plaintext[a] == 'W') {ciphertext[a] = 55;}
			else if(plaintext[a] == '(') {ciphertext[a] =  8;}	else if(plaintext[a] == 'X') {ciphertext[a] = 56;}
			else if(plaintext[a] == ')') {ciphertext[a] =  9;}	else if(plaintext[a] == 'Y') {ciphertext[a] = 57;}
			else if(plaintext[a] == '*') {ciphertext[a] = 10;}	else if(plaintext[a] == 'Z') {ciphertext[a] = 58;}
			else if(plaintext[a] == '+') {ciphertext[a] = 11;}	else if(plaintext[a] == '[') {ciphertext[a] = 59;}
			else if(plaintext[a] == ',') {ciphertext[a] = 12;}	else if(plaintext[a] =='\\') {ciphertext[a] = 60;}
			else if(plaintext[a] == '-') {ciphertext[a] = 13;}	else if(plaintext[a] == ']') {ciphertext[a] = 61;}
			else if(plaintext[a] == '.') {ciphertext[a] = 14;}	else if(plaintext[a] == '^') {ciphertext[a] = 62;}
			else if(plaintext[a] == '/') {ciphertext[a] = 15;}	else if(plaintext[a] == '_') {ciphertext[a] = 63;}
			else if(plaintext[a] == '0') {ciphertext[a] = 16;}	else if(plaintext[a] == '`') {ciphertext[a] = 64;}
			else if(plaintext[a] == '1') {ciphertext[a] = 17;}	else if(plaintext[a] == 'a') {ciphertext[a] = 65;}
			else if(plaintext[a] == '2') {ciphertext[a] = 18;}	else if(plaintext[a] == 'b') {ciphertext[a] = 66;}
			else if(plaintext[a] == '3') {ciphertext[a] = 19;}	else if(plaintext[a] == 'c') {ciphertext[a] = 67;}
			else if(plaintext[a] == '4') {ciphertext[a] = 20;}	else if(plaintext[a] == 'd') {ciphertext[a] = 68;}
			else if(plaintext[a] == '5') {ciphertext[a] = 21;}	else if(plaintext[a] == 'e') {ciphertext[a] = 69;}
			else if(plaintext[a] == '6') {ciphertext[a] = 22;}	else if(plaintext[a] == 'f') {ciphertext[a] = 70;}
			else if(plaintext[a] == '7') {ciphertext[a] = 23;}	else if(plaintext[a] == 'g') {ciphertext[a] = 71;}
			else if(plaintext[a] == '8') {ciphertext[a] = 24;}	else if(plaintext[a] == 'h') {ciphertext[a] = 72;}
			else if(plaintext[a] == '9') {ciphertext[a] = 25;}	else if(plaintext[a] == 'i') {ciphertext[a] = 73;}
			else if(plaintext[a] == ':') {ciphertext[a] = 25;}	else if(plaintext[a] == 'j') {ciphertext[a] = 74;}
			else if(plaintext[a] == ';') {ciphertext[a] = 27;}	else if(plaintext[a] == 'k') {ciphertext[a] = 75;}
			else if(plaintext[a] == '<') {ciphertext[a] = 28;}	else if(plaintext[a] == 'l') {ciphertext[a] = 76;}
			else if(plaintext[a] == '=') {ciphertext[a] = 29;}	else if(plaintext[a] == 'm') {ciphertext[a] = 77;}
			else if(plaintext[a] == '>') {ciphertext[a] = 30;}	else if(plaintext[a] == 'n') {ciphertext[a] = 78;}
			else if(plaintext[a] == '?') {ciphertext[a] = 31;}	else if(plaintext[a] == 'o') {ciphertext[a] = 79;}
			else if(plaintext[a] == '@') {ciphertext[a] = 32;}	else if(plaintext[a] == 'p') {ciphertext[a] = 80;}
			else if(plaintext[a] == 'A') {ciphertext[a] = 33;}	else if(plaintext[a] == 'q') {ciphertext[a] = 81;}
			else if(plaintext[a] == 'B') {ciphertext[a] = 34;}	else if(plaintext[a] == 'r') {ciphertext[a] = 82;}
			else if(plaintext[a] == 'C') {ciphertext[a] = 35;}	else if(plaintext[a] == 's') {ciphertext[a] = 83;}
			else if(plaintext[a] == 'D') {ciphertext[a] = 36;}	else if(plaintext[a] == 't') {ciphertext[a] = 84;}
			else if(plaintext[a] == 'E') {ciphertext[a] = 37;}	else if(plaintext[a] == 'u') {ciphertext[a] = 85;}
			else if(plaintext[a] == 'F') {ciphertext[a] = 38;}	else if(plaintext[a] == 'v') {ciphertext[a] = 86;}
			else if(plaintext[a] == 'G') {ciphertext[a] = 39;}	else if(plaintext[a] == 'w') {ciphertext[a] = 87;}
			else if(plaintext[a] == 'H') {ciphertext[a] = 40;}	else if(plaintext[a] == 'x') {ciphertext[a] = 88;}
			else if(plaintext[a] == 'I') {ciphertext[a] = 41;}	else if(plaintext[a] == 'y') {ciphertext[a] = 89;}
			else if(plaintext[a] == 'J') {ciphertext[a] = 42;}	else if(plaintext[a] == 'z') {ciphertext[a] = 90;}
			else if(plaintext[a] == 'K') {ciphertext[a] = 43;}	else if(plaintext[a] == '{') {ciphertext[a] = 91;}
			else if(plaintext[a] == 'L') {ciphertext[a] = 44;}	else if(plaintext[a] == '|') {ciphertext[a] = 92;}
			else if(plaintext[a] == 'M') {ciphertext[a] = 45;}	else if(plaintext[a] == '}') {ciphertext[a] = 93;}
			else if(plaintext[a] == 'N') {ciphertext[a] = 46;}	else if(plaintext[a] == '~') {ciphertext[a] = 94;}
			else if(plaintext[a] == 'O') {ciphertext[a] = 47;}	else if(plaintext[a] =='\0') {ciphertext[a] = -1;} //If message < 79 char, this marks all ending unused spaces to which randomness will be applied then encrypted.
			
			else
			{	cout << "\nDefective input, try again.\n";
				
				//Overwrites RAM of arrays plaintext[] and ciphertext[].
				for(int a = 0; a < 80; a++)
				{	for(int b = 0; b < 10; b++)
					{	plaintext[a]  = b;
						ciphertext[a] = b;
					}
				} //Only partially effective, printed/copied text is cloned from RAM to RAM.
				
				return 0;
			}
		}
		
		//Adjusting file remaining.encrypt.txt.
		remaining_encrypt_decimal--;
		out_stream.open("remaining.encrypt.txt");
		if(remaining_encrypt_decimal < 1000000) {out_stream << "0";}
		if(remaining_encrypt_decimal <  100000) {out_stream << "0";}
		if(remaining_encrypt_decimal <   10000) {out_stream << "0";}
		if(remaining_encrypt_decimal <    1000) {out_stream << "0";}
		if(remaining_encrypt_decimal <     100) {out_stream << "0";}
		if(remaining_encrypt_decimal <      10) {out_stream << "0";}
		out_stream << remaining_encrypt_decimal;
		out_stream << " messages left to encrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Maintaining symmetry entanglement. If you received the symmetry.entanglement file,
		//these file names are modified in the path-to-file section where only the folder
		//names are swapped. Now your incoming channel is symmetric with their outgoing
		//channel, and your outgoing channel is symmetric with their incoming channel.
		char file_name_key_outgoing[21] = "./keys/outgoing/0000";
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == false)
		{	file_name_key_outgoing[ 7] = 'i';
			file_name_key_outgoing[ 8] = 'n';
			file_name_key_outgoing[ 9] = 'c';
			file_name_key_outgoing[10] = 'o';
			file_name_key_outgoing[11] = 'm';
		}
		in_stream.close();
		
		//Generates key file NAME based on depletion.
		int file_numbering = 1000000; //Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 10000; a++)
		{	int temp_file_numbering = file_numbering;
			file_name_key_outgoing[19] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_outgoing[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_outgoing[16] = (temp_file_numbering % 10) + 48;
			
			in_stream.open(file_name_key_outgoing);
			if(in_stream.fail() == false) {in_stream.close(); break;}
			in_stream.close();
			
			file_numbering++;
		}
		
		//Gets a copy of the key file. (Only the first 160 characters!)
		char key_outgoing_content[160];
		in_stream.open(file_name_key_outgoing);
		for(int a = 0; a < 160; a++) {in_stream.get(key_outgoing_content[a]);}
		in_stream.close();
		for(int a = 0; a < 160; a++) {key_outgoing_content[a] -= 32;} //Fixes key contents.
		
		//Gets the message length information.
		int message_length = 0;
		for(int a = 0; a < 79; a++)
		{	if(ciphertext[a] != -1) {message_length++;}
		}
		
		//Appends randomness if message is less than 79 characters.
		for(int a = 0; a < 79; a++)
		{	if(ciphertext[a] == -1) {ciphertext[a] = key_outgoing_content[a];}
		}
		
		//Appends message length information (overwrites 80th element.)
		ciphertext[79] = (message_length);
		
		///Encrypts message.
		for(int a = 0; a < 80; a++) {ciphertext[a] += key_outgoing_content[a + 80]; ciphertext[a] %= 95;}
		
		//Prints ciphertext.
		cout << "\nSelect all 80 characters including end spaces, right-click & copy. Ciphertext:\n";
		for(int a = 0; a < 80; a++)
		{	cout << char(ciphertext[a] + 32);
		}
		
		//Overwriting RAM of plaintext[], ciphertext[].
		for(int a = 0; a < 80; a++)
		{	for(int b = 0; b < 10; b++)
			{	plaintext[a] = b;
			}
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwriting RAM of key_outgoing_content[].
		for(int a = 0; a < 160; a++)
		{	for(int b = 0; b < 10; b++)
			{	key_outgoing_content[a] = b;
			}
		}
		
		//Copies entire outgoing key into RAM before overwriting it.
		char truncating_table_private[100001] = {'\0'};
		in_stream.open(file_name_key_outgoing);
		in_stream.get(truncating_table_private[0]);
		for(int a = 1; in_stream.eof() == false; a++) {in_stream.get(truncating_table_private[a]);}
		in_stream.close();
		
		//Overwrites the outgoing key file twice with 100,000 characters each round.
		out_stream.open(file_name_key_outgoing); for(int a = 0; a < 100000; a++) {out_stream << '\0';} out_stream.close(); //Binary: 00000000
		out_stream.open(file_name_key_outgoing); for(int a = 0; a < 100000; a++) {out_stream.put(-1);} out_stream.close(); //Binary: 11111111
		
		//Removing or truncating the outgoing key file by the first 160 characters.
		if(truncating_table_private[160] == '\0') {remove(file_name_key_outgoing);}
		else
		{	out_stream.open(file_name_key_outgoing);
			for(int a = 160; truncating_table_private[a] != '\0'; a++) {out_stream.put(truncating_table_private[a]);}
			out_stream.close();
		}
		
		//Overwriting RAM of truncating_table_private[];
		for(int a = 0; a < 100001; a++)
		{	for(int b = 0; b < 10; b++) {truncating_table_private[a] = b;}
		}
		
		//Displays # of messages left to generate.
		if     (remaining_encrypt_decimal == 0) {cout << "\n\nEncryption keys depleted.\n"        ;}
		else if(remaining_encrypt_decimal == 1) {cout << "\n\nYou may encrypt one more message.\n";}
		else   {cout << "\n\nYou may encrypt " << remaining_encrypt_decimal << " more messages.\n";}
	}
	
	
	
	
	
	//__________________________________________________________________________________________________________________
	//______________________________________________________Decrypt____________________________________________________/
	else if(user_option == 2)
	{	//Checks that messages left to decrypt is not zero.
		char remaining_decrypt[7];
		in_stream.open("remaining.decrypt.txt");
		if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nCan't decrypt without keys.\n"; return 0;}
		for(int a = 0; a < 7; a++) {in_stream >> remaining_decrypt[a];}
		in_stream.close();
		
		for(int a = 0; a < 7; a++) {remaining_decrypt[a] -= 48;} //Fixes input.
		int remaining_decrypt_decimal = 0;
		if(remaining_decrypt[0] > 0) {remaining_decrypt_decimal += (remaining_decrypt[0] * 1000000);}
		if(remaining_decrypt[1] > 0) {remaining_decrypt_decimal += (remaining_decrypt[1] *  100000);}
		if(remaining_decrypt[2] > 0) {remaining_decrypt_decimal += (remaining_decrypt[2] *   10000);}
		if(remaining_decrypt[3] > 0) {remaining_decrypt_decimal += (remaining_decrypt[3] *    1000);}
		if(remaining_decrypt[4] > 0) {remaining_decrypt_decimal += (remaining_decrypt[4] *     100);}
		if(remaining_decrypt[5] > 0) {remaining_decrypt_decimal += (remaining_decrypt[5] *      10);}
		if(remaining_decrypt[6] > 0) {remaining_decrypt_decimal +=  remaining_decrypt[6]           ;}
		if(remaining_decrypt_decimal == 0)     {cout << "\n\nDecryption keys depleted.\n"; return 0;}
		
		cout << "Decrypt in the order received.\n"
		     << "Right-click and paste the ciphertext of 80 characters:\n\n";
		
		char nothing_to_see_here[1]; //This is here to catch the cached new line.
		cin.getline(nothing_to_see_here, 1);
		
		char ciphertext[81]; //Incase the user enters too many.
		for(int a = 0; a < 81; a++) {ciphertext[a] = '\0';} //Fills ciphertext[] with null.
		cin.getline(ciphertext, 81);
		ciphertext[80] = '\0'; //Input is cut down to 80 characters.
		
		if(ciphertext[0] == '\0') {cout << "No input given.\n"; return 0;}
		for(int a = 0; a < 80; a++) {ciphertext[a] -= 32;} //Fixes ciphertext.
		
		//Adjusting file remaining.decrypt.txt
		remaining_decrypt_decimal--;
		out_stream.open("remaining.decrypt.txt");
		if(remaining_decrypt_decimal < 1000000) {out_stream << "0";}
		if(remaining_decrypt_decimal <  100000) {out_stream << "0";}
		if(remaining_decrypt_decimal <   10000) {out_stream << "0";}
		if(remaining_decrypt_decimal <    1000) {out_stream << "0";}
		if(remaining_decrypt_decimal <     100) {out_stream << "0";}
		if(remaining_decrypt_decimal <      10) {out_stream << "0";}
		out_stream << remaining_decrypt_decimal;
		out_stream << " messages left to decrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Maintaining symmetry entanglement. If you received the symmetry.entanglement file,
		//these file names are modified in the path-to-file section where only the folder
		//names are swapped. Now your incoming channel is symmetric with their outgoing
		//channel, and your outgoing channel is symmetric with their incoming channel.
		char file_name_key_incoming[21] = "./keys/incoming/0000";
		in_stream.open("symmetry.entanglement");
		if(in_stream.fail() == false)
		{	file_name_key_incoming[ 7] = 'o';
			file_name_key_incoming[ 8] = 'u';
			file_name_key_incoming[ 9] = 't';
			file_name_key_incoming[10] = 'g';
			file_name_key_incoming[11] = 'o';
		}
		in_stream.close();
		
		//Generates key file NAME based on existence.
		int file_numbering = 1000000; //Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 10000; a++)
		{	int temp_file_numbering = file_numbering;
			file_name_key_incoming[19] = (temp_file_numbering % 10) + 48; //       ./keys/incoming/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_incoming[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_incoming[16] = (temp_file_numbering % 10) + 48;
			
			in_stream.open(file_name_key_incoming);
			if(in_stream.fail() == false) {in_stream.close(); break;}
			in_stream.close();
			
			file_numbering++;
		}
		
		//Gets a copy of the key file. (Only the first 160 characters!)
		char key_incoming_content[160];
		in_stream.open(file_name_key_incoming);
		for(int a = 0; a < 160; a++) {in_stream.get(key_incoming_content[a]);}
		in_stream.close();
		for(int a = 80; a < 160; a++) {key_incoming_content[a] -= 32;} //Fixes key content portion used for decryption.
		
		/// Decrypts message. The following formula helps extract plaintext quickly.
		/*   ______________________________________________ ________________________________________________
		    |                                              |                                                |
		    |              if key <= ciphertext            |                     else                       |
		    |      then plaintext = (ciphertext - key)     |      plaintext = ((95 - key) + ciphertext)     |
		    |______________________________________________|________________________________________________|
		*/
		int plaintext[80];
		for(int a = 0; a < 80; a++)
		{	if(key_incoming_content[a + 80] <= ciphertext[a])
			{	plaintext[a] = (ciphertext[a] - key_incoming_content[a + 80]);
			}
			else
			{	plaintext[a] = ((95 - key_incoming_content[a + 80]) + ciphertext[a]);
			}
		}
		
		//Prints plaintext.
		cout << "\nPlaintext:\n";
		for(int a = 0; a < (plaintext[79]); a++) {cout << char(plaintext[a] + 32);}
		
		//Overwriting RAM of plaintext[], ciphertext[].
		for(int a = 0; a < 80; a++)
		{	for(int b = 0; b < 10; b++)
			{	plaintext[a] = b;
			}
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwriting RAM of key_incoming_content[].
		for(int a = 0; a < 160; a++)
		{	for(int b = 0; b < 10; b++)
			{	key_incoming_content[a] = b;
			}
		}
		
		//Copies entire incoming key into RAM before overwriting it.
		char truncating_table_private[100001] = {'\0'};
		in_stream.open(file_name_key_incoming);
		in_stream.get(truncating_table_private[0]);
		for(int a = 1; in_stream.eof() == false; a++) {in_stream.get(truncating_table_private[a]);}
		in_stream.close();
		
		//Overwrites the incoming key file twice with 100,000 characters each round.
		out_stream.open(file_name_key_incoming); for(int a = 0; a < 100000; a++) {out_stream << '\0';} out_stream.close(); //Binary: 00000000
		out_stream.open(file_name_key_incoming); for(int a = 0; a < 100000; a++) {out_stream.put(-1);} out_stream.close(); //Binary: 11111111
		
		//Removing or truncating the incoming key file by the first 160 characters.
		if(truncating_table_private[160] == '\0') {remove(file_name_key_incoming);}
		else
		{	out_stream.open(file_name_key_incoming);
			for(int a = 160; truncating_table_private[a] != '\0'; a++) {out_stream.put(truncating_table_private[a]);}
			out_stream.close();
		}
		
		//Overwriting RAM of truncating_table_private[];
		for(int a = 0; a < 100001; a++)
		{	for(int b = 0; b < 10; b++) {truncating_table_private[a] = b;}
		}
		
		//Displays # of messages left to decrypt.
		if     (remaining_decrypt_decimal == 0) {cout << "\n\nDecryption keys depleted.\n"        ;}
		else if(remaining_decrypt_decimal == 1) {cout << "\n\nYou may decrypt one more message.\n";}
		else   {cout << "\n\nYou may decrypt " << remaining_decrypt_decimal << " more messages.\n";}
		
		char wait; cin >> wait; //In case the user presses enter twice, the decrypted message will not vanish immediately.
	}
	
	
	
	
	
	//__________________________________________________________________________________________________________________
	//______________________________________________________Get_keys_in_20_seconds_____________________________________/
	else if(user_option == 3)
	{	//Are you testing your fork and need keys fast? Set the following variable
		//to 1 and it will ask for only one seed and fill table_private[] in one pass.
		int value_90_seeds = 90;
		
		//Checks if regular files already exist.
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == false)
		{	in_stream.close();
			cout << "\n\nKeys already exist, run a new OTP.cpp file in a different folder.\n";
			return 0;
		}
		in_stream.close();
		
		cout << "\nEnter a random nine-digit integer, repeat 90 times. (Get 7MB in 20s)\n\n";
		
		//Gets seeds for RNG.
		unsigned int user_seeds[90] = {0};
		for(int a = 0; a < value_90_seeds; a++)
		{	if(a < 9) {cout << " " << (a + 1) << " of 90: ";} //Prints blank to align input status report (aesthetics.)
			else      {cout <<        (a + 1) << " of 90: ";}
			
			//Gets and checks input.
			cin >> user_seeds[a];
			if((user_seeds[a] > 999999999) || (user_seeds[a] < 100000000)) {cout << "\nOut of bounds, try again.\n"; return 0;}
		}
		
		cout << "\nWait 20 seconds...\n";
		
		//Fills table_private[] with randomness 00 - 94
		unsigned char table_private[6400000] = {0};
		for(int a = 0; a < value_90_seeds; a++) //Constructively applies random digits to table_private[] based on the 90 seeds provided by the user.
		{	srand(user_seeds[a]);               //WRITES ALTERNATING BETWEEN LEFT TO RIGHT & RIGHT TO LEFT. Alternation is based on the 90 user seeds.
			
			if((user_seeds[a] % 2) == 0)
			{	for(int b = 0; b < 6400000; b++) //WRITES LEFT TO RIGHT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
			else
			{	for(int b = 6399999; b >= 0; b--) //WRITES RIGHT TO LEFT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
		}
		
		//Adding additional randomness in table_private[].
		if(user_seeds[89] > 0) //(Inactive if in testing or quick mode as prompted at the top.)
		{	unsigned int seeds_sum = 0;
			for(int a = 0; a < 90; a++) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
			srand(seeds_sum); //A new 9-digit seed comes from the sum of ALL user-seeds.
			for(int a = 0; a < 6400000; a++) //WRITES LEFT TO RIGHT.
			{	table_private[a] += (rand() % 95);
				table_private[a] %= 95;
			}
			
			//Again, adding additional randomness in table_private[].
			seeds_sum = 0;
			for(int a = 0; a < 90; a += 2) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
			srand(seeds_sum); //Another new 9-digit seed comes from the sum of EVERY OTHER user-seed.
			for(int a = 6399999; a >= 0; a--) //WRITES RIGHT TO LEFT.
			{	table_private[a] += (rand() % 95);
				table_private[a] %= 95;
			}
			seeds_sum = 123456789; //Overwriting.
		}
		
		//Writing all keys for channel incoming then all keys for channel outgoing (separately, reusing code.)
		system("mkdir keys"         ); //Creates a folder. Folder-izing helps lighten resource usage by 1,000%.
		system("mkdir keys/incoming"); //Creates a folder within that keys folder.
		system("mkdir keys/outgoing"); //Creates another folder within that keys folder.
		char file_name_key_incoming[21] = "./keys/incoming/0000";
		char file_name_key_outgoing[21] = "./keys/outgoing/0000";
		
		//Writes keys to folder incoming.
		int table_private_read_bookmark = 0;
		int file_numbering = 1000000; //Only the last 2 digits are used, size makes mod operations easier.
		for(int a = 0; a < 100; a++)
		{	out_stream.open(file_name_key_incoming);
			for(int b = 0; b < 32000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream.close();
			
			file_numbering++; //Adjusts file numbering.
			int temp_file_numbering = file_numbering;
			file_name_key_incoming[19] = (temp_file_numbering % 10) + 48;//        ./keys/incoming/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
		}
		
		//Writes keys to folder outgoing, table_private_read_bookmark is not reset.
		file_numbering = 1000000; //Resetting. Only the last 2 digits are used, size makes mod operations easier.
		for(int a = 0; a < 100; a++)
		{	out_stream.open(file_name_key_outgoing);
			for(int b = 0; b < 32000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream.close();
			
			file_numbering++; //Adjusts file numbering.
			int temp_file_numbering = file_numbering;
			file_name_key_outgoing[19] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
		}
		
		//Creates the encryption remaining counter file.
		out_stream.open("remaining.encrypt.txt");
		out_stream << "0020000 messages left to encrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the decryption remaining counter file.
		out_stream.open("remaining.decrypt.txt");
		out_stream << "0020000 messages left to decrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the symmetry entanglement file.
		out_stream.open("symmetry.entanglement");
		out_stream << "REMINDER: one of you must remove this file!\n"
		           << "(Key maker had already been asked to do so.)";
		out_stream.close();
		
		//Overwrites RAM of user_seeds[].
		for(int a = 0; a < 90; a++)
		{	user_seeds[a] = 123456789;
			user_seeds[a] = 987604321;
			user_seeds[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwrites RAM of array table_private[].
		for(int a = 0; a < 6400000; a++)
		{	for(int b = 0; b < 10; b++) {table_private[a] = b;}
		}
		
		cout << "\n\nFinished! Share this folder in private, then\n"
		     << "REMOVE file symmetry.entanglement on your end ONLY!\n\n";
	}
	
	
	
	
	
	//__________________________________________________________________________________________________________________
	//______________________________________________________Get_keys_in_20_minutes_____________________________________/
	else if(user_option == 4)
	{	//Checks if regular files already exist.
		in_stream.open("remaining.encrypt.txt");
		if(in_stream.fail() == false)
		{	in_stream.close();
			cout << "\n\nKeys already exist, run a new OTP.cpp file in a different folder.\n";
			return 0;
		}
		in_stream.close();
		
		cout << "\nEnter a random nine-digit integer, repeat 90 times. (Get 512MB in 20m)\n\n";
		
		//Gets seeds for RNG.
		unsigned int user_seeds[90] = {0};
		for(int a = 0; a < 90; a++)
		{	if(a < 9) {cout << " " << (a + 1) << " of 90: ";} //Prints blank to align input status report (aesthetics.)
			else      {cout <<        (a + 1) << " of 90: ";}
			
			//Gets and checks input.
			cin >> user_seeds[a];
			if((user_seeds[a] > 999999999) || (user_seeds[a] < 100000000)) {cout << "\nOut of bounds, try again.\n"; return 0;}
		}
		
		cout << "\nWait 20 minutes...\n";
		
		//Fills table_private[] with randomness 00 - 94
		static unsigned char table_private[512000000] = {0};
		for(int a = 0; a < 90; a++) //Constructively applies random digits to table_private[] based on the 90 seeds provided by the user.
		{	srand(user_seeds[a]);   //WRITES ALTERNATING BETWEEN LEFT TO RIGHT & RIGHT TO LEFT. Alternation is based on the 90 user seeds.
			
			if((user_seeds[a] % 2) == 0)
			{	for(int b = 0; b < 512000000; b++) //WRITES LEFT TO RIGHT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
			else
			{	for(int b = 511999999; b >= 0; b--) //WRITES RIGHT TO LEFT.
				{	table_private[b] += (rand() % 95);
					table_private[b] %= 95;
				}
			}
		}
		
		//Adding additional randomness in table_private[].
		unsigned int seeds_sum = 0;
		for(int a = 0; a < 90; a++) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
		srand(seeds_sum); //A new 9-digit seed comes from the sum of ALL user-seeds.
		for(int a = 0; a < 512000000; a++) //WRITES LEFT TO RIGHT.
		{	table_private[a] += (rand() % 95);
			table_private[a] %= 95;
		}
		
		//Again, adding additional randomness in table_private[].
		seeds_sum = 0;
		for(int a = 0; a < 90; a += 2) {seeds_sum = ((seeds_sum + user_seeds[a]) % 1000000000);}
		srand(seeds_sum); //Another new 9-digit seed comes from the sum of EVERY OTHER user-seed.
		for(int a = 511999999; a >= 0; a--) //WRITES RIGHT TO LEFT.
		{	table_private[a] += (rand() % 95);
			table_private[a] %= 95;
		}
		seeds_sum = 123456789; //Overwriting. (Only partially effective, printed/copied text is cloned from RAM to RAM.)
		
		//Writing all keys for channel incoming then all keys for channel outgoing (separately, reusing code.)
		system("mkdir keys"         ); //Creates a folder. Folder-izing helps lighten resource usage by 1,000%.
		system("mkdir keys/incoming"); //Creates a folder within that keys folder.
		system("mkdir keys/outgoing"); //Creates another folder within that keys folder.
		char file_name_key_incoming[21] = "./keys/incoming/0000";
		char file_name_key_outgoing[21] = "./keys/outgoing/0000";
		
		//Writes keys to folder incoming.
		int table_private_read_bookmark = 0;
		int file_numbering = 1000000; //Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 2560; a++)
		{	out_stream.open(file_name_key_incoming);
			for(int b = 0; b < 100000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream.close();
			
			file_numbering++; //Adjusts file numbering.
			int temp_file_numbering = file_numbering;
			file_name_key_incoming[19] = (temp_file_numbering % 10) + 48;//        ./keys/incoming/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_incoming[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_incoming[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_incoming[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Writes keys to folder outgoing, table_private_read_bookmark is not reset.
		file_numbering = 1000000; //Resetting. Only the last 4 digits are used, size makes mod operations easier.
		for(int a = 0; a < 2560; a++)
		{	out_stream.open(file_name_key_outgoing);
			for(int b = 0; b < 100000; b++)
			{	out_stream.put(table_private[table_private_read_bookmark] + 32);
				
				table_private_read_bookmark++;
			}
			out_stream.close();
			
			file_numbering++; //Adjusts file numbering.
			int temp_file_numbering = file_numbering;
			file_name_key_outgoing[19] = (temp_file_numbering % 10) + 48; //       ./keys/outgoing/0  0  0  0    (file name)
			temp_file_numbering /=    10; //                                                       ^  ^  ^  ^
			file_name_key_outgoing[18] = (temp_file_numbering % 10) + 48; //                      16 17 18 19    (element layout)
			temp_file_numbering /=    10;
			file_name_key_outgoing[17] = (temp_file_numbering % 10) + 48;
			temp_file_numbering /=    10;
			file_name_key_outgoing[16] = (temp_file_numbering % 10) + 48;
		}
		
		//Creates the encryption remaining counter file.
		out_stream.open("remaining.encrypt.txt");
		out_stream << "1600000 messages left to encrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the decryption remaining counter file.
		out_stream.open("remaining.decrypt.txt");
		out_stream << "1600000 messages left to decrypt.\n\n"
		
		           << "Do not modify this file.\n"
		           << "This number must consist\n"
		           << "of digits 0000000 - 1600000.";
		out_stream.close();
		
		//Creates the symmetry entanglement file.
		out_stream.open("symmetry.entanglement");
		out_stream << "REMINDER: one of you must remove this file!\n"
		           << "(Key maker had already been asked to do so.)";
		out_stream.close();
		
		//Overwrites RAM of user_seeds[].
		for(int a = 0; a < 90; a++)
		{	user_seeds[a] = 123456789;
			user_seeds[a] = 987604321;
			user_seeds[a] = 0;
		} //Only partially effective, printed/copied text is cloned from RAM to RAM.
		
		//Overwrites RAM of array table_private[].
		for(int a = 0; a < 512000000; a++)
		{	for(int b = 0; b < 10; b++) {table_private[a] = b;}
		}
		
		cout << "\n\nFinished! Share this folder in private, then\n"
		     << "REMOVE file symmetry.entanglement on your end ONLY!\n\n";
	}
	
	else {cout << "\nInvalid option, program ended.\n"; return 0;}
}
