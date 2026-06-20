/*Creates a minimalist analysis file about your file.                           Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
Occurrence, distinct, raw, and text. This cpp contains
resources; it should be the first tab in your editor.*/

#include <bitset>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
int main()
{	int raw_byte;
	char file_byte;
	std::ifstream in_stream;
	std::ofstream out_stream;
	
	//Gets path (files & folders).
	std::cout << "\nDrop/enter file:\n";
	std::string path; std::getline(std::cin, path); if(path[0] == '\0') {std::getline(std::cin, path);}
	if(path[0] == '\'') {path.erase(0, 1); path.pop_back(); path.pop_back();} //Fixes path if drag-n-dropped.
	in_stream.open(path); if(!in_stream) {std::cout << "\nNo path " << path << "\n"; return 1;} in_stream.close();
	
	//Checks if file is empty.
	unsigned long long size = std::filesystem::file_size(path);
	if(size == 0) {std::cout << "\nEmpty file.\n"; return 0;}
	
	//Gets byte occurrence.
	in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Byte occurrence).\n"; return 1;}
	unsigned long long byte_occur[256] = {0};
	for(; in_stream.get(file_byte);)
	{	raw_byte = file_byte & 0xFF;
		byte_occur[raw_byte]++;
	}
	in_stream.close();
	
	//Gets bit occurrence (from byte occurrence).
	unsigned long long ones = 0, zeros = 0;
	for(int a = 0; a < 256; a++)
	{	std::bitset<8> bits(a);
		ones  += (  bits. count() * byte_occur[a]);
		zeros += ((~bits).count() * byte_occur[a]);
	}
	
	//Writes bit occurrence.
	out_stream.open("analysis"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Bit occurrence).\n"; return 1;}
	out_stream << path << "\n\n"
	           << "occurrence of bit 0: " << zeros << "\n"
	           << "occurrence of bit 1: " << ones  << "\n";
	out_stream.close();
	
	//Appends byte occurrence.
	out_stream.open("analysis", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Byte occurrence).\n"; return 1;}
	out_stream << "\n";
	for(int a = 0; a < 256; a++) {out_stream << "occurrence of byte " << a << ": " << byte_occur[a] << "\n";}
	out_stream.close();
	
	//Appends distinct and total.
	out_stream.open("analysis", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Distinct and total).\n"; return 1;}
	unsigned long long distinct = 0, total = 0;
	for(int a = 0; a < 256; a++)
	{	if(byte_occur[a] != 0) {distinct++;}
		total += byte_occur[a];
	}
	out_stream << "\n" << distinct << " distinct, " << total << " total" << "\n";
	out_stream.close();
	
	//Appends every byte raw.
	in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Every byte raw).\n"; return 1;}
	out_stream.open("analysis", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Every byte raw).\n"; return 1;}
	out_stream << "\nEvery byte raw:\n";
	for(; in_stream.get(file_byte);) {raw_byte = file_byte & 0xFF; out_stream << raw_byte << "\n";}
	in_stream.close();
	out_stream.close();
	
	//Appends only the 97 standard text bytes (9, 10, and 32-126).
	in_stream.open(path); if(!in_stream) {std::cout << "\nCan't open file for reading. (Only the 97 standard text bytes).\n"; return 1;}
	out_stream.open("analysis", std::ios::app); if(!out_stream) {std::cout << "\nCan't open file for writing. (Only the 97 standard text bytes).\n"; return 1;}
	out_stream << "\nOnly the 97 standard text bytes (9, 10, and 32-126):\n";
	for(; in_stream.get(file_byte);)
	{	if      ((file_byte > 31) && (file_byte < 127)) {out_stream.put(file_byte);}
		else if ((file_byte == 9) || (file_byte == 10)) {out_stream.put(file_byte);}
	}
	in_stream.close();
	out_stream.close();
}

