all:
session.o : session.c ./lib/session.h
		gcc -o session.o -c session.c -Wall -O 

data.o : data.c ./lib/data.h
		gcc -o data.o -c data.c -Wall -O 
	    
repReq.o : repReq.c repReq.h
		gcc -o repReq.o -c repReq.c -Wall -O
		

srv : serveur
serveur : session.o data.o repReq.o srv.o 
		gcc -o serveur session.o data.o repReq.o srv.o -Wall -O
	 
srv.o : srv.c
		gcc -o srv.o -c srv.c -Wall -O
		
	
clt : client
client : session.o data.o repReq.o clt.o 
		gcc -o serveur session.o data.o repReq.o clt.o -Wall -O
	 
clt.o : clt.c
		gcc -o clt.o -c clt.c -Wall -O
		
	
clean : 
		rm -f *.o core
	
