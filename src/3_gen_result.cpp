#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include "3_gen_result.hpp"

using namespace std;

string seq[100000];
string vidcds_seq[50000];

// parsing accession number from the annotation line
string get_acc(string tmp)
{
	string str;

	tmp = tmp.substr(0, tmp.find("|"));
	if (tmp.find("(") != string::npos) {
		str = tmp.substr(tmp.find("(") + 1, tmp.size());
		tmp = str;
	}
	if (tmp.find(">") != string::npos) {
		str = tmp.substr(1, tmp.size());
		tmp = str;
	}
	if (tmp.find("(") != string::npos) {
		str = tmp.substr(tmp.find("(") + 1, tmp.size());
	}

	return str;
}

// at the position n
string get_virus(string tmp)
{
	string str;
	int i;

	i = tmp.find('[');
	str = tmp.substr(i + 1, tmp.find("]|") - i - 1);
	return str;
}

string get_cds(string tmp)
{
	string str;

	str = tmp.substr(tmp.find('|') + 1, tmp.size());
	str = str.substr(0, str.find('[') - 1);
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

void gen_result(int num_host_seq, inputParameter *input)
{
        string inputPath(input->inputPath);
        string dataPath(input->dataPath);
        string outputPath(input->outputPath);

	string cur_org;
	string str, tmp, tmp2;
	int cur_tid;
	int i;

	bool sid_tids_gen = true;
	bool tid_vid_gen = true;
	bool sid_vids_total_gen = true;
	bool sort_by_vidcds = true;
	bool aid_gen = true;

	if (sid_tids_gen)
	{
		ifstream in3(dataPath + "/virus_tid_sequence.txt");
		ifstream in4(dataPath + "/virus_sid_sequence.txt");
		ifstream in5(dataPath + "/virus_annotation.txt");

		ofstream out4(dataPath + "/virus_sid_tids.txt");
		ofstream out5(dataPath + "/virus_annotation_sid.txt");
		ofstream out6(dataPath + "/virus_tid_acc.txt");
		ofstream out7(dataPath + "/virus_sid_accs.txt");

		map<string, int> seq;		// unique sequence / sid
		map<int, string> anno;
		map<int, string> sid_tids;	// sid / tids
		map<int, string> tid_acc;	// accession number of the tid
		map<int, string> sid_accs;	// accession numbers of the sid

		// generation of cid_rem_cids
		
		cur_tid = num_host_seq;
		while (getline(in4, tmp)) {
			cur_tid++;
			seq[tmp.substr(tmp.find('\t') + 1)] = cur_tid;
			if (cur_tid % 1000 == 0) {
				cout << "finding sid: current tid: " << cur_tid << endl;
			}
		}
		in4.close();
		cur_tid = num_host_seq;
		while (getline(in5, tmp)) {
			cur_tid++;
			anno[cur_tid] = tmp;
			tid_acc[cur_tid] = get_acc(tmp);
			out6 << cur_tid << "\t" << tid_acc[cur_tid] << endl;
		}
		out6.close();
		in5.close();

		cout << "get sid end" << endl;
		cur_tid = num_host_seq;
		while (getline(in3, tmp)) {
			cur_tid++;
			str = tmp.substr(tmp.find('\t') + 1);
			if (seq.count(str) > 0) {
				if (sid_tids.count(seq[str]) == 0) {
					sid_tids[seq[str]] = to_string(cur_tid);
					sid_accs[seq[str]] = tid_acc[cur_tid];
					out5 << anno[cur_tid] << endl;
				}
				else {
					sid_tids[seq[str]] += string("-") + to_string(cur_tid);
					sid_accs[seq[str]] += string("-") + tid_acc[cur_tid];
				}
			}
			else {
				cout << "error occur in" << cur_tid << endl;
			}
			if (cur_tid % 5000 == 0) {
				cout << "finding cids: current tid: " << cur_tid << endl;
			}
		}
		in3.close();
		for (i = num_host_seq + 1; i < num_host_seq + 1 + seq.size(); i++) {
			out4 << i << "\t" << sid_tids[i] << endl;
			out7 << i << "\t" << sid_accs[i] << endl;
		}
		out4.close();
	}

	map<int, int> tid_vid;
	map<string, int> virus_vid;
	map<int, int> tid_vidcds;
	map<string, int> viruscds_vtid;

	// tid가 각각 어느 vid에 배정되는지
	if (tid_vid_gen)
	{
		ifstream in(dataPath + "/virus_annotation.txt");

		ofstream out(dataPath + "/virus_virus_oid.txt");
		ofstream out2(dataPath + "/virus_viruscds_cid.txt"); // "virus=cds" with cid (CDS id). original: virus_vidcds

		int cur_tid = num_host_seq;
		int cur_vid = 0;
		int cur_vidcds = 0;
		string virus;
		string cds;
		int vidcds_2[10000];

		while (getline(in, tmp)) {
			cur_tid++;
			virus = get_virus(tmp);
			cds = virus + "=" + get_cds(tmp);
			if (virus_vid.count(virus) == 0) {
				cur_vid++;
				virus_vid[virus] = cur_vid;
				tid_vid[cur_tid] = cur_vid;
			}
			else {
				tid_vid[cur_tid] = virus_vid[virus];
			}
			if (viruscds_vtid.count(cds) == 0) {
				cur_vidcds++;
				viruscds_vtid[cds] = cur_vidcds;
				tid_vidcds[cur_tid] = cur_vidcds;
			}
			else {
				tid_vidcds[cur_tid] = viruscds_vtid[cds];
			}
		}

		map<string, int>::iterator it;
		for (it = virus_vid.begin(); it != virus_vid.end(); it++) {
			out << it->first << "\t" << it->second << endl;
		}
		cur_vidcds = 0;
		for (it = viruscds_vtid.begin(); it != viruscds_vtid.end(); it++) {
			cur_vidcds++;
			vidcds_2[it->second] = cur_vidcds;
			it->second = cur_vidcds;
			out2 << it->first << "\t" << it->second << endl;
		}
		map<int, int>::iterator it2;
		for (it2 = tid_vidcds.begin(); it2 != tid_vidcds.end(); it2++) {
			tid_vidcds[it2->first] = vidcds_2[it2->second];
		}
		in.close();
		out.close();
		out2.close();
	}
	
	// generation of cid_rem_vids
	if (sid_vids_total_gen)
	{
		ifstream in(dataPath + "/virus_sid_tids.txt");

		ofstream out(dataPath + "/virus_sid_oids.txt");
		ofstream out2(dataPath + "/virus_oid_sid.txt");
		ofstream out3(dataPath + "/virus_sid_cids.txt");
		ofstream out4(dataPath + "/virus_cid_sid.txt");

		string num;
		string tid_vids;
		string tid_vidcdss;
		map<int, string> vid_tids;
		map<int, string> vidcds_tids;
		bool virus_check[3000] = { 0 };
		map<int, bool> viruscds_check;

		cur_tid = num_host_seq;
		while (getline(in, tmp)) {
			tid_vids.clear();
			tid_vidcdss.clear();
			cur_tid++;
			str = tmp.substr(tmp.find("\t") + 1, tmp.size());
			num.clear();

			for (i = 0; i < str.size(); i++) {
				if (str.at(i) == '-') {
					virus_check[tid_vid[stoi(num)]] = 1;
					viruscds_check[tid_vidcds[stoi(num)]] = true;
					num.clear();
				}
				else {
					num += str.at(i);
				}
			}
			virus_check[tid_vid[stoi(num)]] = 1;
			viruscds_check[tid_vidcds[stoi(num)]] = true;

			for (i = 0; i < 3000; i++) {
				if (virus_check[i] == 1) {
					virus_check[i] = 0;
					tid_vids += string("-") + to_string(i);
					vid_tids[i] += string("-") + to_string(cur_tid);
				}
			}
			out << cur_tid << "\t" << tid_vids.substr(1) << endl;

			map<int, bool>::iterator it;
			for (it = viruscds_check.begin(); it != viruscds_check.end(); it++) {
				if (it->second == true) {
					it->second = false;
					tid_vidcdss += string("-") + to_string(it->first);
					vidcds_tids[it->first] += string("-") + to_string(cur_tid);
				}
			}
			out3 << cur_tid << "\t" << tid_vidcdss.substr(1) << endl;

		}
		map<int, string>::iterator it;
		for (it = vid_tids.begin(); it != vid_tids.end(); it++) {
			out2 << it->first << "\t" << it->second.substr(1) << endl;
		}
		map<int, string>::iterator it2;
		for (it2 = vidcds_tids.begin(); it2 != vidcds_tids.end(); it2++) {
			out4 << it2->first << "\t" << it2->second.substr(1) << endl;
		}

		in.close();
		out.close();
		out2.close();
	}

	if (sort_by_vidcds)
	{
		cout << "sort by vidcds start" << endl;

		ifstream in(dataPath + "/virus_sid_sequence.txt");
		ifstream in2(dataPath + "/virus_cid_sid.txt");
		ifstream in3(dataPath + "/virus_annotation_sid.txt");
		ifstream in4(dataPath + "/virus_viruscds_cid.txt");

		ofstream out(outputPath + "/virus_sort_tid_seq.txt");
		ofstream out2(dataPath + "/virus_sort_tid_cid.txt");
		ofstream out3(outputPath + "/virus_sort_annotation_sid.txt");

		int cur_tid, cur_vidcds;
		string tmp, str;
		int tid_vtid_mapping[43000];
		map<int, string> anno_org, anno_sort;
		map<int, string> vidcds_virus;

		cur_tid = 0;
		while (getline(in, tmp)) {
			seq[cur_tid] = tmp.substr(tmp.find("\t") + 1);
			cur_tid++;
		}
		in.close();
		cout << "store seq end" << endl;
		cur_tid = 0;
		while (getline(in3, tmp)) {
			anno_org[cur_tid] = tmp;
			cur_tid++;
		}
		in3.close();
		cout << "store annotation end" << endl;
		cur_tid = num_host_seq;
		cur_vidcds = 0;
		int num;
		int xxx = 0;

		while (getline(in4, tmp)) {
			str = tmp.substr(0, tmp.find("\t"));	// virus name
			tmp.erase(0, tmp.find("\t") + 1);	// num
			vidcds_virus[stoi(tmp)] = str;
		}

		while (getline(in2, tmp)) {
			cur_vidcds++;
			tmp = tmp.substr(tmp.find("\t") + 1);
			tmp += "-";
			while (tmp.find("-") != string::npos) {
				cur_tid++;
				num = stoi(tmp.substr(0, tmp.find("-")));
				vidcds_seq[cur_vidcds] += seq[num - (num_host_seq + 1)] + "-";
				anno_sort[xxx] = anno_org[num - (num_host_seq + 1)];
				tid_vtid_mapping[xxx] = cur_vidcds;
				xxx++;
				tmp = tmp.substr(tmp.find("-") + 1);
			}
		}
		in2.close();
		cout << "print start" << endl;
		int i;
		cur_tid = num_host_seq;
		for (i = 1; i <= cur_vidcds; i++) {
			tmp = vidcds_seq[i];
			while (tmp.find("-") != string::npos) {
				str = tmp.substr(0, tmp.find("-"));
				cur_tid++;
				out << cur_tid << "\t" << str << endl;
				out2 << cur_tid << "\t" << tid_vtid_mapping[cur_tid - (num_host_seq + 1)] << endl;
				out3 << vidcds_virus[tid_vtid_mapping[cur_tid - (num_host_seq + 1)]] << "\t" << anno_sort[cur_tid - (num_host_seq + 1)] << endl;
				tmp = tmp.substr(tmp.find("-") + 1);
			}
		}
		out.close();
		out2.close();
		out3.close();
	}

	if (aid_gen)
	{
		cout << "aid_gen" << endl;

		ifstream in_anno(dataPath + "/virus_annotation_sid.txt");
		ifstream in_sort_anno(outputPath + "/virus_sort_annotation_sid.txt");
		ifstream in_acc(dataPath + "/virus_sid_accs.txt");

		ofstream out_vid_tids(dataPath + "/virus_sort_oid_tids.txt");
		ofstream out_tid_vid(outputPath + "/sid_oid.txt");
		ofstream out_tid_aids(outputPath + "/sid_vidset.txt");
		ofstream out_vid_aids(outputPath + "/oid_vidset.txt");

		ofstream out_aid_acc(dataPath + "/virus_sort_vid_acc.txt");

		int cur_tid;
		map<string, int> anno_tid;	// tid of annotation_sid
		map<int, int> stid_tid;

		string cur_virus, bef_virus;
		int cur_vid;

		map<int, string> tid_accs;
		map<int, string> stid_accs;

		// generating anno_cid
		cur_tid = num_host_seq;
		while (getline(in_anno, tmp)) {
			cur_tid++;
			anno_tid[tmp] = cur_tid;
		}
		in_anno.close();
		cur_tid = num_host_seq;
		while (getline(in_sort_anno, tmp)) {
			cur_tid++;
			tmp.erase(0, tmp.find("\t") + 1);
			stid_tid[cur_tid] = anno_tid[tmp];
		}
		// end of generating anno_cid

		// print sort_cid_vid
		cur_tid = num_host_seq;
		cur_vid = 0;
		bef_virus.clear();
		in_sort_anno.clear();
		in_sort_anno.seekg(0, in_sort_anno.beg);
		while (getline(in_sort_anno, tmp)) {
			cur_tid++;

			cur_virus = tmp.substr(0, tmp.find("="));
			if (bef_virus != cur_virus) {
				cur_vid++;
			}

			out_tid_vid << cur_tid << "\t" << cur_vid << endl;
			bef_virus = cur_virus;
		}
		out_tid_vid.close();
		// end of print sort_tid_vid

		cur_tid = num_host_seq;
		while (getline(in_acc, tmp)) {	// cid_rem_accs
			cur_tid++;
			tid_accs[cur_tid] = tmp.substr(tmp.find("\t") + 1);
		}
		in_acc.close();
		map<int, int>::iterator it;
		for (it = stid_tid.begin(); it != stid_tid.end(); it++) {
			stid_accs[it->first] = tid_accs[it->second];
		}

		ifstream in_tid_vid(outputPath + "/sid_oid.txt");
		cur_tid = num_host_seq;

		int bef_vid = 1;
		int cur_aid = 0;
		int xxx = num_host_seq + 1;
		string cur_accs, cur_acc;
		map<string, int> acc_aid;
		map<int, bool> cur_aids;	// for cids
		map<int, bool> cur_aids2;	// for vids;

		cur_aids2.clear();
		// to print out2 (sort_vid_cid_map)
		while (getline(in_tid_vid, tmp)) {	// vid mapping for tid
			cur_aids.clear();
			cur_tid++;
			cur_vid = stoi(tmp.substr(tmp.find('\t') + 1));

			if (cur_vid != bef_vid) {	// aid++ if vid changes
				for (auto itt = acc_aid.begin(); itt != acc_aid.end(); itt++) {
					out_aid_acc << itt->second << "\t" << itt->first << endl;
				}
				acc_aid.clear();
				out_vid_tids << bef_vid << "\t" << xxx;	// for each vid(for each virus organism) print tids
				for (int i = xxx + 1; i < cur_tid; i++) {
					out_vid_tids << "-" << i;
				}
				out_vid_tids << endl;
				xxx = cur_tid;

				str.clear();
				map<int, bool>::iterator it2;
				for (it2 = cur_aids2.begin(); it2 != cur_aids2.end(); it2++) {
					str += "-" + to_string(it2->first);
				}
				out_vid_aids << bef_vid << "\t" << str.substr(1) << endl;

				cur_aids2.clear();
			}
			// start generating current cid's and org's aids
			cur_accs = stid_accs[cur_tid];
			size_t pos = 0;
			while ((pos = cur_accs.find("-")) != string::npos) {
				cur_acc = cur_accs.substr(0, pos);
				if (acc_aid.find(cur_acc) == acc_aid.end()) { // if it is the first accession number in this virus organism
					cur_aid++;
					acc_aid[cur_acc] = cur_aid;
					cur_aids[cur_aid] = true;
					cur_aids2[cur_aid] = true;
				}
				else {
					cur_aids[acc_aid[cur_acc]] = true;
					cur_aids2[acc_aid[cur_acc]] = true;
				}
				cur_accs.erase(0, pos + 1);
			}
			cur_acc = cur_accs;
			if (acc_aid.find(cur_acc) == acc_aid.end()) { // if it is the first accession number in this virus organism
				cur_aid++;
				acc_aid[cur_acc] = cur_aid;
				cur_aids[cur_aid] = true;
				cur_aids2[cur_aid] = true;
			}
			else {
				cur_aids[acc_aid[cur_acc]] = true;
				cur_aids2[acc_aid[cur_acc]] = true;
			}
			// end something

			str.clear();
			map<int, bool>::iterator it;
			for (it = cur_aids.begin(); it != cur_aids.end(); it++) {
				str += "-" + to_string(it->first);
			}
			out_tid_aids << cur_tid << "\t" << str.substr(1) << endl;

			bef_vid = cur_vid;
		}

		out_tid_aids.close();

		for (auto itt = acc_aid.begin(); itt != acc_aid.end(); itt++) {
			out_aid_acc << itt->second << "\t" << itt->first << endl;
		}

		out_vid_tids << bef_vid << "\t" << xxx;
		for (int i = xxx + 1; i <= cur_tid; i++) {
			out_vid_tids << "-" << i;
		}
		out_vid_tids << endl;
		out_vid_tids.close();
		str.clear();
		map<int, bool>::iterator it2;
		for (it2 = cur_aids2.begin(); it2 != cur_aids2.end(); it2++) {
			str += "-" + to_string(it2->first);
		}
		out_vid_aids << bef_vid << "\t" << str.substr(1) << endl;
		in_tid_vid.close();
	}
	return;
}
