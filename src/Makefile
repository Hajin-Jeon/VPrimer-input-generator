CC=g++
CFLAGS=-g -Wall
TARGET=VPrimer_input_generator
OBJS=main.o 1_gen_host_sequence.o 2_gen_virus_sequence.o library.o

$(TARGET) : $(OBJS)
	$(CC) -O2 -o $@ $(OBJS)

library.o : library.cpp
	$(CC) -c -o library.o library.cpp

1_gen_host_sequence.o : 1_gen_host_sequence.cpp
	$(CC) -c -o 1_gen_host_sequence.o 1_gen_host_sequence.cpp

2_gen_virus_seuqnece.o : 2_gen_virus_sequence.cpp
	$(CC) -c -o 2_gen_virus_sequence.o 2_gen_virus_sequence.cpp

main.o : main.cpp
	$(CC) -c -o main.o main.cpp

clean:
	rm *.o VPrimer_input_generator
