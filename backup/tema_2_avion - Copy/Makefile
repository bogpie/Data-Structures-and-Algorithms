build:
	gcc -Wall -g piele_bogdan_312ab_tema_2_avion.c DijkstraHeader.c MainHeader.c MinHeapHeader.c GraphHeader.c TrieHeader.c UtilHeader.c -o avion
run:
	./avion date.in rezultate.out
clean:
	rm -f *.o
	rm -f avion
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./avion date.in rezultate.out
