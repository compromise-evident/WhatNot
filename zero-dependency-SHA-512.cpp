//Raw unoptimized SHA-512. No lib required.                                     Run it: "apt install g++ geany". Open the .cpp in Geany. Hit F9 once. F5 to run.
//To compare, do "sha512sum /your/file"

#include <iostream>
#include <string>
int main()
{	std::string SHA_512_input = "abc"; //Can be any file too.
	std::string SHA_512_output;
	
	
	
	
	
	{SHA_512_output = ""; /*The following code can go here to make a 1-liner that is copy-pastable & loopable.*/}
	
	//Copies input.
	std::string msg = SHA_512_input;
	
	//Fudge.
	unsigned long long H[8] =
	{	0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL, 0xa54ff53a5f1d36f1ULL,
		0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL, 0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL
	};
	
	const unsigned long long K[80] =
	{	0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL,
		0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL,
		0xd807aa98a3030242ULL, 0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
		0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL, 0xc19bf174cf692694ULL,
		0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
		0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
		0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL,
		0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL, 0x06ca6351e003826fULL, 0x142929670a0e6e70ULL,
		0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
		0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
		0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL,
		0xd192e819d6ef5218ULL, 0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
		0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL,
		0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL,
		0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
		0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL,
		0xca273eceea26619cULL, 0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL,
		0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
		0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL, 0x431d67c49c100d4cULL,
		0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
	};
	
	//Pads input.
	//Your input is processed 128 bytes at-a-time, first-to-last. So bytes are appended to your input, until it's a multiple of 128.
	//However, 17 bytes are appended regardless. If you want the least amount of bytes to be appended to your input,
	//make sure your input length is a multiple of 128, minus 17. Then 17 bytes will be appended, no more, no less.
	unsigned long long orig_len_bits = msg.length() * 8ULL;
	msg.push_back((char)0x80);                                         //Appends a '1' bit (0x80 byte).
	for(; (msg.length() % 128) != 112;) {msg.push_back((char)0x00);}   //Appends 0x00 bytes until (message length mod 128) = 112 bytes.
	msg.append(8, (char)0x00);                                         //Appends the 1st 8 bytes of the 128-bit length block (all zeros).
	for(int a = 0; a < 8; a++)                                         //Appends the final 8 bytes containing the original message length in bits.
	{	msg.push_back((char)((orig_len_bits >> (56 - a * 8)) & 0xFF));
	}
	
	//Processes each 128-byte chunk.
	for(unsigned long long offset = 0; offset < msg.length(); offset += 128)
	{	unsigned long long W[80];
		
		//Prepares the message schedule (Convert 128 byte chunk into 16 64-bit words).
		for(int i = 0; i < 16; i++)
		{	unsigned long long p = offset + (i * 8);
			W[i] = ((unsigned long long)(unsigned char)msg[p + 0] << 56) |
			       ((unsigned long long)(unsigned char)msg[p + 1] << 48) |
			       ((unsigned long long)(unsigned char)msg[p + 2] << 40) |
			       ((unsigned long long)(unsigned char)msg[p + 3] << 32) |
			       ((unsigned long long)(unsigned char)msg[p + 4] << 24) |
			       ((unsigned long long)(unsigned char)msg[p + 5] << 16) |
			       ((unsigned long long)(unsigned char)msg[p + 6] <<  8) |
			       ((unsigned long long)(unsigned char)msg[p + 7]);
		}
		
		//Extends the 16 words into 80 words.
		for(int i = 16; i < 80; i++)
		{	unsigned long long x0 = W[i - 15];
			unsigned long long s0 = ((x0 >> 1) | (x0 << 63)) ^ ((x0 >> 8) | (x0 << 56)) ^ (x0 >> 7);
			unsigned long long x1 = W[i - 2];
			unsigned long long s1 = ((x1 >> 19) | (x1 << 45)) ^ ((x1 >> 61) | (x1 << 3)) ^ (x1 >> 6);
			W[i] = s1 + W[i - 7] + s0 + W[i - 16];
		}
		
		//Initializes working variables with current hash value.
		unsigned long long a = H[0], b = H[1], c = H[2], d = H[3], e = H[4], f = H[5], g = H[6], h = H[7];
		
		//Compresses.
		for(int i = 0; i < 80; i++)
		{	unsigned long long bs1 = ((e >> 14) | (e << 50)) ^ ((e >> 18) | (e << 46)) ^ ((e >> 41) | (e << 23));
			unsigned long long ch  = (e & f) ^ (~e & g);
			unsigned long long T1  = h + bs1 + ch + K[i] + W[i];
			unsigned long long bs0 = ((a >> 28) | (a << 36)) ^ ((a >> 34) | (a << 30)) ^ ((a >> 39) | (a << 25));
			unsigned long long maj = (a & b) ^ (a & c) ^ (b & c);
			unsigned long long T2  = bs0 + maj;
			
			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}
		
		//Adds accumulated total hash.
		H[0] += a; H[1] += b; H[2] += c; H[3] += d; H[4] += e; H[5] += f; H[6] += g; H[7] += h;
	}
	
	//Converts hash to string.
	const char symbols[] = "0123456789abcdef";
	for(int a = 0; a < 8; a++)
	{	for(int b = 15; b >= 0; b--)
		{	int nibble = (H[a] >> (b * 4)) & 0xF;
			SHA_512_output += symbols[nibble];
		}
	}
	
	
	
	
	
	std::cout << SHA_512_output;
	
	if(SHA_512_output == "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f") {std::cout << "\n\nVERIFIED\n\n";}
}
