//Raw unoptimized SHA-256. No lib required.

#include <iostream>
#include <string>
int main()
{	std::string SHA_256_input = "abc";
	std::string SHA_256_output;
	
	
	
	
	
	{SHA_256_output = ""; /*The following code can go here to make a 1-liner that is copy-pastable & loopable.*/}
	
	//Copies input.
	std::string msg = SHA_256_input;
	
	//Fudge.
	unsigned int H[8] =
	{	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
	};
	
	const unsigned int K[64] =
	{	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};
	
	//Pads input.
	unsigned long long bit_len = (unsigned long long)msg.length() * 8;
	msg.push_back((char)0x80);                                                        //Appends a '1' bit (0x80 byte).
	for(; (msg.length() % 64) != 56;) {msg.push_back((char)0x00);}                    //Appends 0x00 bytes until (message length mod 64) = 56 bytes.
	for(int a = 7; a >= 0; a--) {msg.push_back((char)((bit_len >> (a * 8)) & 0xFF));} //Appends original length as 8-byte big-endian integer.
	
	//Processes each 64-byte chunk.
	for(unsigned long long block_offset = 0; block_offset < msg.length(); block_offset += 64)
	{	unsigned int W[64];
		
		//Breaks 64-byte block into sixteen 32-bit big-endian words.
		for(int t = 0; t < 16; t++)
		{	W[t] = ((unsigned char)msg[block_offset + t * 4 + 0] << 24) |
			       ((unsigned char)msg[block_offset + t * 4 + 1] << 16) |
			       ((unsigned char)msg[block_offset + t * 4 + 2] <<  8) |
			       ((unsigned char)msg[block_offset + t * 4 + 3]);
		}
		
		//Expands 16 words into 64 words (Inlined sigma0 and sigma1).
		for(int t = 16; t < 64; t++)
		{	unsigned int x1 = W[t - 2];
			unsigned int s1 = ((x1 >> 17) | (x1 << 15)) ^ ((x1 >> 19) | (x1 << 13)) ^ (x1 >> 10);
			unsigned int x0 = W[t - 15];
			unsigned int s0 = ((x0 >> 7) | (x0 << 25)) ^ ((x0 >> 18) | (x0 << 14)) ^ (x0 >> 3);
			W[t] = s1 + W[t - 7] + s0 + W[t - 16];
		}
		
		//Initializes working variables.
		unsigned int a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
		
		//Compresses (inlined sigma0, sigma1, choose, majority).
		for(int t = 0; t < 64; t++)
		{	unsigned int S1  = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
			unsigned int ch  = (e & f) ^ (~e & g);
			unsigned int T1  = h + S1 + ch + K[t] + W[t];
			unsigned int S0  = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
			unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
			unsigned int T2  = S0 + maj;
			
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}
		
		//Merges block variables back into global state.
		H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;
	}
	
	//Converts hash to string.
	const char symbols[] = "0123456789abcdef";
	for(int a = 0; a < 8; a++)
	{	for(int b = 7; b >= 0; b--)
		{	int nibble = (H[a] >> (b * 4)) & 0xF;
			SHA_256_output += symbols[nibble];
		}
	}
	
	
	
	
	
	std::cout << SHA_256_output;
	
	if(SHA_256_output == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad") {std::cout << "\n\nVERIFIED\n\n";}
}
