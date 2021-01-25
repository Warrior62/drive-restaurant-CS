all:
session.o : session.c ./lib/session.h
		gcc -o session.o -c session.c -Wall -O 

data.o : data.c ./lib/data.h
		gcc -o data.o -c data.c -Wall -O 

repReq.o : repReq.c ./lib/repReq.h
		gcc -o repReq.o -c repReq.c -Wall -O


srv : serveurDrive
serveurDrive : session.o data.o repReq.o srv.o 
		gcc -o serveurDrive session.o data.o repReq.o srv.o -Wall -O -lpthread

srv.o : srv.c ./lib/standard.h
		gcc -o srv.o -c srv.c -Wall -O


clt : clientDrive
clientDrive : session.o data.o repReq.o clt.o 
		gcc -o clientDrive session.o data.o repReq.o clt.o -Wall -O -lpthread

clt.o : clt.c ./lib/standard.h
		gcc -o clt.o -c clt.c -Wall -O


clean : 
		rm -f *.o core
