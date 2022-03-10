#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "library.hpp"

using namespace std;

int parse_organism_host(inputParameter *input)
{
	string inputPath(input->inputPath);
	string dataPath(input->dataPath);
	string outputPath(input->outputPath);

	// string path = "../FASTA/host.fasta";
	string path = inputPath + "/host.fasta";

	ifstream in(path);
	/*
	ofstream out("../result/host_annotation.txt");	// about tid
	ofstream out2("../data/host_tid_sequence.txt");
	ofstream out3("../result/host_sid_sequence.txt");
	*/
	ofstream out(outputPath + "/host_annotation.txt");
	ofstream out2(dataPath + "/host_tid_sequence.txt");
	ofstream out3(outputPath + "/host_sid_sequence.txt");

	int cur_cid = 0;
	int cur_cid_rem = 1;
	string tmp, str;
	map<string, bool> string_total;

	while (getline(in, tmp)) {
		if (tmp.find('>') != string::npos) {
			out << tmp << endl;
			if (cur_cid != 0) {
				print_data(out2, cur_cid, str);
				if (string_total.find(str) == string_total.end()) {
					print_data(out3, cur_cid_rem, str);
					cur_cid_rem++;
					string_total[str] = true;
				}
			}
			cur_cid++;
			str.clear();
			continue;
		}
		str += tmp;
	}
	print_data(out2, cur_cid, str);
	if (string_total.find(str) == string_total.end()) {
		print_data(out3, cur_cid_rem, str);
		cur_cid_rem++;
		string_total[str] = true;
	}
	in.close();
	return cur_cid_rem - 1;	// number of sid
}

int gen_host_seq(inputParameter *input)
{
	int host_seq = parse_organism_host(input);

	return host_seq;
}
