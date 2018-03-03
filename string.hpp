#ifndef STRING_H
#define STRING_H

#ifndef NULL
#define NULL 0
#endif

#include <new>

namespace NHF{
    template <typename T>
    class basic_string{
        struct Cell;
        Cell * data;
    public:
        class Iterator;
    private:
        struct cell{
            T data[20];
            Cell * next;
            Cell * prev;
        };
    public:
        basic_string();


    public:
        class Iterator{
            Cell * cell;
            unsigned char num;
        public:
            Iterator(Cell * c, unsigned char num=0):cell(c),num(num){
            }
            Iterator(const Iterator&);
            ~Iterator(){}
            Iterator& operator=(const Iterator&);
            Iterator& operator++();
            Iterator operator++(int);
            T& operator*() const;
            //T& operator[](unsigned int);

        };
    };

    typedef basic_string<char> string;
    typedef basic_string<unsigned char> ustring;
    typedef basic_string<unsigned short> unistring;

}


#endif