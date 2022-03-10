#include <iostream>
#include <fstream>
#include <string.h>
#include "library.hpp"

using namespace std;

void print_data(ofstream& out, int sid, string str)
{
	out << sid << '\t' << str << endl;
	return;
}

bool readInputParameter(int argc, char *argv[], inputParameter* input)
{
	int argnr = 0;
	const char *defaultInput = "../FASTA";
	const char *defaultData = "../data";
	const char *defaultOutput = "../result";

	input->inputPath = (char *)defaultInput;
	input->dataPath = (char *)defaultData;
	input->outputPath = (char *)defaultOutput;

	while (++argnr < argc) {
		if (!strcmp(argv[argnr], "-i")) {
			input->inputPath = argv[++argnr];
		}
		else if (!strcmp(argv[argnr], "-d")) {
			input->dataPath = argv[++argnr];
		}
		else if (!strcmp(argv[argnr], "-o")) {
			input->outputPath = argv[++argnr];
		}
		else{
			cout << "-i <input FASTA sequence path (default: ../FASTA)>" << endl;
			cout << "-o <final output path (default: ../data)>" << endl;
			cout << "-d <intermediate data path (default: ../result)>" << endl;
			cout << "-h (or others) <help message>" << endl;
			return false;
		}
	}
	input->printInputParameter();
	return true;
}
