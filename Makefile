debug:
	clang++ string.cpp -c -g -Weverything -Wno-padded -pedantic -std=c++11 -Wno-c++98-compat-pedantic -Wno-old-style-cast
	clang++ test_main.cpp string.o -o test2.exe -g -Weverything -pedantic -std=c++11 -Wno-c++98-compat-pedantic  -Wno-old-style-cast
