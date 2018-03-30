int main(int argc, char* argv[])
{
	int i = 0xffff0000;
		if ( ((char*)&i)[0] == 0)
			printf("LE\n");
		else
			printf("BE\n");
	return 0;
}