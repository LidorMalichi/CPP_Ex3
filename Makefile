CXX=clang++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Tile.hpp Card.hpp Vertex.hpp Edge.hpp Hexagon.hpp
 
OBJECTS := Test.o TestCounter.o Tile.cpp Edge.cpp Vertex.cpp Hexagon.cpp

.PHONY: clean tidy valgrind

run: catan
	./$^

runtests: test
	./$^

catan: Catan.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) Catan.o -o $@ 

test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ 

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
 
%.o: %.cpp $(SOURCES)
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o catan test
