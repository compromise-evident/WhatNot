/// Byte occurrence print-out for any file, and C++/GNU+Linux resource.

/* All files are just text files stored in byte quantity. Type char takes input
using its 256 storage values -128 to 127. See bottom for extensive byte details.
Depending on byte endings and encoding,  some char may show up here as  multiple
separate items--for which multiple occurrence counters tick once. This issue may
come from  special  characters such as those copied and pasted from  LibreOffice
writer. Regular text files normally contain a  9, 10, 13, and 32-126 ASCII char.
If you select a special character in Geany,  you can see the stats at the bottom
"sel:3" for example,  which means this one char is composed of three bytes.  And
if you create files strictly using C++,  out_stream.put(-1) for example, you get
one byte as expected. However, if you copy and paste that char, that new file is
now two bytes in size--holding one character.  Safely, and without adjusting for
the \r\n fuckery of copy/paste & other OSes, you may use  96 characters--the tab
being 9--to create files that can't be  corrupted as they're re-formatted across
the web until finally reaching your device,  such as an  Authorship.public file.
When in doubt,use only characters 9 and 32-126 for  un-fuckable  file integrity.
See char  13  and  10  in the table below if your files need to be  copy/pasted.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
If you wish to deal with bytes as numbers  0 to 255  (as done here, in Multiway,
schemeOTP, groupOTP, Allornothing, RICIN, RICINgauss, and RICINoptic)   then use
this line to convert the signed char value, but first create an integer/unsigned
char destination such as  int file_byte_normal;


        char file_byte;
        int  file_byte_normal;
        in_stream.get(file_byte);
        file_byte_normal = file_byte;
>>>>    if(file_byte_normal < 0) {file_byte_normal += 256;}




and write-back to file:

if(file_byte_normal < 128) {out_stream.put(file_byte_normal      );}
else                       {out_stream.put(file_byte_normal - 256);}


Now you can perform mathematical operations & modular arithmetic such as mod 256
which returns a value 0 to 255--accounting for 256 total items--0 is item 1.  */

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	ifstream in_stream;
	
	//Gets path to file from user.
	cout << "\nDrag & drop file into terminal or enter path:\n\n";
	char  path_to_file[10000];
	for(int a = 0; a < 10000; a++) {path_to_file[a] = '\0';} //Fills path_to_file[] with null.
	cin.getline(path_to_file, 10000);
	if(path_to_file[0] == '\0') {cout << "\nNo path given.\n"; return 0;}
	
	//Fixes path to file if drag & dropped (removes single quotes for ex:)   '/home/nikolay/my documents/hush hush.bmp'
	if(path_to_file[0] == '\'')
	{	for(int a = 0; a < 10000; a++)
		{	path_to_file[a] = path_to_file[a + 1];
			if(path_to_file[a] == '\'')
			{	path_to_file[a] = '\0';
				path_to_file[a + 1] = '\0';
				path_to_file[a + 2] = '\0';
				break;
			}
		}
	}
	
	//Checks if file exists (failure can be bad path info as well.)
	in_stream.open(path_to_file);
	if(in_stream.fail() == true) {in_stream.close(); cout << "\n\nNo such file or directory.\n";             return 0;}
	char sniffed_one_file_character;
	in_stream.get(sniffed_one_file_character);
	if(in_stream.eof() == true) {in_stream.close();  cout << "\n\nNothing to process, the file is empty.\n"; return 0;}
	in_stream.close();
	
	//Fills distribution[] and calculates total_bytes.
	int location_counter = 2;
	int location_of_special_character = -1;
	bool count_until_special_character = true;
	
	char temp_file_byte;
	int  temp_file_byte_normal;
	long long distribution[256] = {0};
	long long total_bytes = 0;
	in_stream.open(path_to_file);
	in_stream.get(temp_file_byte);
	for(; in_stream.eof() == false;)
	{	temp_file_byte_normal = temp_file_byte;
		if(temp_file_byte_normal < 0) {temp_file_byte_normal += 256;}
		distribution[temp_file_byte_normal]++;
		in_stream.get(temp_file_byte);
		total_bytes++;
		
		if(count_until_special_character == true)
		{	if((temp_file_byte <  32)
			|| (temp_file_byte > 126))
			{	if((temp_file_byte !=  9)
				&& (temp_file_byte != 10)
				&& (temp_file_byte != 13))
				{	count_until_special_character = false;
					location_of_special_character = location_counter;
				}
			}
			
			location_counter++;
		}
	}
	in_stream.close();
	
	//Displays occurrence, total, and distinct.
	cout << "\n";
	int distinct_bytes = 0;
	for(int a = 0; a < 256; a++)
	{	     if(a <  10) {cout << "occurrence of   " << a << ":  ";}
		else if(a < 100) {cout << "occurrence of  "  << a << ":  ";}
		else             {cout << "occurrence of "   << a << ":  ";}
		
		if(distribution[a] == 0) {cout << "-\n"                  ;}
		else   {distinct_bytes++; cout << distribution[a] << "\n";}
	}
	cout << "\n" << total_bytes << " total bytes, ";
	if(total_bytes == distinct_bytes) {cout << "all distinct.\n\n";}
	else               {cout << distinct_bytes << " distinct.\n\n";}
	
	//Displays average, minimum, and maximum.
	long long minimum = 999999999999999999;
	long long maximum = 0;
	for(int a = 0; a < 256; a++)
	{	if((distribution[a] < minimum) && (distribution[a] > 0)) {minimum = distribution[a];}
		if(distribution[a] > maximum) {maximum = distribution[a];}
	}
	cout << (total_bytes / distinct_bytes) << "\t (average tallies of present)\n"
	     << minimum << "\t (least tallies of present)\n"
	     << maximum << "\t (most tallies)\n\n";
	
	if(location_of_special_character == -1) {cout << "No characters outside of the standard 9, 10, 13, and 32-126.\n\n";}
	else
	{	cout << "Character ~" << location_of_special_character << " is the 1st char outside of 9, 10, 13, and 32-126.\n"
		     << "(if examining text file. It may be a hidden/unwanted special char.)\n\n";
	}
}








