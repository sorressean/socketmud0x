CC	= g++
C_FLAGS	= -Wall -pedantic -ansi -g
L_FLAGS	= 

O_FILES	= socket.o server.o socketmud.o

all:	$(O_FILES)
	rm -f SocketMud
	$(CC) -o SocketMud $(O_FILES) $(L_FLAGS)

$(O_FILES): %.o: %.cpp
	$(CC) -c $(C_FLAGS) $<

clean:
	rm -f *.o
	rm -f *.*~
	rm -f SocketMud
