# VPrimer input data generator
VPrimer: A method of designing and updating primer and probe with high variant coverage for RNA virus detection

https://pubmed.ncbi.nlm.nih.gov/34951850/

https://github.com/qhtjrmin/VPrimer/

# 1. Get VPrimer input data generator
To get VPrimer input data generator, follow the queries.
```
$ git clone https://github.com/Hajin-Jeon/VPrimer-input-generator
```
The source codes are in "src" folder.

The guidline for execution is in section 2.

## Environment
VPrimer input data generator needs the following software to run in the system:
- gcc/g++ 4.8.x or later

# 2. Running
## 2.1. Prepare input sequence data
The example of input files that can be used are in "input_test" folder. 

The required data is as follow in "FASTA" folder:
- host sequence (host.fasta, in FASTA format)
- virus sequence (virus.fasta, in FASTA format)

At this time, the format of the virus sequence should be as follows:
- starts with '>' sign
- each column must be separated by the '|' symbol
- The structure as "(Coding Sequence) [Virus Name]"
- (for example: >QLI57642.1 |hypothetical protein [Orf virus]): starts with '>' sign, separated by '|' symbol, CDS is hypothetical protein, and virus name is Orf virus

## 2.2 make
input "make" in the "src" folder. Then, the file "VPrimer_input_generator" would be generated.

## 2.3 execution order
The basic execution order is as follows.
- host sequence parsing
- virus sequence parsing
- generating mapping data

## 2.4 how to start

Optional arguments: 

| Parameter                 | Default       | Description   |	
| :------------------------ |:-------------:| :-------------|
| -i 	       |	../FASTA           |input FASTA sequence folder path
| -d          | ../data           |final output folder path
| -o 	       |	../result	            |intermediate data folder path
| -h (or others)	       | (none)	           | help message

Example: 
```
./VPrimer_input_generator -i /home/(username)/VPrimer/FASTA -d /home/(username)/VPrimer/data/ -o /home/(username)/VPrimer/result/
```

# 3. Result
The intermediate data will be generated as follow in "data" folder:
- mapping data for sid and sequence (virus_sid_sequence.txt)
- mapping data for tid and sequence (host_tid_sequence.txt, virus_tid_sequence.txt)
- virus_sid_tids.txt
- virus_annotation_sid.txt
- virus_tid_acc.txt
- virus_sid_accs.txt
- virus_virus_oid.txt
- virus_viruscds_cid.txt
- virus_sid_oids.txt
- virus_oid_sid.txt
- virus_sid_cids.txt
- virus_cid_sid.txt
- virus_sort_tid_vidcds_seq.txt
- virus_sort_tid_cid.txt
- virus_sort_annotation_sid.txt
- virus_sort_oid_tids.txt
- virus_sort_tid_oid.txt
- virus_sort_tid_vids.txt
- virus_sort_oid_vids.txt
- virus_sort_vid_acc.txt

The result data will be generated as follow in "result" folder:
- mapping data for sid and sequence (host_sid_sequence, virus_sort_tid_seq.txt)
- mapping data for virus sequence (oid-vidset, sid-oid, sid-vidset)
- annotation data (host_annotation.txt, virus_sort_annotation_sid.txt) (not be used in VPrimer CLI mode)


If you have any question, please contact summerj2@dgist.ac.kr

