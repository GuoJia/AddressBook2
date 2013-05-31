AddBook: Main.o Command.o JSONList.o
	g++ -o AddBook Main.o Command.o JSONList.o
Main.o: Main.cpp Command.h
	g++ -c Main.cpp
Command.o: Command.cpp JSONList.h
	g++ -c Command.cpp
JSONList.o: JSONList.cpp
	g++ -c JSONList.cpp
clean:
	rm AddBook Main.o Command.o JSONList.o