///###############################################################################################################################
///###############################################################################################################################
///###############################################################################################################################
/* ALL ASCII ARE FULL BYTES OR 8 BITS! ALL FILES ARE STRINGS OF BYTES!
The tilde character for example is 01111110 having first bit as zero
since it's unused, but it must still be there so as not to break the
rule of every byte being 8 bits! You had always used extended ASCII.


Dec	Hex	 Binary      HTML   Char  Description                  C++ file read/write


  0  00  00000000     &#0;  NUL   Null                         out_stream.put(0);   or   out_stream << '\0';
  1  01  00000001     &#1;  SOH   Start of Header              out_stream.put(1);
  2  02  00000010     &#2;  STX   Start of Text                out_stream.put(2);
  3  03  00000011     &#3;  ETX   End of Text                  out_stream.put(3);
  4  04  00000100     &#4;  EOT   End of Transmission          out_stream.put(4);
  5  05  00000101     &#5;  ENQ   Enquiry                      out_stream.put(5);
  6  06  00000110     &#6;  ACK   Acknowledge                  out_stream.put(6);
  7  07  00000111     &#7;  BEL   Bell                         out_stream.put(7);   or   out_stream << '\a';   (Makes a single beep-noise. If your motherboard is old and has a tweeter soldered onto it, \a will make that beep once.)
  8  08  00001000     &#8;  BS    Backspace                    out_stream.put(8);
  9  09  00001001     &#9;  HT    Horizontal Tab               out_stream.put(9);   or   out_stream << '\t';   (Horizontal tab.)
 10  0A  00001010    &#10;  LF    Line Feed                    out_stream.put(10);  or   out_stream << '\n';   (Enter key on GNU+Linux.) Moves cursor down a line. CAUTION: uploading to stikked.ch for example means the downloaded or copy/paste output will have prepended '\r' to each '\n' automatically to make "\r\n". pastebin.pl on the other hand, removes the \r in "\r\n" to make \n alone.
 11  0B  00001011    &#11;  VT    Vertical Tab                 out_stream.put(11);
 12  0C  00001100    &#12;  FF    Form Feed                    out_stream.put(12);
 13  0D  00001101    &#13;  CR    Carriage Return              out_stream.put(13);  or   out_stream << '\r';   (Enter key on Mac.) Moves cursor to beginning of line. And on Windows: "\r\n" (combined.) NOTE: this only exists unfortunately (shame on Mac & Windows) because on the type-writer, in order to press enter, you must do both; move down a line, THEN move the contraption to the beginning of the line. And so it stuck around to confuse noob auditors and waste precious disk space since \n would suffice.
 14  0E  00001110    &#14;  SO    Shift Out                    out_stream.put(14);
 15  0F  00001111    &#15;  SI    Shift In                     out_stream.put(15);
 16  10  00010000    &#16;  DLE   Data Link Escape             out_stream.put(16);
 17  11  00010001    &#17;  DC1   Device Control 1             out_stream.put(17);
 18  12  00010010    &#18;  DC2   Device Control 2             out_stream.put(18);
 19  13  00010011    &#19;  DC3   Device Control 3             out_stream.put(19);
 20  14  00010100    &#20;  DC4   Device Control 4             out_stream.put(20);
 21  15  00010101    &#21;  NAK   Negative Acknowledge         out_stream.put(21);
 22  16  00010110    &#22;  SYN   Synchronize                  out_stream.put(22);
 23  17  00010111    &#23;  ETB   End of Transmission Block    out_stream.put(23);
 24  18  00011000    &#24;  CAN   Cancel                       out_stream.put(24);
 25  19  00011001    &#25;  EM    End of Medium                out_stream.put(25);
 26  1A  00011010    &#26;  SUB   Substitute                   out_stream.put(26);
 27  1B  00011011    &#27;  ESC   Escape                       out_stream.put(27);
 28  1C  00011100    &#28;  FS    File Separator               out_stream.put(28);
 29  1D  00011101    &#29;  GS    Group Separator              out_stream.put(29);
 30  1E  00011110    &#30;  RS    Record Separator             out_stream.put(30);
 31  1F  00011111    &#31;  US    Unit Separator               out_stream.put(31);
 32  20  00100000    &#32;  space Blank or space               out_stream.put(32);   or   out_stream << ' ';  or   out_stream << " ";   Standard 95 printable ASCII characters begin here (32 to 126 or space to tilde.)
 33  21  00100001    &#33;  !     Exclamation mark             out_stream.put(33);   or   out_stream << '!';  or   out_stream << "!";
 34  22  00100010    &#34;  "     Double quote                 out_stream.put(34);   or   out_stream << '"';  or   out_stream <<"\"";   As escape sequence so C++ does not confuse where double quotes end.
 35  23  00100011    &#35;  #     Number                       out_stream.put(35);   or   out_stream << '#';  or   out_stream << "#";
 36  24  00100100    &#36;  $     Dollar sign                  out_stream.put(36);   or   out_stream << '$';  or   out_stream << "$";
 37  25  00100101    &#37;  %     Percent                      out_stream.put(37);   or   out_stream << '%';  or   out_stream << "%";
 38  26  00100110    &#38;  &     Ampersand                    out_stream.put(38);   or   out_stream << '&';  or   out_stream << "&";
 39  27  00100111    &#39;  '     Single quote                 out_stream.put(39);   or   out_stream <<'\'';  or   out_stream << "'";   As escape sequence so C++ does not confuse where single quote ends.
 40  28  00101000    &#40;  (     Left parenthesis             out_stream.put(40);   or   out_stream << '(';  or   out_stream << "(";
 41  29  00101001    &#41;  )     Right parenthesis            out_stream.put(41);   or   out_stream << ')';  or   out_stream << ")";
 42  2A  00101010    &#42;  *     Asterisk                     out_stream.put(42);   or   out_stream << '*';  or   out_stream << "*";
 43  2B  00101011    &#43;  +     Plus                         out_stream.put(43);   or   out_stream << '+';  or   out_stream << "+";
 44  2C  00101100    &#44;  ,     Comma                        out_stream.put(44);   or   out_stream << ',';  or   out_stream << ",";
 45  2D  00101101    &#45;  -     Minus                        out_stream.put(45);   or   out_stream << '-';  or   out_stream << "-";
 46  2E  00101110    &#46;  .     Period                       out_stream.put(46);   or   out_stream << '.';  or   out_stream << ".";
 47  2F  00101111    &#47;  /     Slash                        out_stream.put(47);   or   out_stream << '/';  or   out_stream << "/";
 48  30  00110000    &#48;  0     Zero                         out_stream.put(48);   or   out_stream << '0';  or   out_stream << "0";
 49  31  00110001    &#49;  1     One                          out_stream.put(49);   or   out_stream << '1';  or   out_stream << "1";
 50  32  00110010    &#50;  2     Two                          out_stream.put(50);   or   out_stream << '2';  or   out_stream << "2";
 51  33  00110011    &#51;  3     Three                        out_stream.put(51);   or   out_stream << '3';  or   out_stream << "3";
 52  34  00110100    &#52;  4     Four                         out_stream.put(52);   or   out_stream << '4';  or   out_stream << "4";
 53  35  00110101    &#53;  5     Five                         out_stream.put(53);   or   out_stream << '5';  or   out_stream << "5";
 54  36  00110110    &#54;  6     Six                          out_stream.put(54);   or   out_stream << '6';  or   out_stream << "6";
 55  37  00110111    &#55;  7     Seven                        out_stream.put(55);   or   out_stream << '7';  or   out_stream << "7";
 56  38  00111000    &#56;  8     Eight                        out_stream.put(56);   or   out_stream << '8';  or   out_stream << "8";
 57  39  00111001    &#57;  9     Nine                         out_stream.put(57);   or   out_stream << '9';  or   out_stream << "9";
 58  3A  00111010    &#58;  :     Colon                        out_stream.put(58);   or   out_stream << ':';  or   out_stream << ":";
 59  3B  00111011    &#59;  ;     Semicolon                    out_stream.put(59);   or   out_stream << ';';  or   out_stream << ";";
 60  3C  00111100    &#60;  <     Less than                    out_stream.put(60);   or   out_stream << '<';  or   out_stream << "<";
 61  3D  00111101    &#61;  =     Equality sign                out_stream.put(61);   or   out_stream << '=';  or   out_stream << "=";
 62  3E  00111110    &#62;  >     Greater than                 out_stream.put(62);   or   out_stream << '>';  or   out_stream << ">";
 63  3F  00111111    &#63;  ?     Question mark                out_stream.put(63);   or   out_stream << '?';  or   out_stream << "?";
 64  40  01000000    &#64;  @     At sign                      out_stream.put(64);   or   out_stream << '@';  or   out_stream << "@";
 65  41  01000001    &#65;  A     Capital A                    out_stream.put(65);   or   out_stream << 'A';  or   out_stream << "A";
 66  42  01000010    &#66;  B     Capital B                    out_stream.put(66);   or   out_stream << 'B';  or   out_stream << "B";
 67  43  01000011    &#67;  C     Capital C                    out_stream.put(67);   or   out_stream << 'C';  or   out_stream << "C";
 68  44  01000100    &#68;  D     Capital D                    out_stream.put(68);   or   out_stream << 'D';  or   out_stream << "D";
 69  45  01000101    &#69;  E     Capital E                    out_stream.put(69);   or   out_stream << 'E';  or   out_stream << "E";
 70  46  01000110    &#70;  F     Capital F                    out_stream.put(70);   or   out_stream << 'F';  or   out_stream << "F";
 71  47  01000111    &#71;  G     Capital G                    out_stream.put(71);   or   out_stream << 'G';  or   out_stream << "G";
 72  48  01001000    &#72;  H     Capital H                    out_stream.put(72);   or   out_stream << 'H';  or   out_stream << "H";
 73  49  01001001    &#73;  I     Capital I                    out_stream.put(73);   or   out_stream << 'I';  or   out_stream << "I";
 74  4A  01001010    &#74;  J     Capital J                    out_stream.put(74);   or   out_stream << 'J';  or   out_stream << "J";
 75  4B  01001011    &#75;  K     Capital K                    out_stream.put(75);   or   out_stream << 'K';  or   out_stream << "K";
 76  4C  01001100    &#76;  L     Capital L                    out_stream.put(76);   or   out_stream << 'L';  or   out_stream << "L";
 77  4D  01001101    &#77;  M     Capital M                    out_stream.put(77);   or   out_stream << 'M';  or   out_stream << "M";
 78  4E  01001110    &#78;  N     Capital N                    out_stream.put(78);   or   out_stream << 'N';  or   out_stream << "N";
 79  4F  01001111    &#79;  O     Capital O                    out_stream.put(79);   or   out_stream << 'O';  or   out_stream << "O";
 80  50  01010000    &#80;  P     Capital P                    out_stream.put(80);   or   out_stream << 'P';  or   out_stream << "P";
 81  51  01010001    &#81;  Q     Capital Q                    out_stream.put(81);   or   out_stream << 'Q';  or   out_stream << "Q";
 82  52  01010010    &#82;  R     Capital R                    out_stream.put(82);   or   out_stream << 'R';  or   out_stream << "R";
 83  53  01010011    &#83;  S     Capital S                    out_stream.put(83);   or   out_stream << 'S';  or   out_stream << "S";
 84  54  01010100    &#84;  T     Capital T                    out_stream.put(84);   or   out_stream << 'T';  or   out_stream << "T";
 85  55  01010101    &#85;  U     Capital U                    out_stream.put(85);   or   out_stream << 'U';  or   out_stream << "U";
 86  56  01010110    &#86;  V     Capital V                    out_stream.put(86);   or   out_stream << 'V';  or   out_stream << "V";
 87  57  01010111    &#87;  W     Capital W                    out_stream.put(87);   or   out_stream << 'W';  or   out_stream << "W";
 88  58  01011000    &#88;  X     Capital X                    out_stream.put(88);   or   out_stream << 'X';  or   out_stream << "X";
 89  59  01011001    &#89;  Y     Capital Y                    out_stream.put(89);   or   out_stream << 'Y';  or   out_stream << "Y";
 90  5A  01011010    &#90;  Z     Capital Z                    out_stream.put(90);   or   out_stream << 'Z';  or   out_stream << "Z";
 91  5B  01011011    &#91;  [     Left square bracket          out_stream.put(91);   or   out_stream << '[';  or   out_stream << "[";
 92  5C  01011100    &#92;  \     Backslash                    out_stream.put(92);   or   out_stream <<'\\';  or   out_stream <<"\\";   As escape sequence so C++ knows you want the backslash given to file/terminal rather than it being an escape sequence.
 93  5D  01011101    &#93;  ]     Right square bracket         out_stream.put(93);   or   out_stream << ']';  or   out_stream << "]";
 94  5E  01011110    &#94;  ^     Caret/circumflex             out_stream.put(94);   or   out_stream << '^';  or   out_stream << "^";
 95  5F  01011111    &#95;  _     Underscore                   out_stream.put(95);   or   out_stream << '_';  or   out_stream << "_";
 96  60  01100000    &#96;  `     Grave/accent                 out_stream.put(96);   or   out_stream << '`';  or   out_stream << "`";
 97  61  01100001    &#97;  a     Small a                      out_stream.put(97);   or   out_stream << 'a';  or   out_stream << "a";
 98  62  01100010    &#98;  b     Small b                      out_stream.put(98);   or   out_stream << 'b';  or   out_stream << "b";
 99  63  01100011    &#99;  c     Small c                      out_stream.put(99);   or   out_stream << 'c';  or   out_stream << "c";
100  64  01100100   &#100;  d     Small d                      out_stream.put(100);  or   out_stream << 'd';  or   out_stream << "d";
101  65  01100101   &#101;  e     Small e                      out_stream.put(101);  or   out_stream << 'e';  or   out_stream << "e";
102  66  01100110   &#102;  f     Small f                      out_stream.put(102);  or   out_stream << 'f';  or   out_stream << "f";
103  67  01100111   &#103;  g     Small g                      out_stream.put(103);  or   out_stream << 'g';  or   out_stream << "g";
104  68  01101000   &#104;  h     Small h                      out_stream.put(104);  or   out_stream << 'h';  or   out_stream << "h";
105  69  01101001   &#105;  i     Small i                      out_stream.put(105);  or   out_stream << 'i';  or   out_stream << "i";
106  6A  01101010   &#106;  j     Small j                      out_stream.put(106);  or   out_stream << 'j';  or   out_stream << "j";
107  6B  01101011   &#107;  k     Small k                      out_stream.put(107);  or   out_stream << 'k';  or   out_stream << "k";
108  6C  01101100   &#108;  l     Small l                      out_stream.put(108);  or   out_stream << 'l';  or   out_stream << "l";
109  6D  01101101   &#109;  m     Small m                      out_stream.put(109);  or   out_stream << 'm';  or   out_stream << "m";
110  6E  01101110   &#110;  n     Small n                      out_stream.put(110);  or   out_stream << 'n';  or   out_stream << "n";
111  6F  01101111   &#111;  o     Small o                      out_stream.put(111);  or   out_stream << 'o';  or   out_stream << "o";
112  70  01110000   &#112;  p     Small p                      out_stream.put(112);  or   out_stream << 'p';  or   out_stream << "p";
113  71  01110001   &#113;  q     Small q                      out_stream.put(113);  or   out_stream << 'q';  or   out_stream << "q";
114  72  01110010   &#114;  r     Small r                      out_stream.put(114);  or   out_stream << 'r';  or   out_stream << "r";
115  73  01110011   &#115;  s     Small s                      out_stream.put(115);  or   out_stream << 's';  or   out_stream << "s";
116  74  01110100   &#116;  t     Small t                      out_stream.put(116);  or   out_stream << 't';  or   out_stream << "t";
117  75  01110101   &#117;  u     Small u                      out_stream.put(117);  or   out_stream << 'u';  or   out_stream << "u";
118  76  01110110   &#118;  v     Small v                      out_stream.put(118);  or   out_stream << 'v';  or   out_stream << "v";
119  77  01110111   &#119;  w     Small w                      out_stream.put(119);  or   out_stream << 'w';  or   out_stream << "w";
120  78  01111000   &#120;  x     Small x                      out_stream.put(120);  or   out_stream << 'x';  or   out_stream << "x";
121  79  01111001   &#121;  y     Small y                      out_stream.put(121);  or   out_stream << 'y';  or   out_stream << "y";
122  7A  01111010   &#122;  z     Small z                      out_stream.put(122);  or   out_stream << 'z';  or   out_stream << "z";
123  7B  01111011   &#123;  {     Left curly bracket           out_stream.put(123);  or   out_stream << '{';  or   out_stream << "{";
124  7C  01111100   &#124;  |     Unix pipe                    out_stream.put(124);  or   out_stream << '|';  or   out_stream << "|";
125  7D  01111101   &#125;  }     Right curly bracket          out_stream.put(125);  or   out_stream << '}';  or   out_stream << "}";
126  7E  01111110   &#126;  ~     Tilde                        out_stream.put(126);  or   out_stream << '~';  or   out_stream << "~";
127  7F  01111111   &#127;  DEL   Delete                       out_stream.put(127);
128  80  10000000   -                                       out_stream.put(128);  or   out_stream.put(-128);   (continues increasing but from negatives)
129  81  10000001   -                                       out_stream.put(129);  or   out_stream.put(-127);
130  82  10000010   -                                       out_stream.put(130);  or   out_stream.put(-126);
131  83  10000011   -                                       out_stream.put(131);  or   out_stream.put(-125);
132  84  10000100   -                                       out_stream.put(132);  or   out_stream.put(-124);
133  85  10000101   -                                       out_stream.put(133);  or   out_stream.put(-123);
134  86  10000110   -                                       out_stream.put(134);  or   out_stream.put(-122);
135  87  10000111   -                                       out_stream.put(135);  or   out_stream.put(-121);
136  88  10001000   -                                       out_stream.put(136);  or   out_stream.put(-120);
137  89  10001001   -                                       out_stream.put(137);  or   out_stream.put(-119);
138  8A  10001010   -                                       out_stream.put(138);  or   out_stream.put(-118);
139  8B  10001011   -                                       out_stream.put(139);  or   out_stream.put(-117);
140  8C  10001100   -                                       out_stream.put(140);  or   out_stream.put(-116);
141  8D  10001101   -                                        out_stream.put(141);  or   out_stream.put(-115);
142  8E  10001110   -                                       out_stream.put(142);  or   out_stream.put(-114);
143  8F  10001111   -                                       out_stream.put(143);  or   out_stream.put(-113);
144  90  10010000   -                                       out_stream.put(144);  or   out_stream.put(-112);
145  91  10010001   -                                       out_stream.put(145);  or   out_stream.put(-111);
146  92  10010010   -                                       out_stream.put(146);  or   out_stream.put(-110);
147  93  10010011   -                                       out_stream.put(147);  or   out_stream.put(-109);
148  94  10010100   -                                       out_stream.put(148);  or   out_stream.put(-108);
149  95  10010101   -                                        out_stream.put(149);  or   out_stream.put(-107);
150  96  10010110   -                                       out_stream.put(150);  or   out_stream.put(-106);
151  97  10010111   -                                       out_stream.put(151);  or   out_stream.put(-105);
152  98  10011000   -                                       out_stream.put(152);  or   out_stream.put(-104);
153  99  10011001   -                                      out_stream.put(153);  or   out_stream.put(-103);
154  9A  10011010   -                                       out_stream.put(154);  or   out_stream.put(-102);
155  9B  10011011   -                                       out_stream.put(155);  or   out_stream.put(-101);
156  9C  10011100   -                                        out_stream.put(156);  or   out_stream.put(-100);
157  9D  10011101   -                                       out_stream.put(157);  or   out_stream.put(-99);
158  9E  10011110   -                                        out_stream.put(158);  or   out_stream.put(-98);
159  9F  10011111   -                                       out_stream.put(159);  or   out_stream.put(-97);
160  A0  10100000   &#160;                                     out_stream.put(160);  or   out_stream.put(-96);
161  A1  10100001   &#161;  ¡                                  out_stream.put(161);  or   out_stream.put(-95);
162  A2  10100010   &#162;  ¢                                  out_stream.put(162);  or   out_stream.put(-94);
163  A3  10100011   &#163;  £                                  out_stream.put(163);  or   out_stream.put(-93);
164  A4  10100100   &#164;  ¤                                  out_stream.put(164);  or   out_stream.put(-92);
165  A5  10100101   &#165;  ¥                                  out_stream.put(165);  or   out_stream.put(-91);
166  A6  10100110   &#166;  ¦                                  out_stream.put(166);  or   out_stream.put(-90);
167  A7  10100111   &#167;  §                                  out_stream.put(167);  or   out_stream.put(-89);
168  A8  10101000   &#168;  ¨                                  out_stream.put(168);  or   out_stream.put(-88);
169  A9  10101001   &#169;  ©                                  out_stream.put(169);  or   out_stream.put(-87);
170  AA  10101010   &#170;  ª                                  out_stream.put(170);  or   out_stream.put(-86);
171  AB  10101011   &#171;  «                                  out_stream.put(171);  or   out_stream.put(-85);
172  AC  10101100   &#172;  ¬                                  out_stream.put(172);  or   out_stream.put(-84);
173  AD  10101101   &#173;  ­                                   out_stream.put(173);  or   out_stream.put(-83);
174  AE  10101110   &#174;  ®                                  out_stream.put(174);  or   out_stream.put(-82);
175  AF  10101111   &#175;  ¯                                  out_stream.put(175);  or   out_stream.put(-81);
176  B0  10110000   &#176;  °                                  out_stream.put(176);  or   out_stream.put(-80);
177  B1  10110001   &#177;  ±                                  out_stream.put(177);  or   out_stream.put(-79);
178  B2  10110010   &#178;  ²                                  out_stream.put(178);  or   out_stream.put(-78);
179  B3  10110011   &#179;  ³                                  out_stream.put(179);  or   out_stream.put(-77);
180  B4  10110100   &#180;  ´                                  out_stream.put(180);  or   out_stream.put(-76);
181  B5  10110101   &#181;  µ                                  out_stream.put(181);  or   out_stream.put(-75);
182  B6  10110110   &#182;  ¶                                  out_stream.put(182);  or   out_stream.put(-74);
183  B7  10110111   &#183;  ·                                  out_stream.put(183);  or   out_stream.put(-73);
184  B8  10111000   &#184;  ¸                                  out_stream.put(184);  or   out_stream.put(-72);
185  B9  10111001   &#185;  ¹                                  out_stream.put(185);  or   out_stream.put(-71);
186  BA  10111010   &#186;  º                                  out_stream.put(186);  or   out_stream.put(-70);
187  BB  10111011   &#187;  »                                  out_stream.put(187);  or   out_stream.put(-69);
188  BC  10111100   &#188;  ¼                                  out_stream.put(188);  or   out_stream.put(-68);
189  BD  10111101   &#189;  ½                                  out_stream.put(189);  or   out_stream.put(-67);
190  BE  10111110   &#190;  ¾                                  out_stream.put(190);  or   out_stream.put(-66);
191  BF  10111111   &#191;  ¿                                  out_stream.put(191);  or   out_stream.put(-65);
192  C0  11000000   &#192;  À                                  out_stream.put(192);  or   out_stream.put(-64);
193  C1  11000001   &#193;  Á                                  out_stream.put(193);  or   out_stream.put(-63);
194  C2  11000010   &#194;  Â                                  out_stream.put(194);  or   out_stream.put(-62);
195  C3  11000011   &#195;  Ã                                  out_stream.put(195);  or   out_stream.put(-61);
196  C4  11000100   &#196;  Ä                                  out_stream.put(196);  or   out_stream.put(-60);
197  C5  11000101   &#197;  Å                                  out_stream.put(197);  or   out_stream.put(-59);
198  C6  11000110   &#198;  Æ                                  out_stream.put(198);  or   out_stream.put(-58);
199  C7  11000111   &#199;  Ç                                  out_stream.put(199);  or   out_stream.put(-57);
200  C8  11001000   &#200;  È                                  out_stream.put(200);  or   out_stream.put(-56);
201  C9  11001001   &#201;  É                                  out_stream.put(201);  or   out_stream.put(-55);
202  CA  11001010   &#202;  Ê                                  out_stream.put(202);  or   out_stream.put(-54);
203  CB  11001011   &#203;  Ë                                  out_stream.put(203);  or   out_stream.put(-53);
204  CC  11001100   &#204;  Ì                                  out_stream.put(204);  or   out_stream.put(-52);
205  CD  11001101   &#205;  Í                                  out_stream.put(205);  or   out_stream.put(-51);
206  CE  11001110   &#206;  Î                                  out_stream.put(206);  or   out_stream.put(-50);
207  CF  11001111   &#207;  Ï                                  out_stream.put(207);  or   out_stream.put(-49);
208  D0  11010000   &#208;  Ð                                  out_stream.put(208);  or   out_stream.put(-48);
209  D1  11010001   &#209;  Ñ                                  out_stream.put(209);  or   out_stream.put(-47);
210  D2  11010010   &#210;  Ò                                  out_stream.put(210);  or   out_stream.put(-46);
211  D3  11010011   &#211;  Ó                                  out_stream.put(211);  or   out_stream.put(-45);
212  D4  11010100   &#212;  Ô                                  out_stream.put(212);  or   out_stream.put(-44);
213  D5  11010101   &#213;  Õ                                  out_stream.put(213);  or   out_stream.put(-43);
214  D6  11010110   &#214;  Ö                                  out_stream.put(214);  or   out_stream.put(-42);
215  D7  11010111   &#215;  ×                                  out_stream.put(215);  or   out_stream.put(-41);
216  D8  11011000   &#216;  Ø                                  out_stream.put(216);  or   out_stream.put(-40);
217  D9  11011001   &#217;  Ù                                  out_stream.put(217);  or   out_stream.put(-39);
218  DA  11011010   &#218;  Ú                                  out_stream.put(218);  or   out_stream.put(-38);
219  DB  11011011   &#219;  Û                                  out_stream.put(219);  or   out_stream.put(-37);
220  DC  11011100   &#220;  Ü                                  out_stream.put(220);  or   out_stream.put(-36);
221  DD  11011101   &#221;  Ý                                  out_stream.put(221);  or   out_stream.put(-35);
222  DE  11011110   &#222;  Þ                                  out_stream.put(222);  or   out_stream.put(-34);
223  DF  11011111   &#223;  ß                                  out_stream.put(223);  or   out_stream.put(-33);
224  E0  11100000   &#224;  à                                  out_stream.put(224);  or   out_stream.put(-32);
225  E1  11100001   &#225;  á                                  out_stream.put(225);  or   out_stream.put(-31);
226  E2  11100010   &#226;  â                                  out_stream.put(226);  or   out_stream.put(-30);
227  E3  11100011   &#227;  ã                                  out_stream.put(227);  or   out_stream.put(-29);
228  E4  11100100   &#228;  ä                                  out_stream.put(228);  or   out_stream.put(-28);
229  E5  11100101   &#229;  å                                  out_stream.put(229);  or   out_stream.put(-27);
230  E6  11100110   &#230;  æ                                  out_stream.put(230);  or   out_stream.put(-26);
231  E7  11100111   &#231;  ç                                  out_stream.put(231);  or   out_stream.put(-25);
232  E8  11101000   &#232;  è                                  out_stream.put(232);  or   out_stream.put(-24);
233  E9  11101001   &#233;  é                                  out_stream.put(233);  or   out_stream.put(-23);
234  EA  11101010   &#234;  ê                                  out_stream.put(234);  or   out_stream.put(-22);
235  EB  11101011   &#235;  ë                                  out_stream.put(235);  or   out_stream.put(-21);
236  EC  11101100   &#236;  ì                                  out_stream.put(236);  or   out_stream.put(-20);
237  ED  11101101   &#237;  í                                  out_stream.put(237);  or   out_stream.put(-19);
238  EE  11101110   &#238;  î                                  out_stream.put(238);  or   out_stream.put(-18);
239  EF  11101111   &#239;  ï                                  out_stream.put(239);  or   out_stream.put(-17);
240  F0  11110000   &#240;  ð                                  out_stream.put(240);  or   out_stream.put(-16);
241  F1  11110001   &#241;  ñ                                  out_stream.put(241);  or   out_stream.put(-15);
242  F2  11110010   &#242;  ò                                  out_stream.put(242);  or   out_stream.put(-14);
243  F3  11110011   &#243;  ó                                  out_stream.put(243);  or   out_stream.put(-13);
244  F4  11110100   &#244;  ô                                  out_stream.put(244);  or   out_stream.put(-12);
245  F5  11110101   &#245;  õ                                  out_stream.put(245);  or   out_stream.put(-11);
246  F6  11110110   &#246;  ö                                  out_stream.put(246);  or   out_stream.put(-10);
247  F7  11110111   &#247;  ÷                                  out_stream.put(247);  or   out_stream.put(-9);
248  F8  11111000   &#248;  ø                                  out_stream.put(248);  or   out_stream.put(-8);
249  F9  11111001   &#249;  ù                                  out_stream.put(249);  or   out_stream.put(-7);
250  FA  11111010   &#250;  ú                                  out_stream.put(250);  or   out_stream.put(-6);
251  FB  11111011   &#251;  û                                  out_stream.put(251);  or   out_stream.put(-5);
252  FC  11111100   &#252;  ü                                  out_stream.put(252);  or   out_stream.put(-4);
253  FD  11111101   &#253;  ý                                  out_stream.put(253);  or   out_stream.put(-3);
254  FE  11111110   &#254;  þ                                  out_stream.put(254);  or   out_stream.put(-2);
255  FF  11111111   &#255;  ÿ                                  out_stream.put(255);  or   out_stream.put(-1);


    ####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*####
    ##'                                         '##
    #       With negatives (signed), order =      #
    #        0 up to 127 then  -128 up to -1      #
    ##,                                         ,##
    ####*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##*/