/*

#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                               Raw file bytes                               ,#
#'                                 (0 to 255)                                 '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

CONVERT: int raw_byte = file_byte & 0xFF;             //raw_byte is now 0 to 255

WRITE: out_stream.put(raw_byte);








#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                               Table of bytes                               ,#
#'                                                                            '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

Dec	Hex	  Binary   Char  Description

  0  00  00000000  NUL   Null                         out_stream.put(0);    or   out_stream << '\0';
  1  01  00000001  SOH   Start of Header              out_stream.put(1);
  2  02  00000010  STX   Start of Text                out_stream.put(2);
  3  03  00000011  ETX   End of Text                  out_stream.put(3);
  4  04  00000100  EOT   End of Transmission          out_stream.put(4);
  5  05  00000101  ENQ   Enquiry                      out_stream.put(5);
  6  06  00000110  ACK   Acknowledge                  out_stream.put(6);
  7  07  00000111  BEL   Bell                         out_stream.put(7);
  8  08  00001000  BS    Backspace                    out_stream.put(8);
  9  09  00001001  HT    Horizontal Tab               out_stream.put(9);    or   out_stream << '\t';   (Tab)
 10  0A  00001010  LF    Line Feed                    out_stream.put(10);   or   out_stream << '\n';   (New line for Linux/Mac)
 11  0B  00001011  VT    Vertical Tab                 out_stream.put(11);
 12  0C  00001100  FF    Form Feed                    out_stream.put(12);
 13  0D  00001101  CR    Carriage Return              out_stream.put(13);   or   out_stream << '\r';   (New line for Windows if followed by 10)
 14  0E  00001110  SO    Shift Out                    out_stream.put(14);
 15  0F  00001111  SI    Shift In                     out_stream.put(15);
 16  10  00010000  DLE   Data Link Escape             out_stream.put(16);
 17  11  00010001  DC1   Device Control 1             out_stream.put(17);
 18  12  00010010  DC2   Device Control 2             out_stream.put(18);
 19  13  00010011  DC3   Device Control 3             out_stream.put(19);
 20  14  00010100  DC4   Device Control 4             out_stream.put(20);
 21  15  00010101  NAK   Negative Acknowledge         out_stream.put(21);
 22  16  00010110  SYN   Synchronize                  out_stream.put(22);
 23  17  00010111  ETB   End of Transmission Block    out_stream.put(23);
 24  18  00011000  CAN   Cancel                       out_stream.put(24);
 25  19  00011001  EM    End of Medium                out_stream.put(25);
 26  1A  00011010  SUB   Substitute                   out_stream.put(26);
 27  1B  00011011  ESC   Escape                       out_stream.put(27);
 28  1C  00011100  FS    File Separator               out_stream.put(28);
 29  1D  00011101  GS    Group Separator              out_stream.put(29);
 30  1E  00011110  RS    Record Separator             out_stream.put(30);
 31  1F  00011111  US    Unit Separator               out_stream.put(31);
 32  20  00100000  space Blank or space               out_stream.put(32);   or   out_stream << ' ';   (32-126 begins here. Space to tilde.)
 33  21  00100001  !     Exclamation mark             out_stream.put(33);
 34  22  00100010  "     Double quote                 out_stream.put(34);
 35  23  00100011  #     Number sign                  out_stream.put(35);
 36  24  00100100  $     Dollar sign                  out_stream.put(36);
 37  25  00100101  %     Percent                      out_stream.put(37);
 38  26  00100110  &     Ampersand                    out_stream.put(38);
 39  27  00100111  '     Single quote                 out_stream.put(39);
 40  28  00101000  (     Left parenthesis             out_stream.put(40);
 41  29  00101001  )     Right parenthesis            out_stream.put(41);
 42  2A  00101010  *     Asterisk                     out_stream.put(42);
 43  2B  00101011  +     Plus                         out_stream.put(43);
 44  2C  00101100  ,     Comma                        out_stream.put(44);
 45  2D  00101101  -     Minus                        out_stream.put(45);
 46  2E  00101110  .     Period                       out_stream.put(46);
 47  2F  00101111  /     Slash                        out_stream.put(47);
 48  30  00110000  0     Zero                         out_stream.put(48);
 49  31  00110001  1     One                          out_stream.put(49);
 50  32  00110010  2     Two                          out_stream.put(50);
 51  33  00110011  3     Three                        out_stream.put(51);
 52  34  00110100  4     Four                         out_stream.put(52);
 53  35  00110101  5     Five                         out_stream.put(53);
 54  36  00110110  6     Six                          out_stream.put(54);
 55  37  00110111  7     Seven                        out_stream.put(55);
 56  38  00111000  8     Eight                        out_stream.put(56);
 57  39  00111001  9     Nine                         out_stream.put(57);
 58  3A  00111010  :     Colon                        out_stream.put(58);
 59  3B  00111011  ;     Semicolon                    out_stream.put(59);
 60  3C  00111100  <     Less than                    out_stream.put(60);
 61  3D  00111101  =     Equality sign                out_stream.put(61);
 62  3E  00111110  >     Greater than                 out_stream.put(62);
 63  3F  00111111  ?     Question mark                out_stream.put(63);
 64  40  01000000  @     At sign                      out_stream.put(64);
 65  41  01000001  A     Capital A                    out_stream.put(65);
 66  42  01000010  B     Capital B                    out_stream.put(66);
 67  43  01000011  C     Capital C                    out_stream.put(67);
 68  44  01000100  D     Capital D                    out_stream.put(68);
 69  45  01000101  E     Capital E                    out_stream.put(69);
 70  46  01000110  F     Capital F                    out_stream.put(70);
 71  47  01000111  G     Capital G                    out_stream.put(71);
 72  48  01001000  H     Capital H                    out_stream.put(72);
 73  49  01001001  I     Capital I                    out_stream.put(73);
 74  4A  01001010  J     Capital J                    out_stream.put(74);
 75  4B  01001011  K     Capital K                    out_stream.put(75);
 76  4C  01001100  L     Capital L                    out_stream.put(76);
 77  4D  01001101  M     Capital M                    out_stream.put(77);
 78  4E  01001110  N     Capital N                    out_stream.put(78);
 79  4F  01001111  O     Capital O                    out_stream.put(79);
 80  50  01010000  P     Capital P                    out_stream.put(80);
 81  51  01010001  Q     Capital Q                    out_stream.put(81);
 82  52  01010010  R     Capital R                    out_stream.put(82);
 83  53  01010011  S     Capital S                    out_stream.put(83);
 84  54  01010100  T     Capital T                    out_stream.put(84);
 85  55  01010101  U     Capital U                    out_stream.put(85);
 86  56  01010110  V     Capital V                    out_stream.put(86);
 87  57  01010111  W     Capital W                    out_stream.put(87);
 88  58  01011000  X     Capital X                    out_stream.put(88);
 89  59  01011001  Y     Capital Y                    out_stream.put(89);
 90  5A  01011010  Z     Capital Z                    out_stream.put(90);
 91  5B  01011011  [     Left square bracket          out_stream.put(91);
 92  5C  01011100  \     Backslash                    out_stream.put(92);
 93  5D  01011101  ]     Right square bracket         out_stream.put(93);
 94  5E  01011110  ^     Caret/circumflex             out_stream.put(94);
 95  5F  01011111  _     Underscore                   out_stream.put(95);
 96  60  01100000  `     Grave/accent                 out_stream.put(96);
 97  61  01100001  a     Small a                      out_stream.put(97);
 98  62  01100010  b     Small b                      out_stream.put(98);
 99  63  01100011  c     Small c                      out_stream.put(99);
100  64  01100100  d     Small d                      out_stream.put(100);
101  65  01100101  e     Small e                      out_stream.put(101);
102  66  01100110  f     Small f                      out_stream.put(102);
103  67  01100111  g     Small g                      out_stream.put(103);
104  68  01101000  h     Small h                      out_stream.put(104);
105  69  01101001  i     Small i                      out_stream.put(105);
106  6A  01101010  j     Small j                      out_stream.put(106);
107  6B  01101011  k     Small k                      out_stream.put(107);
108  6C  01101100  l     Small l                      out_stream.put(108);
109  6D  01101101  m     Small m                      out_stream.put(109);
110  6E  01101110  n     Small n                      out_stream.put(110);
111  6F  01101111  o     Small o                      out_stream.put(111);
112  70  01110000  p     Small p                      out_stream.put(112);
113  71  01110001  q     Small q                      out_stream.put(113);
114  72  01110010  r     Small r                      out_stream.put(114);
115  73  01110011  s     Small s                      out_stream.put(115);
116  74  01110100  t     Small t                      out_stream.put(116);
117  75  01110101  u     Small u                      out_stream.put(117);
118  76  01110110  v     Small v                      out_stream.put(118);
119  77  01110111  w     Small w                      out_stream.put(119);
120  78  01111000  x     Small x                      out_stream.put(120);
121  79  01111001  y     Small y                      out_stream.put(121);
122  7A  01111010  z     Small z                      out_stream.put(122);
123  7B  01111011  {     Left curly bracket           out_stream.put(123);
124  7C  01111100  |     Unix pipe                    out_stream.put(124);
125  7D  01111101  }     Right curly bracket          out_stream.put(125);
126  7E  01111110  ~     Tilde                        out_stream.put(126);  or   out_stream << '~';   (32-126 ends here. Space to tilde.)
127  7F  01111111  DEL   Delete                       out_stream.put(127);
128  80  10000000                                     out_stream.put(128);  or   out_stream.put(-128);
129  81  10000001                                     out_stream.put(129);  or   out_stream.put(-127);
130  82  10000010                                     out_stream.put(130);  or   out_stream.put(-126);
131  83  10000011                                     out_stream.put(131);  or   out_stream.put(-125);
132  84  10000100                                     out_stream.put(132);  or   out_stream.put(-124);
133  85  10000101                                     out_stream.put(133);  or   out_stream.put(-123);
134  86  10000110                                     out_stream.put(134);  or   out_stream.put(-122);
135  87  10000111                                     out_stream.put(135);  or   out_stream.put(-121);
136  88  10001000                                     out_stream.put(136);  or   out_stream.put(-120);
137  89  10001001                                     out_stream.put(137);  or   out_stream.put(-119);
138  8A  10001010                                     out_stream.put(138);  or   out_stream.put(-118);
139  8B  10001011                                     out_stream.put(139);  or   out_stream.put(-117);
140  8C  10001100                                     out_stream.put(140);  or   out_stream.put(-116);
141  8D  10001101                                     out_stream.put(141);  or   out_stream.put(-115);
142  8E  10001110                                     out_stream.put(142);  or   out_stream.put(-114);
143  8F  10001111                                     out_stream.put(143);  or   out_stream.put(-113);
144  90  10010000                                     out_stream.put(144);  or   out_stream.put(-112);
145  91  10010001                                     out_stream.put(145);  or   out_stream.put(-111);
146  92  10010010                                     out_stream.put(146);  or   out_stream.put(-110);
147  93  10010011                                     out_stream.put(147);  or   out_stream.put(-109);
148  94  10010100                                     out_stream.put(148);  or   out_stream.put(-108);
149  95  10010101                                     out_stream.put(149);  or   out_stream.put(-107);
150  96  10010110                                     out_stream.put(150);  or   out_stream.put(-106);
151  97  10010111                                     out_stream.put(151);  or   out_stream.put(-105);
152  98  10011000                                     out_stream.put(152);  or   out_stream.put(-104);
153  99  10011001                                     out_stream.put(153);  or   out_stream.put(-103);
154  9A  10011010                                     out_stream.put(154);  or   out_stream.put(-102);
155  9B  10011011                                     out_stream.put(155);  or   out_stream.put(-101);
156  9C  10011100                                     out_stream.put(156);  or   out_stream.put(-100);
157  9D  10011101                                     out_stream.put(157);  or   out_stream.put(-99);
158  9E  10011110                                     out_stream.put(158);  or   out_stream.put(-98);
159  9F  10011111                                     out_stream.put(159);  or   out_stream.put(-97);
160  A0  10100000                                     out_stream.put(160);  or   out_stream.put(-96);
161  A1  10100001  ¡                                  out_stream.put(161);  or   out_stream.put(-95);
162  A2  10100010  ¢                                  out_stream.put(162);  or   out_stream.put(-94);
163  A3  10100011  £                                  out_stream.put(163);  or   out_stream.put(-93);
164  A4  10100100  ¤                                  out_stream.put(164);  or   out_stream.put(-92);
165  A5  10100101  ¥                                  out_stream.put(165);  or   out_stream.put(-91);
166  A6  10100110  ¦                                  out_stream.put(166);  or   out_stream.put(-90);
167  A7  10100111  §                                  out_stream.put(167);  or   out_stream.put(-89);
168  A8  10101000  ¨                                  out_stream.put(168);  or   out_stream.put(-88);
169  A9  10101001  ©                                  out_stream.put(169);  or   out_stream.put(-87);
170  AA  10101010  ª                                  out_stream.put(170);  or   out_stream.put(-86);
171  AB  10101011  «                                  out_stream.put(171);  or   out_stream.put(-85);
172  AC  10101100  ¬                                  out_stream.put(172);  or   out_stream.put(-84);
173  AD  10101101  ­                                   out_stream.put(173);  or   out_stream.put(-83);
174  AE  10101110  ®                                  out_stream.put(174);  or   out_stream.put(-82);
175  AF  10101111  ¯                                  out_stream.put(175);  or   out_stream.put(-81);
176  B0  10110000  °                                  out_stream.put(176);  or   out_stream.put(-80);
177  B1  10110001  ±                                  out_stream.put(177);  or   out_stream.put(-79);
178  B2  10110010  ²                                  out_stream.put(178);  or   out_stream.put(-78);
179  B3  10110011  ³                                  out_stream.put(179);  or   out_stream.put(-77);
180  B4  10110100  ´                                  out_stream.put(180);  or   out_stream.put(-76);
181  B5  10110101  µ                                  out_stream.put(181);  or   out_stream.put(-75);
182  B6  10110110  ¶                                  out_stream.put(182);  or   out_stream.put(-74);
183  B7  10110111  ·                                  out_stream.put(183);  or   out_stream.put(-73);
184  B8  10111000  ¸                                  out_stream.put(184);  or   out_stream.put(-72);
185  B9  10111001  ¹                                  out_stream.put(185);  or   out_stream.put(-71);
186  BA  10111010  º                                  out_stream.put(186);  or   out_stream.put(-70);
187  BB  10111011  »                                  out_stream.put(187);  or   out_stream.put(-69);
188  BC  10111100  ¼                                  out_stream.put(188);  or   out_stream.put(-68);
189  BD  10111101  ½                                  out_stream.put(189);  or   out_stream.put(-67);
190  BE  10111110  ¾                                  out_stream.put(190);  or   out_stream.put(-66);
191  BF  10111111  ¿                                  out_stream.put(191);  or   out_stream.put(-65);
192  C0  11000000  À                                  out_stream.put(192);  or   out_stream.put(-64);
193  C1  11000001  Á                                  out_stream.put(193);  or   out_stream.put(-63);
194  C2  11000010  Â                                  out_stream.put(194);  or   out_stream.put(-62);
195  C3  11000011  Ã                                  out_stream.put(195);  or   out_stream.put(-61);
196  C4  11000100  Ä                                  out_stream.put(196);  or   out_stream.put(-60);
197  C5  11000101  Å                                  out_stream.put(197);  or   out_stream.put(-59);
198  C6  11000110  Æ                                  out_stream.put(198);  or   out_stream.put(-58);
199  C7  11000111  Ç                                  out_stream.put(199);  or   out_stream.put(-57);
200  C8  11001000  È                                  out_stream.put(200);  or   out_stream.put(-56);
201  C9  11001001  É                                  out_stream.put(201);  or   out_stream.put(-55);
202  CA  11001010  Ê                                  out_stream.put(202);  or   out_stream.put(-54);
203  CB  11001011  Ë                                  out_stream.put(203);  or   out_stream.put(-53);
204  CC  11001100  Ì                                  out_stream.put(204);  or   out_stream.put(-52);
205  CD  11001101  Í                                  out_stream.put(205);  or   out_stream.put(-51);
206  CE  11001110  Î                                  out_stream.put(206);  or   out_stream.put(-50);
207  CF  11001111  Ï                                  out_stream.put(207);  or   out_stream.put(-49);
208  D0  11010000  Ð                                  out_stream.put(208);  or   out_stream.put(-48);
209  D1  11010001  Ñ                                  out_stream.put(209);  or   out_stream.put(-47);
210  D2  11010010  Ò                                  out_stream.put(210);  or   out_stream.put(-46);
211  D3  11010011  Ó                                  out_stream.put(211);  or   out_stream.put(-45);
212  D4  11010100  Ô                                  out_stream.put(212);  or   out_stream.put(-44);
213  D5  11010101  Õ                                  out_stream.put(213);  or   out_stream.put(-43);
214  D6  11010110  Ö                                  out_stream.put(214);  or   out_stream.put(-42);
215  D7  11010111  ×                                  out_stream.put(215);  or   out_stream.put(-41);
216  D8  11011000  Ø                                  out_stream.put(216);  or   out_stream.put(-40);
217  D9  11011001  Ù                                  out_stream.put(217);  or   out_stream.put(-39);
218  DA  11011010  Ú                                  out_stream.put(218);  or   out_stream.put(-38);
219  DB  11011011  Û                                  out_stream.put(219);  or   out_stream.put(-37);
220  DC  11011100  Ü                                  out_stream.put(220);  or   out_stream.put(-36);
221  DD  11011101  Ý                                  out_stream.put(221);  or   out_stream.put(-35);
222  DE  11011110  Þ                                  out_stream.put(222);  or   out_stream.put(-34);
223  DF  11011111  ß                                  out_stream.put(223);  or   out_stream.put(-33);
224  E0  11100000  à                                  out_stream.put(224);  or   out_stream.put(-32);
225  E1  11100001  á                                  out_stream.put(225);  or   out_stream.put(-31);
226  E2  11100010  â                                  out_stream.put(226);  or   out_stream.put(-30);
227  E3  11100011  ã                                  out_stream.put(227);  or   out_stream.put(-29);
228  E4  11100100  ä                                  out_stream.put(228);  or   out_stream.put(-28);
229  E5  11100101  å                                  out_stream.put(229);  or   out_stream.put(-27);
230  E6  11100110  æ                                  out_stream.put(230);  or   out_stream.put(-26);
231  E7  11100111  ç                                  out_stream.put(231);  or   out_stream.put(-25);
232  E8  11101000  è                                  out_stream.put(232);  or   out_stream.put(-24);
233  E9  11101001  é                                  out_stream.put(233);  or   out_stream.put(-23);
234  EA  11101010  ê                                  out_stream.put(234);  or   out_stream.put(-22);
235  EB  11101011  ë                                  out_stream.put(235);  or   out_stream.put(-21);
236  EC  11101100  ì                                  out_stream.put(236);  or   out_stream.put(-20);
237  ED  11101101  í                                  out_stream.put(237);  or   out_stream.put(-19);
238  EE  11101110  î                                  out_stream.put(238);  or   out_stream.put(-18);
239  EF  11101111  ï                                  out_stream.put(239);  or   out_stream.put(-17);
240  F0  11110000  ð                                  out_stream.put(240);  or   out_stream.put(-16);
241  F1  11110001  ñ                                  out_stream.put(241);  or   out_stream.put(-15);
242  F2  11110010  ò                                  out_stream.put(242);  or   out_stream.put(-14);
243  F3  11110011  ó                                  out_stream.put(243);  or   out_stream.put(-13);
244  F4  11110100  ô                                  out_stream.put(244);  or   out_stream.put(-12);
245  F5  11110101  õ                                  out_stream.put(245);  or   out_stream.put(-11);
246  F6  11110110  ö                                  out_stream.put(246);  or   out_stream.put(-10);
247  F7  11110111  ÷                                  out_stream.put(247);  or   out_stream.put(-9);
248  F8  11111000  ø                                  out_stream.put(248);  or   out_stream.put(-8);
249  F9  11111001  ù                                  out_stream.put(249);  or   out_stream.put(-7);
250  FA  11111010  ú                                  out_stream.put(250);  or   out_stream.put(-6);
251  FB  11111011  û                                  out_stream.put(251);  or   out_stream.put(-5);
252  FC  11111100  ü                                  out_stream.put(252);  or   out_stream.put(-4);
253  FD  11111101  ý                                  out_stream.put(253);  or   out_stream.put(-3);
254  FE  11111110  þ                                  out_stream.put(254);  or   out_stream.put(-2);
255  FF  11111111  ÿ                                  out_stream.put(255);  or   out_stream.put(-1);








#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                             Specs of variables                             ,#
#'                                                                            '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

______________________________________________________________________________________________________________________________________________________
char           -128 to
                127

                  0 to
                255                               (unsigned)                                256   total items for signed/unsigned.
______________________________________________________________________________________________________________________________________________________
short          -32,768 to
                32,767

                     0 to
                65,535                            (unsigned)                             65,536   total items for signed/unsigned. (256^2)
______________________________________________________________________________________________________________________________________________________
int            -2,147,483,648 to
                2,147,483,647

                            0 to
                4,294,967,295                     (unsigned)                      4,294,967,296   total items for signed/unsigned. (256^4)
______________________________________________________________________________________________________________________________________________________
long long      -9,223,372,036,854,775,807 to
                9,223,372,036,854,775,807

                                        0 to                         18,446,744,073,709,551,615   total items for signed.          (256^8 -1)
               18,446,744,073,709,551,615         (unsigned)         18,446,744,073,709,551,616   total items for unsigned.        (256^8)
______________________________________________________________________________________________________________________________________________________








#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                                Useful stuff                                ,#
#'                                                                            '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

SEARCH A FOLDER:                grep -rlF 'the word' /path

GET FILE SIZE IN BYTES:         unsigned long long size = std::filesystem::file_size(path);          Needs #include <filesystem>

CREATE FOLDER NO MATTER WHAT:   std::filesystem::create_directories("my_folder");                    Needs #include <filesystem>

DELETE FOLDER NO MATTER WHAT:   std::filesystem::remove_all("my_folder");                            Needs #include <filesystem>

RUN ANOTHER C++ PROGRAM:        system("/home/user/Desktop/Authorship");   //The executable made by Geany or with the g++ command (both produce the same file.)

TERMINAL OUTPUT TO FILE:        system("sha256sum my_file > hash_file");

CHANGE WORKING DIR:             chdir("/home/user/Desktop/my_folder");          Needs #include <unistd.h>

APPEND TO FILE:                 out_stream.open(path, std::ios::app);

DO NOT OPTIMIZE VARIABLE:       volatile int a;

INVISIBLE WHILE TYPING:         cout.setstate(ios::failbit); //Disables cout.
and:                            cout.clear();                //Restores cout.

CLEAR TERMINAL:                 std::cout << "\033[2J\033[3J\033[1;1H"; //Clears screen, erasing history.
and:                            std::cout << "\033[2J\033[1;1H";        //Clears screen, keeping history.

GET LIST OF ALL FILES AND
FOLDERS FROM A FOLDER:

	//Needs:
	//#include <algorithm>
	//#include <filesystem>
	//#include <fstream>
	//#include <string>
	//#include <vector>
	
	std::string path = "path_to_folder";
	
	//Gets list of ALL files & folders from a folder.
	std::vector <std::string>   file_list;
	std::vector <std::string> folder_list;
	for(const auto& entry : std::filesystem::recursive_directory_iterator(path))
	{	     if(entry.is_regular_file()) {  file_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of   files to RAM as relative paths.
		else if(entry.is_directory   ()) {folder_list.push_back(entry.path().lexically_relative(path).string());} //Loads list of folders to RAM as relative paths.
	}
	std::sort(  file_list.begin(),   file_list.end()); //Sorts list of   files in RAM.
	std::sort(folder_list.begin(), folder_list.end()); //Sorts list of folders in RAM.
	
	out_stream.open("list_of_files"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Writes list of files).\n"; return 1;} //Writes list of files.
	for(const auto& file_path : file_list) {out_stream << file_path << "\n";}
	out_stream.close();
	
	out_stream.open("list_of_folders"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Writes list of folders).\n"; return 1;} //Writes list of folders.
	for(const auto& file_path : folder_list) {out_stream << file_path << "\n";}
	out_stream.close();








#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                             Useful Linux tools                             ,#
#'                                                                            '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

actiona                  GUI  Tool to emulate human activity without programming or using suspected tools.)
amberol                  GUI  Minimalist yet beautiful music player.
artha                    GUI  Offline thesaurus & dictionary.
audacity                 GUI  Audio editor & sound recorder.
bleachbit                GUI  Wipe logs & what not.
geany                    GUI  Fast & lightweight IDE & text editor (if src tabs are cooked on ms-notepad, this is for you. Characters 13 & 10 are displayed as intended. That's \r\n.)
geany-plugin-automark    GUI  Global highlighting of what's selected or at cursor (Geany.)
geany-plugin-spellcheck  GUI  Grammar (Geany, overwrite hot-key to Ctrl+g to help remember: g for grammar.)
gparted                  GUI  GNU partition editor for formatting storage device without fail. (Create partition table before final formatting!)
gqrx-sdr                 GUI  Interface to software-defined radio dongles. Comes with gnuradio. Works for the RTL-SDR dongle.
inkscape                 GUI  Powerful vector graphics manipulation.
krita                    GUI  Advanced digital art creator.
lightdm-settings         GUI  Auto-login. Usage: in Control Center, open Login Window, go to Users, type in username in Username field, then restart.
mate-tweak               GUI  Remove home folder from desktop, disable folders that show up on desktop when USB stick is inserted.
mtpaint                  GUI  Alternative to the all-mighty inimitable Microsoft Paint of Windows 7. Although not intuitive, it is extremely powerful at file specs.
openshot-qt              GUI  Video editor and advanced frame dispenser.
qasmixer                 GUI  Allows volume-up for headphones on old laptops (set & forget, excellent quality audio.)
shotwell                 GUI  Image viewer+editor with edit options right on the home of each image.

exiv2                    CLI  Delete/modify/print image EXIF data. Commands: exiv2 print /path/to/file    exiv2 delete /path/to/file.
fswebcam                 CLI  Take pictures using USB-connected Android phone or USB-connected webcam or built-in webcam. (Command: fswebcam -q --no-banner a.jpg   Default capture is from built-in webcam or the only connected. If phone: swipe down & see webcam option in USB connection pop-up. To use USB-connected webcam if built-in exists: fswebcam -q --device /dev/video2 --no-banner a.jpg   And if really old webcam, it creates temporary file in /dev/v4l/by-id when plugged in, so use path to that file as source for your fswebcam command.   And if you want images converted to bmp (good for feeding models) use the mogrify command (comes from package imagemagick which should already be installed on Devuan/Debian): mogrify -format bmp a.jpg   (C++ FYI: running system("fswebcam -q --device /dev/video2 --no-banner a.jpg"); for example, creates the image in working directory, very good.) On a decent laptop, fswebcam can capture 1 image/s.)   (And for automated capture, see github.com/compromise-evident/WhatNot/blob/main/quick-security-camera.cpp)
g++                      CLI  GNU compiler for C++ (runs C++ in Geany, industry standard compiler. Install gcc if programming in C.) Command: g++ /path/to/file.
imagemagick              CLI  Convert images and all kinds of stuff. (Use "mogrify" or "convert path_to.bmp out.jpg".)
tesseract-ocr            CLI  Recognize text from image.  Use: tesseract image.jpg my_words   (To make it look for specific char hence improve accuracy & efficiency, use: tesseract image.png output.txt --tessedit_char_whitelist=0123456789RSTXYZ)
qrcode-terminal          CLI  Make & show qr in terminal. Use: qrcode-terminal 'my_text'
qrencode                 CLI  Make qr code.               Use: qrencode -o output.png "my text, no ! char."
zbar-tools               CLI  Read qr code.               Use: zbarimg image.png
xdg-open                 CLI  Open image.                 Use: xdg-open your_image_file.jpg && sleep 5 && pkill -f xdg-open   (Comes pre-installed.)
pkill                    CLI  Close image.                Use: pkill -f "eog your_image_file.jpg"                             (Comes pre-installed.)
xz-utils                 CLI  Compress/decompress .xz files (especially downloaded OS images for Raspberry Pi.) Command: xz -d -v /path/to/file.

libgmp-dev               LIB  GMP  - GNU Multiple Precision Arithmetic library.                                        Run it: "apt install g++ geany libgmp-dev".                       Open the .cpp in Geany. Append "-lgmp"  to Geany's compile & build commands.        Hit F9 once. F5 to run.     Don't forget to add "#include <gmp.h>"  in that .cpp file!
libmpfr-dev              LIB  MPFR - GNU Multiple Precision Floating point computations with correct Rounding library. Run it: "apt install g++ geany libmpfr-dev".                      Open the .cpp in Geany. Append "-lmpfr" to Geany's compile & build commands.        Hit F9 once. F5 to run.     Don't forget to add "#include <mpfr.h>" in that .cpp file!
python3-torch            LIB  PyTorch - Machine Learning library practical only in Python.                             Run it: "apt install geany python3-torch".                        Open the  .py in Geany. Replace "python" with "python3" in Geany's execute command.              F5 to run.     Don't forget to add "import torch", "import torch.nn as nn", "import torch.optim as optim" in that .py file!     (You don't need numpy. Some pkg managers don't set numpy as dep upon "apt install python3-torch", don't force your users to need more shit.)
tinygrad                 LIB  Nearly unrestricted Machine Learning library.                                            Run it: "apt install geany python3-pip", "pip3 install tinygrad". Open the  .py in Geany. Replace "python" with "python3" in Geany's execute command.              F5 to run.     imports in progress...

Commands:
apt-mark hold package_name     (stop updates to this package)
apt-mark unhold package_name   (undo above)
apt-mark showhold              (shows what's on hold)
chmod                          (change file/directory permissions such as that of an ext4 USB drive: chmod 777 /media/user/USB-drive-name)
dd                             (iso to thumbdrive) (dd if=/path.iso of=/dev/sdb) Use command lsblk to see names of devices, "sdb" is usially the thumbdrive name to put iso onto, else use what lsblk says it is.
dmesg --notime -wd             (list USB device info live - as root only)
g++                            (create executable from .cpp) (g++ path_to.cpp   or hit F9 in Geany.)
grep                           (search files) use: grep -rin "my_keyword" /path/to/folder_or_file
lsblk                          (list block devices) (do lsblk -f to see names)
passwd                         (change passwd for user)
passwd root                    (change passwd for root)
sudo dmidecode -t memory       (list computer specs as root)   options: bios, system, baseboard, chassis, processor, memory, cache, connector, slot,     sudo dmidecode -s system-product-name

Commands for C++. For terminal: use what's quoted:
Record as raw audio for 7 seconds using sox:        system("rec -r 44100 -c 2 -b 8 -e unsigned-integer -t raw temp/recorded.raw trim 0 7");
Convert raw audio (any file) to .wav using sox:     system("sox -r 44100 -e unsigned -b 8 -c 1 my_file.raw -t wav out_file.wav");
Get length of .wav file in seconds using sox:       system("sox my_audio.wav -n stat 2>&1 | grep 'Length' > seconds.txt");
Play audio file through vlc then close vlc:         system("vlc my_audio.wav --play-and-exit 2>/dev/null &");
Set system volume using pre-installed ALSA:         system("amixer -q set Master 75%");








#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                                Laptop setup                                ,#
#'                                                                            '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

Devuan, MATE
apt install amberol g++ geany geany-plugin-automark geany-plugin-spellcheck gparted lightdm-settings mate-tweak shotwell
If Apple: cut speaker wires to eliminate chime ad, cut keyboard backlight cable, sand F9 & F5, physically swap keyboard keys "fn" and "left Ctrl", then do as root:
    echo "options hid_apple swap_fn_leftctrl=1 fnmode=2" > /etc/modprobe.d/hid_apple.conf
    sudo update-initramfs -u -k all








#########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*##########
#####'`                                                                  `'#####
###'                                                                        '###
##                                                                            ##
#,                              Programming style                             ,#
#'                                                                            '#
##                                                                            ##
###,                                                                        ,###
#####,.                                                                  .,#####
##########*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#########

 1. Security, not convenience.
 2. Overkill security.
 3. Single C++ files.
 4. Original C++ files.
 5. Everything in main().
 6. No functions or OOP.
 7. No "using namespace std".
 8. No system() calls in big tools.
 9. Everything under the Unlicense.
10. Everything minimalist.
11. Type-casting: (type)var;
12. Check failure for file i/o:

in_stream.open("file"); if(!in_stream) {std::cout << "\nCan't open file for reading. (Say for what here).\n"; return 1;}
out_stream.open("file"); if(!out_stream) {std::cout << "\nCan't open file for writing. (Say for what here).\n"; return 1;}
for(; in_stream.get(file_byte);)
or if(!in_stream.get(file_byte)) {return 0; or break;} //READS A BYTE TO THEN USE. Exits if eof/error.
in_stream.close();
out_stream.close();

FAQ
Big tech feels insecure about publishing their code, what makes you different?
Independent verification means those who excel in domains you do not--can show
you flaws privately, before those flaws are used by someone anonymous. Authors
of proprietary software are either claiming they alone excel in all domains,
or have malicious features implemented willingly or against their will.

Do you accept code contributions?
Not a single line, not a single character. That would be a security hole
waiting for trouble. Just tell me what I got wrong and I'll fix it.

*/
