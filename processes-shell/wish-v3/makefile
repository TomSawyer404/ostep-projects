FLAG = -Wall -Werror -g
CMPE = -c -Wall -g

EVAL = eval-v3
COMCTR = CommandConstructor
DRD = DoRedirection


main: $(EVAL).o $(COMCTR).o $(DRD).o
	gcc $(FLAG) -o wish wish.c $(EVAL).o  $(COMCTR).o $(DRD).o 

clean:
	rm *.o wish

$(EVAL).o: $(EVAL).c
	gcc $(CMPE) $(EVAL).c

$(COMCTR).o: $(COMCTR).c
	gcc $(CMPE) $(COMCTR).c

$(DRD).o: $(DRD).c
	gcc $(CMPE) $(DRD).c
