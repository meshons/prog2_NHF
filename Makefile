debug:
	clang++ -c memtrace.cpp -o memtrace.o -g -DMEMTRACE -Wall -std=c++11
	clang++ string.cpp -c -g -DMEMTRACE -Weverything -Wno-disabled-macro-expansion -Wno-padded -pedantic -std=c++11 -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-weak-vtables -Wno-padded
	clang++ test.cpp memtrace.o string.o -o string.exe -g -DMEMTRACE -Weverything -Wno-disabled-macro-expansion -pedantic -std=c++11 -Wno-c++98-compat-pedantic  -Wno-old-style-cast -Wno-weak-vtables -Wno-padded 