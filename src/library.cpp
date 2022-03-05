#include <iostream>
#include <fstream>

using namespace std;

void print_data(ofstream& out, int sid, string str)
{
	out << sid << '\t' << str << endl;
	return;
}
