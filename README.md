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

## 2.2 make
input "make" in the "src" folder. Then, the file "VPrimer_input_generator" would be generated.

## 2.3 execution order
The basic execution order is as follows.
- host sequence parsing
- virus sequence parsing
- generating mapping data

# 3. Result
The intermediate data will be generated as follow in "data" folder:
- annotation data (host_annotation.txt, virus_annotation.txt)
- mapping data for tid and sequence (host_tid_sequence.txt, virus_tid_sequence.txt)

The result data will be generated as follow in "result" folder:
- mapping data for sid and sequence (host_sid_sequence.txt, virus_sid_sequence.txt)
- mapping data for virus sequence (oid-vidset, sid-oid, sid-vidset)


If you have any question, please contact summerj2@dgist.ac.kr

