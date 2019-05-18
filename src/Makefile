OUTPUT=socketmud
C_FLAGS	= -Wall -pedantic -ansi -ggdb -O0 -std=c++11 -march=native
L_FLAGS	= 

O_FILES	= socket.o server.o main.o

all:	$(O_FILES)
	rm -f $(OUTPUT)
	c++ -o $(OUTPUT) $(O_FILES) $(L_FLAGS)

$(O_FILES): %.o: %.cpp
	c++ -c $(C_FLAGS) $<

clean:
	rm -f *.o
	rm -f SocketMud
