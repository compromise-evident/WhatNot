int main()
{	for(int chain[27]= {0}; chain[0] != 4; chain[26]++)
	{	for(int a = 26; chain[a] == 10; a--) {chain[a] = 0; chain[a - 1]++;}
	}
}
