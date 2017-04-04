EXECUTABLES = main main_node searcher merger
CC = gcc
FLAGS = -g -o 
all: $(EXECUTABLES)
# create/compile the individual files >>separately<< 
main: 
	$(CC) $(FLAGS) main main.c secondary_functions.c main_functions.c

main_node: 
	$(CC) $(FLAGS) main_node main_node.c secondary_functions.c -lm

searcher: 
	$(CC) $(FLAGS) searcher searcher.c secondary_functions.c
merger: 
	$(CC) $(FLAGS) merger merger.c secondary_functions.c
# clean house
clean:
	rm -f $(EXECUTABLES)
