All:
	g++ string.cpp -c -g -Wall -pedantic
	g++ test_main.cpp string.o -o test.exe -g -Wall -pedantic