# Makefile - R Arce
all: client

client: client.o ParsedFile.o
	c++ client.o ParsedFile.o -o client

client.o: client.cpp ParsedFile.h 
	c++ -c client.cpp

ParsedFile.o: ParsedFile.cpp ParsedFile.h 
	c++ -c ParsedFile.cpp

clean: 
	rm -rf *.o

pack:
	tar cvzf engine.tgz client.cpp ParsedFile.h ParsedFile.cpp Makefile