///###############################################################################################################################
///###############################################################################################################################
///###############################################################################################################################
/* Other C++ commands for files & folders:

FOLDERS/FILES:
system("ls > my_list.txt");               //Creates a text file in running dir--containing a list of file names in that same dir (standard "ls" command in GNU+Linux.)
system("mkdir keys");                     //Creates folder, append -p for no error if already exists.
system("mkdir /home/nikolay/Desktop/F");  //Creates folder elsewhere.
system("mkdir keys/Other");               //Creates folder within a folder.
out_stream.open("keys/file_1");           //File I/O in folders.
out_stream.open("/home/nikolay/keys/a");  //File I/O in folders elsewhere.

MKDIR WITH VARIABLE:
#include <sys/stat.h> //For mkdir() (creating folders using variable.)
mkdir(file_name, 0777);

MKDIR WITH VARIABLE, WITHOUT INCLUDE DIRECTIVES:
char folder_name[100] = {"mkdir Folder_1"};
system(folder_name);

REMOVING:
remove("file_name");              //as actual file. Add path as above if in folder.
remove(file_name);                //as variable for file (char array.)
system("rm -r /path_to_FOLDER");  //as directory.

WEB:
system("wget -q https://github.com/compromise-evident/Authorship/archive/refs/heads/main.zip");

DECOMPRESS:
system("unzip -qq main.zip");

AS VARIABLE:
char groupOTP[100] = {"wget -q https://github.com/compromise-evident/groupOTP/archive/refs/heads/main.zip"};
system(groupOTP);

RUN ANOTHER C++ PROGRAM:
system("/home/user/Desktop/Authorship");   //That Authorship file is the executable made by Geany or with the g++ command.

WRITE TERMINAL OUTPUT TO FILE INSTEAD:
system("sha256sum main.zip > hash_file");

//Basically, any bash commands will work in C++ if wrapped in system("");  See ss64.com/bash/
*/








