debug:
	clang++ -c memtrace.cpp -o memtrace.o -Wall 
	clang++ string.cpp -c -g -DMEMTRACE -Weverything -Wno-padded -pedantic -std=c++11 -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-weak-vtables -Wno-padded
	clang++ test_main.cpp  string.o -o test2.exe -g -DMEMTRACE -Weverything -pedantic -std=c++11 -Wno-c++98-compat-pedantic  -Wno-old-style-cast -Wno-weak-vtables -Wno-padded
