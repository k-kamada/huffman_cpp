main: main.cpp huffman.cpp
	g++ -o main main.cpp huffman.cpp -Wall -std=c++14

test: unittest.cpp huffman.cpp
	g++ -o test unittest.cpp huffman.cpp -Wall -std=c++14 -lcpptest
