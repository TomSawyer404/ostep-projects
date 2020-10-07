FLAG = -Wall -Werror -g
CMPE = -c -Wall -Og -g

main: eval-v1.o parseline.o
	gcc $(FLAG) wish.c eval-v1.o parseline.o -o wish

clean:
	rm *.o wish

eval-v1.o: eval-v1.c
	gcc $(CMPE) eval-v1.c

parseline.o: parseline.c
	gcc $(CMPE) parseline.c

