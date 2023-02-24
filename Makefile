randmst: prim_test.o heap.o
	g++ prim_test.o heap.o -o randmst

prim_test.o: prim_test.cpp
	g++ -std=gnu++11 -c prim_test.cpp

heap.o: heap.cpp heap.hpp
	g++ -c heap.cpp

clean:
	rm *.o randmst