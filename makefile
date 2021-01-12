all : exe

exe: session.o data.o repReq.o ./clt/clt.o ./srv/srv.o	
	gcc session.o repReq.o data.o ./clt/clt.o ./srv/srv.o -o exe

session.o : session.c ./lib/session.h
		gcc -o session.o -c session.c -Wall -O 

data.o : data.c ./lib/data.h
		gcc -o data.o -c data.c -Wall -O 
	    
repReq.o : repReq.c ./lib/repReq.h
		gcc -o repReq.o -c repReq.c -Wall -O

srv.o : ./srv/srv.c ./lib/standard.h
		gcc -o srv.o -c ./srv/srv.c -Wall -0	

clt.o : ./clt/clt.c
		gcc -o clt.o -c ./clt/clt.c -Wall -0	
	
clean : 
		rm -rf *.o





