#include <iostream>
#include "1_gen_host_sequence.hpp"
#include "2_gen_virus_sequence.hpp"
#include "3_gen_result.hpp"
#include "library.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	inputParameter *input = new inputParameter();
	
	if (readInputParameter(argc, argv, input) == false) {
		return -1;
	}

	cout << "Start program..." << endl;
	cout << "Host gene sequence parsing...";
	int num_host_seq = gen_host_seq(input);
	cout << "end." << endl;
	cout << num_host_seq << " host sequence(s) found." << endl;
	cout << "Virus gene sequence parsing...";
	gen_virus_seq(num_host_seq, input);
	cout << "end" << endl;
	cout << "Generating resultant files..." << endl;
	gen_result(num_host_seq, input);
	cout << "All progress finished! Thank you." << endl;
	return 0;
}
