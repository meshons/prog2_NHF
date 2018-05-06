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
  virtual void write(std::ostream &os) const = 0;
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

  //! A speciális streamre írás a perzisztenciához
  virtual void write(std::ostream &) const;
  //! A speciális streamből beolvasás a perzisztenciához
  virtual void read(std::istream &);

  //! explicit operator=
  String &operator=(const String &);
  //! explicit operator=
  String &operator=(const char *);
  //! explicit operator=
  String &operator=(char);

  //! Iterator a String kezdetére
  Iterator begin() const;
  //! Iterator a String vége után
  Iterator end() const;

  //! A String-ben tárolt karaktersorozat hossza
  size_t size() const;
  //! A String-ben tárolt karaktersorozat hossza
  size_t length() const;

  //! A String jelenlegi maximális kapacitása
  size_t capacity() const;

  //! Kiüríti a String-et
  void clear();
  //! Megadja hogy üres-e a String
  /*! @return bool, hogy üres-e */
  bool empty() const;

  //! referencia a String adott pozíciójú elemére
  char &operator[](size_t);
  //! konstans referencia a String adott pozíciójú elemére
  const char &operator[](size_t) const;
  //! referencia a String adott pozíciójú elemére
  char &at(size_t);
  //! konstans referencia a String adott pozíciójú elemére
  const char &at(size_t) const;

  //! a String c szerű stringé konvertálása, memóriát foglal!
  const char *c_str() const; // lefoglal

  //! összefűzés
  String &operator+=(const char *);
  //! összefűzés
  String &operator+=(const char);
  //! összefűzés
  String &operator+=(const String &);
  //! összefűzés
  String operator+(const char *) const;
  //! összefűzés
  String operator+(const char) const;
  //! összefűzés
  String operator+(const String &) const;

  // todo
  bool operator<(const String &) const;
  bool operator<=(const String &) const;
  bool operator>(const String &) const;
  bool operator>=(const String &) const;

  //! két String megegyezik-e
  bool operator==(const String &) const;
  //! két String eltér-e
  bool operator!=(const String &) const;

public:
  //! A String saját Iterátora
  /*! Saját Iterátor osztály, ami tárolja a String pointerét, az adott cellát és
   * pozíciót a cellában */
  class Iterator {
    const String *parent; //!< az iterátor Stringjének pointere
    Cell *cell;           //!< az aktuális cellára mutató pointer
    size_t num;           //!< az aktuális pozíció

  public:
    //! Az Iterátor konstrukra
    /*! @param s a String
        @param num2 a pozíció, ha van megadva cella akkor attól számítva,
       alapból
       0
        @param c a cella, amitől számítja a pozíciót */
    Iterator(const String *s, size_t num2 = 0, Cell *c = NULL)
        : parent(s), num(num2) {
      if (c == NULL)
        cell = s->first;
      else
        cell = c;
    }
    //! Iterátor másoló konstuktora
    /*! @param i a másolandó Iterator */
    Iterator(const Iterator &i) : parent(i.parent), cell(i.cell), num(i.num) {}
    //! explicit operator=
    Iterator &operator=(const Iterator &);
    //! az Iterátor preinkrementálása
    Iterator &operator++();
    //! az Iterátor posztinkrementálása
    Iterator operator++(int);

    //! hivatkozás az Iterátor által mutatott elemre
    char &operator*();
    //! a mutatott elem értéke
    char val();
    //! konstans referncia az Iterátor által mutatott elemre
    const char &operator*() const;

    //! megnézi, hogy az utolsóra mutat-e a cellában az Iterátor
    /*! @return igaz, ha a num 20, egyébként hamis */
    bool lastInCell() { return num == 20; }

    //! Visszaadja az iterátor pozícióját a cellán belül
    /*! @return a mutatott pozíció száma a cellában */
    size_t getNum() { return num; }

    // todo int

    //! elem elérése az adott pozíciótól relatív távra
    char &operator[](size_t);
    //! konstans elem elérése az adott pozíciótól relatív távra
    const char &operator[](size_t) const;

    //! két Iterátor megegyezését vizsgálja
    bool operator==(const Iterator &) const;
    //! két Iterátor különbözőségét vizsgálja
    bool operator!=(const Iterator &) const;
    //! két Iterátor Stringjének megegyezését vizsgálja
    bool operator^(const Iterator &) const;

    //! Iterátor léptetése megadott számmal
    Iterator operator+(size_t);
    //! Iterátor léptetése megadott számmal
    Iterator operator+(long long);
    //! Iterátor csökkentése megadott számmal
    Iterator operator-(size_t);
    //! Iterátor csökkentése megadott számmal
    Iterator operator-(long long);
    //! Iterátorok különbségének kiszámolása
    size_t operator-(Iterator &);
    //! Iterátor csökkentése megadott számmal
    Iterator &operator-=(size_t);
    //! Iterátor növelése megadott számmal
    Iterator &operator+=(size_t);
    //! Megállapítja, hogy az Iterátor pozíciója nagyobb-e, mint a másiké
    bool operator>(const Iterator &) const;
    //! Megállapítja, hogy az Iterátor pozíciója kiseebb-e, mint a másiké
    bool operator<(const Iterator &) const;
    //! Megállapítja, hogy az Iterátor pozíciója nagyobb-egyenlő-e
    bool operator>=(const Iterator &) const;
    //! Megállapítja, hogy az Iterátor pozíciója kisebb-egyenlő-e
    bool operator<=(const Iterator &) const;
  };
};

//! Összefűzés jobboldali String-el
String operator+(const char *, const String &);
//! Összefűzés jobboldali String-el
String operator+(const char, const String &);

//! String kiírása stream-re operator<<
std::ostream &operator<<(std::ostream &, const String &);
//! String beolvasása stream-ről operator>>
std::istream &operator>>(std::istream &, String &);

//! Az Iterátor növelése számmal
String::Iterator operator+(size_t, String::Iterator &);

} // namespace NHF

#endif
