HT: HT.o puu.o tiedosto.o
	gcc HT.o puu.o tiedosto.o -o HT -Wall -ansi
HT.o: HT.c puu.h tiedosto.h
	gcc HT.c -c -Wall -ansi
puu.o: puu.c puu.h
	gcc puu.c -c -Wall -ansi
tiedosto.o: tiedosto.c tiedosto.h
	gcc tiedosto.c -c -Wall -ansi

clean: 
	$(RM) HT *.o *~
