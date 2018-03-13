#ifndef STRING_H
#define STRING_H

#ifndef NULL
#define NULL 0
#endif

#include <new>

namespace NHF
{
class basic_string
{
    struct Cell;
    Cell *data;

  public:
    class Iterator;

  private:
    struct Cell
    {
        char data[20];
        Cell *next;
        Cell *prev;
    };

  public:
    basic_string();
    basic_string(basic_string &);
    basic_string(const char *);
    basic_string(Iterator s, Iterator e);

    char &operator[](unsigned int);
    char &at(unsigned int);

    //basic_string& operator+=(const char *);

  public:
    class Iterator
    {
        Cell *cell, *last_cell;
        unsigned char num, last_num;

      public:
        Iterator(Cell *c, unsigned char num = 0) : cell(c), num(num)
        {
        }
        Iterator(const Iterator &);
        ~Iterator() {}
        Iterator &operator=(const Iterator &);
        Iterator &operator++();
        Iterator operator++(int);
        char &operator*() const;
        //T& operator[](unsigned int);
    };
};
}

#endif