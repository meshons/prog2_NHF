#ifndef STRING_H
#define STRING_H

#ifndef NULL
#define NULL 0
#endif

#include <cstdlib> //size_t
#include <new>

namespace NHF
{
class String
{
    struct Cell;
    Cell *first;

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
    String();
    String(const String &);
    String(const char *);
    String(Iterator, Iterator);
    ~String();

    Iterator begin();
    const Iterator begin() const;
    Iterator end();
    const Iterator end() const;
    //reverse iterator?

    size_t size() const;
    size_t length() const;

    size_t capacity() const;

    void clear();
    bool empty() const;

    char &operator[](unsigned int);
    char &at(unsigned int);

    //basic_string& operator+=(const char *);

  public:
    class Iterator
    {
        Cell *cell;
        unsigned char num;

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

        unsigned char getNum(){return num;}
        //char& operator[](unsigned int);
    };
};
}

#endif