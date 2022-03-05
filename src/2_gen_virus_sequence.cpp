#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "library.h"

using namespace std;

void parse_organism_virus(int num_host_seq)
{
	string path = "../FASTA/virus.fasta";

	ifstream in(path);
	ofstream out("../data/virus_annotation.txt");
	ofstream out2("../data/virus_tid_sequence.txt");
	ofstream out3("../data/virus_sid_sequence.txt");

	int cur_cid = 0;
	int cur_cid_rem = 0;
	string tmp, str;
	map<string, bool> string_total;

	while (getline(in, tmp)) {
		if (tmp.find('>') != string::npos) {
			out << tmp << endl;
			if (cur_cid != 0) {
				print_data(out2, cur_cid + num_host_seq, str);
				if (string_total.find(str) == string_total.end()) {
					print_data(out3, cur_cid_rem + num_host_seq, str);
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
	print_data(out2, cur_cid + num_host_seq, str);
	if (string_total.find(str) == string_total.end()) {
		print_data(out3, cur_cid_rem + num_host_seq, str);
		cur_cid_rem++;
		string_total[str] = true;
	}
	in.close();
	return;
}

void gen_virus_seq(int num_host_seq)
{
	parse_organism_virus(num_host_seq);

	return;

}
