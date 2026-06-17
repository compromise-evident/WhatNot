//Raw unoptimized SHA3-256. No lib required.                                    Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
//To compare, do "openssl dgst -sha3-256 /your/file"

#include <iostream>
#include <string>
int main()
{	std::string SHA3_256_input = "abc"; //Can be any file too.
	std::string SHA3_256_output;
	
	
	
	
	
	{SHA3_256_output = ""; /*The following code can go here to make a 1-liner that is copy-pastable & loopable.*/}
	
	//Copies input.
	std::string msg = SHA3_256_input;
	
	//Fudge.
	unsigned long long state[25] = {0};
	
	const unsigned long long RC[24] =
	{	0x0000000000000001ULL, 0x0000000000008082ULL, 0x800000000000808aULL, 0x8000000080008000ULL, 0x000000000000808bULL, 0x0000000080000001ULL,
		0x8000000080008081ULL, 0x8000000000008009ULL, 0x000000000000008aULL, 0x0000000000000088ULL, 0x0000000080008009ULL, 0x000000008000000aULL,
		0x000000008000808bULL, 0x800000000000008bULL, 0x8000000000008089ULL, 0x8000000000008003ULL, 0x8000000000008002ULL, 0x8000000000000080ULL,
		0x000000000000800aULL, 0x800000008000000aULL, 0x8000000080008081ULL, 0x8000000000008080ULL, 0x0000000080000001ULL, 0x8000000080008008ULL
	};
	
	const int r[25] = {0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43, 25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14};
	
	//Pads input.
	//Your input is processed 136 bytes at-a-time, first-to-last. So bytes are appended to your input, until it's a multiple of 136.
	//However, 2 bytes are appended regardless. If you want the least amount of bytes to be appended to your input,
	//make sure your input length is a multiple of 136, minus 2. Then 2 bytes will be appended, no more, no less.
	msg.push_back(0x06);
	for(; (msg.length() % 136) != 135;) {msg.push_back(0x00);} //Appends 0x00 bytes until (message length mod 136) = 135 bytes.
	msg.push_back(0x80);
	
	//Processes each 136-byte chunk.
	for(unsigned long long block_offset = 0; block_offset < msg.length(); block_offset += 136)
	{	//XOR the 136-byte block into the state.
		for(int i = 0; i < 17; i++)
		{	unsigned long long word = 0;
			for(int j = 0; j < 8; j++)
			{	unsigned long long idx = block_offset + (i * 8 + j);
				word |= (unsigned long long)(unsigned char)msg[idx] << (j * 8);
			}
			state[i] ^= word;
		}
		
		//Keccak-f[1600] permutation.
		for(int round = 0; round < 24; round++)
		{	//Theta.
			unsigned long long C[5], D[5];
			for(int x = 0; x < 5; x++) {C[x] = state[x] ^ state[x + 5] ^ state[x + 10] ^ state[x + 15] ^ state[x + 20];}
			for(int x = 0; x < 5; x++) {D[x] = C[(x + 4) % 5] ^ ((C[(x + 1) % 5] << 1) | (C[(x + 1) % 5] >> 63));}
			for(int x = 0; x < 5; x++)
			{	for(int y = 0; y < 5; y++) {state[x + y * 5] ^= D[x];}
			}
			
			//Rho & Pi.
			unsigned long long next_state[25];
			for(int x = 0; x < 5; x++)
			{	for(int y = 0; y < 5; y++)
				{	int idx = x + y * 5;
					unsigned long long rot = (state[idx] << r[idx]) | (state[idx] >> (64 - r[idx]));
					next_state[y + ((2 * x + 3 * y) % 5) * 5] = rot;
				}
			}
			
			//Chi.
			for(int y = 0; y < 5; y++)
			{	for(int x = 0; x < 5; x++)
				{	state[x + y * 5] = next_state[x + y * 5] ^ ((~next_state[(x + 1) % 5 + y * 5]) & next_state[(x + 2) % 5 + y * 5]);
				}
			}
			
			//Iota.
			state[0] ^= RC[round];
		}
	}
	
	//Converts hash to string.
	const char symbols[] = "0123456789abcdef";
	for(int a = 0; a < 4; a++)
	{	for(int b = 0; b < 8; b++)
		{	int byte_val = (state[a] >> (b * 8)) & 0xFF;
			SHA3_256_output += symbols[(byte_val >> 4) & 0x0F];
			SHA3_256_output += symbols[byte_val & 0x0F];
		}
	}
	
	
	
	
	
	std::cout << SHA3_256_output;
	
	if(SHA3_256_output == "3a985da74fe225b2045c172d6bd390bd855f086e3e9d525b46bfe24511431532") {std::cout << "\n\nVERIFIED\n\n";}
}
