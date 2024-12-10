#include <iostream>
#include <fstream>

int main()
{
	 {
		/*
		std::ofstream ostream;

		ostream.open("TestFile2.txt");

		ostream.write("AA", 2);

		char Text[32] = {};
		strcpy_s(Text, "¹®ÀÚ¿­");

		ostream.write(Text, strlen(Text));

		ostream.close();
	*/}
	 std::ifstream istream;
	 istream.open("TestFile2.txt");
	 
	 if (istream.is_open())
	 {
		 while (!istream.eof())
		 {
			 char Line[32] = {};

			 istream.getline(Line, 32);
		 }

		 istream.close();
	 }

	return 0;
}