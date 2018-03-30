#ifndef STRING_H
#define STRING_H

#ifndef NULL
#define NULL 0
#endif

#include <cstdlib> //size_t
#include <iostream>
#include <new>

namespace NHF {

class Object {
public:
  virtual ~Object() {}
  virtual void print(std::ostream &) = 0;
};

class String : public Object {
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
      next = NULL;
      prev = NULL;
    }
  };

public:
  String();
  String(const String &);
  String(const char *);
  String(char);
  String(Iterator, Iterator);
  ~String();

  void print(std::ostream &);

  String &operator=(const String &);
  String &operator=(const char *);
  String &operator=(char);

  Iterator begin() const;
  // const Iterator begin() const;
  Iterator end() const;
  // const Iterator end() const;
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

  const char *c_str() const; // lefoglal

  String &operator+=(const char *);
  String &operator+=(const char);
  String &operator+=(const String &);
  String operator+(const char *) const;
  String operator+(const char) const;
  String operator+(const String &) const;

  bool operator<(const String &) const;
  bool operator<=(const String &) const;
  bool operator>(const String &) const;
  bool operator>=(const String &) const;
  bool operator==(const String &) const;
  bool operator!=(const String &) const;

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
    char val();
    const char &operator*() const;

    bool lastInCell() { return num == 20; }

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

String operator+(const char *, const String &);
String operator+(const char, const String &);

std::ostream operator<<(std::ostream &os, String &s);
std::ostream operator>>(std::ostream &os, String &s);

String::Iterator operator+(int i, String::Iterator &);

} // namespace NHF

#endif