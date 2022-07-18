detect: detect.o utils.o problems.o struc.o
	gcc -Wall -o detect detect.o utils.o problems.o struc.o

detect.o: detect.c utils.h problems.h struc.h
	gcc -Wall -c detect.c

utils.o: utils.c utils.h
	gcc -Wall -c utils.c

problems.o: problems.c problems.h
	gcc -Wall -c problems.c

struc.o: struc.c struc.h
	gcc -Wall -c struc.c

clean:
	rm -f *.o detect
