all: miner

miner: main.c siggen.c siggen.h
	gcc -Wall -o miner main.c siggen.c 
