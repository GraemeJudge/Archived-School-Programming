client:
	gcc -g -Wall ClientMain.c Controller.c Communication.c Client.c -o Client -lpthread

server:
	gcc -g -Wall Server.c SerialComms.c -o Server -lpthread

all:
	make server
	make client

clean:
	rm -rf Client
	rm -rf Server
