a.out: addition.o division.o main.o multiplication.o subtraction.o
	gcc -o a.out addition.o division.o main.o multiplication.o subtraction.o

addition.o: addition.c
	gcc -c addition.c

division.o: division.c
	gcc -c division.c

main.o: main.c
	gcc -c main.c

multiplication.o: multiplication.c
	gcc -c multiplication.c

subtraction.o: subtraction.c
	gcc -c subtraction.c

clean:
	rm -f *.o a.out