///###############################################################################################################################
///###############################################################################################################################
///###############################################################################################################################
/* True C++ data type specs WITHOUT unspecified behavior so far.
________________________________________________________________________________________________________________________
char           -128 to
                127

                  0 to
                255                               (unsigned)                      256   total items for signed/unsigned.
________________________________________________________________________________________________________________________
short          -32,768 to
                32,767

                     0 to
                65,535                            (unsigned)                      256^2 total items for signed/unsigned.
________________________________________________________________________________________________________________________
int            -2,147,483,648 to
                2,147,483,647

                            0 to
                4,294,967,295                     (unsigned)                      256^4 total items for signed/unsigned.
________________________________________________________________________________________________________________________
long long      -9,223,372,036,854,775,807 to
                9,223,372,036,854,775,807

                                        0 to                                      256^8    total items for signed.
               18,446,744,073,709,551,615         (unsigned)                      256^8 -1 total items for unsigned.
________________________________________________________________________________________________________________________

Init above/below these bounds means C++ will sometimes automatically convert to some inverse without telling you.
in_stream.get() for signed char gives the same -128 to 127 file items which accounts for 256 different file items.*/








///###############################################################################################################################
///###############################################################################################################################
///###############################################################################################################################
/* GNU+Linux tools.

apt install actiona artha audacity bleachbit exiv2 geany geany-plugin-automark geany-plugin-spellcheck g++ gnome-paint gparted gqrx-sdr inkscape krita openshot qasmixer vlc xz-utils

actiona                 GUI  Tool to emulate human activity without programming or using suspected tools.)
artha                   GUI  Offline thesaurus & dictionary.
audacity                GUI  Audio editor & sound recorder.
bleachbit               GUI  Wipe logs & all kinds of stuff.
exiv2                  >CLI  Delete/modify/print image EXIF data. Commands: exiv2 print /path/to/file    exiv2 delete /path/to/file.
geany                   GUI  Fast & lightweight IDE & text editor (if src looks weird on ms-notepad, this is for you. Characters 13 & 10 are displayed as intended.)
geany-plugin-automark   GUI  Global highlighting of what's selected or at cursor (Geany.)
geany-plugin-spellcheck GUI  Grammar (Geany, overwrite hot-key to Ctrl+G to help remember.)
g++                    >CLI  GNU compiler for C++ (runs C++ in Geany, industry standard compiler. Install gcc if programming in C.) Command: g++ /path/to/file.
gnome-paint             GUI  Beautiful replacement for the proprietary garbage ms-paint.

gparted                 GUI  GNU partition editor (wipe & format any storage device without fail.) How to in 3 quick steps (right-click & unmount drive first):
                             1. Erase everything. If errors, your fault; keep unplugging, plugging in, erasing, & clicking ignore. Apply operations (green check-mark.)
                             2. Go to Device >> Create Partition Table... and hit apply. This is the vital step you've always missed.
                             3. Go to Partition >> New. Use file system: fat32 (for max compatibility.) Apply operations (green check-mark.)
                             IMPORTANT: always use the software "eject/safely remove" features so they can tell you if the device is not busy,
                                        otherwise you can corrupt & set it to read-only (still refresh-able with this powerful program.)
                                        Some flash/SSD devices have on-board RAM as a cache; a computer might tell you that it's ok to
                                        unplug the device but it might still be busy transferring data from its cache to its storage.
                                        Let it sit there. This happens during big operations such as iso burning with the dd command.
                                        As the flash card/USB stick gets hot, write speeds begin to crawl while SLOWLY retrieving from
                                        its cache which is full. And so it needs to sit there until the cache is empty. Let it sit and
                                        and receive power otherwise the transfer is corrupted and the OS image will fail as it boots.
                             REMINDER: secure main drives and storage should always be spinning disk drives for overwriting abilities!

gqrx-sdr                GUI  Interface to software-defined radio dongles. Comes with gnuradio. Works for RTL-SDR.
inkscape                GUI  Powerful vector graphics manipulation.
krita                   GUI  Advanced digital art creator.
openshot                GUI  Video editor and advanced frame dispenser.
qasmixer                GUI  Allows volume-up for headphones on old laptops (set & forget, excellent quality audio.)
vlc                     GUI  Universal media interface (good for music & video, safely plays corrupted and partly-downloaded video, plays streams from online source.)
xz-utils               >CLI  Compress/decompress .xz files (especially downloaded OS images for Raspberry Pi.) Command: xz -d -v /path/to/file.    */








///###############################################################################################################################
///###############################################################################################################################
///###############################################################################################################################
/* GNU+Linux commands.

sha1sum /path/to/file     Also you may drag & drop file into terminal to give path: '/path/to/file'
sha256sum /path/to/file   Also you may drag & drop file into terminal to give path: '/path/to/file'
sha512sum /path/to/file   Also you may drag & drop file into terminal to give path: '/path/to/file'

apt-mark hold package_name     (stop updates to this package)
apt-mark unhold package_name   (undo above)
apt-mark showhold              (shows what's on hold)

lsblk           (list block devices) (do lsblk -f to see names)
chmod           (change file/directory permissions)
passwd          (change passwd for user)
passwd root     (change passwd for root)
g++             (create executable) (then enter dir to run)   Also you may drag & drop file into terminal to give path: '/path/to/file'
dd              (convert and copy a file) (dd if=/path of=/dev/sdb   for iso.) Also you may drag & drop file into terminal to give path: '/path/to/file'   Use command lsblk to see names of devices.*/
