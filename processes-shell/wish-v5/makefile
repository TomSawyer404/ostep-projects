FLAG = -Wall -Werror -g
CMPE = -c -Wall -g

EVAL = eval-v5
COMCTR = CommandConstructor-v2
DRD = DoRedirection-v2
PFP = ParseForParallel


main: $(EVAL).o $(COMCTR).o $(DRD).o $(PFP).o
	gcc $(FLAG) -o wish wish-v2.c $(EVAL).o  $(COMCTR).o $(DRD).o $(PFP).o

clean:
	rm *.o wish

$(EVAL).o: $(EVAL).c
	gcc $(CMPE) $(EVAL).c

$(COMCTR).o: $(COMCTR).c
	gcc $(CMPE) $(COMCTR).c

$(DRD).o: $(DRD).c
	gcc $(CMPE) $(DRD).c

$(PFP).o: $(PFP).c
	gcc $(CMPE) $(PFP).c
