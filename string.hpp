#ifndef STRING_H
#define STRING_H

#ifndef NULL
#define NULL 0
#endif

#include <cstdlib> //size_t
#include <new>

namespace NHF {
class String {
  struct Cell;
  Cell *first;

public:
  class Iterator;

private:
  struct Cell {
    char data[20];
    Cell *next;
    Cell *prev;
    Cell() {
      for (int i = 0; i < 20; i++)
        data[i] = 0;
    }
  };

public:
  String();
  String(const String &);
  String(const char *);
  String(Iterator, Iterator);
  ~String();
  String &operator=(const String &);
  String &operator=(const char *);
  String &operator=(char);

  Iterator begin();
  const Iterator begin() const;
  Iterator end();
  const Iterator end() const;
  // reverse iterator?

  size_t size() const;
  size_t length() const;

  size_t capacity() const;

  void clear();
  bool empty() const;

  char &operator[](unsigned int);
  const char &operator[](unsigned int) const;
  char &at(unsigned int);
  const char &at(unsigned int) const;

  // basic_string& operator+=(const char *);
  // operator+=
  // operator+

  // compare operators

public:
  class Iterator {
    const String *const parent;
    Cell *cell;
    unsigned char num;

  public:
    Iterator(const String *const s, Cell *c, unsigned char num = 0)
        : parent(s), cell(c), num(num) {}
    Iterator(const Iterator &i) : parent(i.parent), cell(i.cell), num(i.num) {}
    ~Iterator() {}
    Iterator &operator=(const Iterator &);
    Iterator &operator++();
    Iterator operator++(int);
    char &operator*();
    const char &operator*() const;

    unsigned char getNum() { return num; }

    char &operator[](unsigned int);
    const char &operator[](unsigned int) const;

    bool operator==(const Iterator &) const;
    bool operator!=(const Iterator &) const;

    //+
    Iterator operator+(int);
    // out too
    //-
    Iterator operator-(int);
    int operator-(Iterator &); // todo
    //-=
    Iterator &operator-=(int);
    //+=
    Iterator &operator+=(int);
    //>
    bool operator>(const Iterator &) const;
    //<
    bool operator<(const Iterator &) const;
    //>=
    bool operator>=(const Iterator &) const;
    //<=
    bool operator<=(const Iterator &) const;
  };
};

String::Iterator operator+(int i, String::Iterator &);

} // namespace NHF

#endif