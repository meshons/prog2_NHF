#ifndef STRING_H
#define STRING_H

#ifndef NULL
#define NULL 0
#endif

#include <cctype>  //isspace
#include <cstdlib> //size_t
#include <iostream>
#include <new>

//! PROG2 nagyházifeladat névtere
namespace NHF {

//! Általános osztály
/*! Általános osztály, ami képes std::ostream-re kiírni
 illetve std::istream-ből beolvasni a származtatott osztályt */
class Object {
public:
  //! Virtuális destruktor
  /*! Virtuális destruktor, hogy a származottnak is lehessen saját destruktora
   */
  virtual ~Object() {}

  /// Absztrakt print függvény
  /*! Absztrakt print függvény az objektum std::ostream-re való kiírására
      @param os a cél std::ostream */
  virtual void print(std::ostream &os) const = 0;
  /// Absztrakt read függvény
  /*! Absztrakt read függvény az objektum std::istream-ről való beolvasásra
      @param is a forrás std::istream */
  virtual void read(std::istream &is) = 0;
};

//! A String osztály
/*! Az általános osztály származtatott String osztály, 20-as méretű char
    tömbökkel tárolva, saját Iterator-al és minél több értelmes művelettel */
class String : public Object {

public:
  class Iterator;

private:
  //! Cella osztály
  /*! Kétirányű láncolt lista fix 20-as méretű char tömbök tárolására */
  struct Cell {
    char data[20]; //!< 20-as méretű char tömb a tárolásra
    Cell *next;    //!< a következő cellára mutató pointer
    Cell *prev;    //!< az előző cellára mutató pointer

    //! Explicit default konstruktor
    /*! Alapértelmezetten 0-ával tölti fel a data tömböt és
        NULL értéket állít a next és prev pointer-be */
    Cell() {
      for (int i = 0; i < 20; i++)
        data[i] = 0;
      next = NULL;
      prev = NULL;
    }
  };

  //! Az első cellára mutató pointer
  Cell *first;

public:
  //! Explicit default konstruktor
  String();
  //! Explicit másoló konstruktor
  String(const String &);
  //! Konstruktor c string-ből
  String(const char *);
  //! Konstruktor char-ból
  String(char);
  //! Konstruktor nyitó és záró Iterátor-ból
  String(Iterator, Iterator);
  //! Virtuális destruktor
  virtual ~String();

  virtual void print(std::ostream &) const;
  virtual void read(std::istream &);

  String &operator=(const String &);
  String &operator=(const char *);
  String &operator=(char);

  Iterator begin() const;
  Iterator end() const;

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

  // todo
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
    Iterator(const String *const s, Cell *c = NULL, unsigned char num = 0)
        : parent(s), num(num) {
      if (c == NULL)
        cell = s->first;
      else
        cell = c;
    }
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
    bool operator^(const Iterator &) const;

    Iterator operator+(int);
    Iterator operator-(int);
    int operator-(Iterator &);
    Iterator &operator-=(int);
    Iterator &operator+=(int);
    bool operator>(const Iterator &) const;
    bool operator<(const Iterator &) const;
    bool operator>=(const Iterator &) const;
    bool operator<=(const Iterator &) const;
  };
};

String operator+(const char *, const String &);
String operator+(const char, const String &);

std::ostream &operator<<(std::ostream &, const String &);
std::istream &operator>>(std::istream &, String &);

String::Iterator operator+(int, String::Iterator &);

} // namespace NHF

#endif