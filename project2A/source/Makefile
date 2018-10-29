all: part1 part2 part3 part4

part1: part1.c
	gcc -o part1 part1.c -pthread

part2: part2.c
	gcc -o part2 part2.c -pthread

part3: part3.c
	gcc -o part3 part3.c -pthread

part4: part4.c
	gcc -o part4 part4.c -pthread

clean:
	rm -f part? part?-output.txt *.o

runpart1:
	./part1 50

runpart2:
	./part2 50

runpart3:
	./part3 50

runpart4:
	./part4 50
