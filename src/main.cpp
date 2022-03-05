#include <iostream>
#include "1_gen_host_sequence.h"
#include "2_gen_virus_sequence.h"
#include "3_gen_result.h"

using namespace std;

int main()
{
	cout << "Start program..." << endl;
	cout << "Host gene sequence parsing...";
	int num_host_seq = gen_host_seq();
	cout << "end." << endl;
	cout << num_host_seq << " host sequence(s) found." << endl;
	cout << "Virus gene sequence parsing...";
	gen_virus_seq(num_host_seq);
	cout << "end" << endl;
	cout << "Generating resultant files..." << endl;
	gen_result(num_host_seq);
	cout << "All progress finished! Thank you." << endl;
	return 0;
}
