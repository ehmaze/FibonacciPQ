test: executable
	./executable

valgrind_test: executable
	valgrind ./executable
	
executable: main.cpp
	g++ main.cpp -Wall -Werror -pedantic --std=c++11 -o executable

clean:
	rm -f executable main