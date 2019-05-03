# tihi target will compile all the file
#all:
#	g++ CSVReader.cpp Query.cpp test_impl/UserImplementationTets.cpp -o reader

CC=g++ -g#declare variable. To get it call - $(CC) (single char vars do not need parentheses). In this case CC represent type of compiler
CFLAGS = -c   # compiler flags: 
			#-Wall - print "all" warning messages
			#-c - compile-only (produce object file). Use ./ld for building
.PHONY = all clean # that targets are not associated with files. Always run that targets even in a case file with corresponding file name exist 
		   # and are up to date	
all: reader

reader: main.o query.o record.o test_impl.o
	$(CC) -g main.o query.o record.o test_impl.o -o reader # -o - set name of an output file
	

main.o: CSVReader.cpp
	$(CC) $(CFLAGS) CSVReader.cpp -o main.o

query.o: Query.cpp
	$(CC) $(CFLAGS) Query.cpp -o query.o

record.o: Record.cpp Record.h
	$(CC) $(CFLAGS) Record.cpp -o record.o

test_impl.o: test_impl/UserImplementationTets.cpp
	$(CC) $(CFLAGS) test_impl/UserImplementationTets.cpp -o test_impl.o
clean:
	rm -rf *o reader #remove all object file and executable 

#General rule:
#      target: pre-req-1 pre-req-2 ...
#              command
#Example:
#      hello.exe: hello.o
#		gcc -o hello.exe hello.o
#Automatic variables (are set after rule is matched):
# $@ -target filename (hello.exe)
# $* -target filename without the file extension (hello)
# $< -first prerequisite filename
# $^ - the filenames of all prerequisites, separetad by spaces, discard duplicates
# $+ - similar to $^, but includes duplicates
# $? - names of all prerequisites that are newer than the target, separated by spaces

# SRCS := $(wildcard *.c)

