CXX=clang++
CXXFLAGS=-std=c++17 -Werror -Wsign-conversion -g
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99
 
SOURCES=Tile.cpp Edge.cpp Vertex.cpp Hexagon.cpp Board.cpp Card.cpp Catan.cpp Player.cpp

OBJECTS=$(subst .cpp,.o,$(SOURCES)) 

.PHONY: clean tidy valgrind

run: catan
	./$^

runtests: test
	./$^

catan: Main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o catan test
