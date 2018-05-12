#include "string.hpp"
// namespace NHF {

typedef String::Iterator It;

//! saját c string copy
/*! csak 20-ig másol, pont a cellák méretéig
    @param to hova másol
    @param from honnan másol */
inline static void copy(char *to, const char *from) {
  for (int i = 0; i < 20; i++)
    to[i] = from[i];
}

/*! Beállítja a first -öt NULL-ra */
String::String() { first = NULL; }

/*! @param s a másolandó string */
String::String(const String &s) {
  Cell *tmp, *c, *prev = NULL;
  if (s.first != NULL) {
    first = new Cell();
    tmp = first;
    copy(tmp->data, s.first->data);
    tmp->prev = NULL;
    tmp->next = NULL;
    prev = tmp;
    for (c = s.first->next; c != NULL; c = c->next) {
      tmp->next = new Cell();
      tmp = tmp->next;
      copy(tmp->data, c->data);
      tmp->prev = prev;
      tmp->next = NULL;
    }
  } else
    first = NULL;
}

/*! @param str a másolandó c string */
String::String(const char *str) {
  Cell *tmp = first, *prev = NULL;
  unsigned int x = 0;
  while (str[x]) {
    if (x % 20 == 0) {
      if (!x) {
        first = new Cell();
        tmp = first;
      } else {
        prev = tmp;
        tmp->next = new Cell();
        tmp = tmp->next;
      }
      tmp->prev = prev;
      tmp->next = NULL;
    }
    tmp->data[x % 20] = str[x];
    x++;
  }
}
/*! @param c a másolandó karakter */
String::String(char c) {
  first = new Cell();
  first->data[0] = c;
}
/*! Egy másik String két Iterátora közötti részt másolja egy új string-be
    @param begin a kezdő Iterátor
    @param end a befejező Iterátor */
String::String(It begin, It end) {
  if (!(begin ^ end))
    throw "nem egy string-ben van a két Iterator";
  if (begin > end)
    throw "nem zárt intervallum";
  Cell **tmp = &first, *prev = NULL;
  unsigned int x = 0;
  while (begin != end) {
    if (x % 20 == 0) {
      if (!x)
        first = new Cell();
      else {
        prev = (*tmp);
        (*tmp)->next = new Cell();
        (*tmp) = (*tmp)->next;
      }
      (*tmp)->prev = prev;
      (*tmp)->next = NULL;
    }
    (*tmp)->data[x % 20] = *begin;
    begin++;
    x++;
  }
}

/*! Virtuális hogy lehessen származtatni, kitörli a lefoglalt cellákat */
String::~String() {
  Cell *tmp = first;
  while (first != NULL) {
    tmp = first->next;
    delete first;
    first = tmp;
  }
}
/*! @param os a kimeneti stream */
void String::write(std::ostream &os) const {
  os << size() << ',';
  char *s = c_str();
  if (std::streamsize(size()) < 0) {
    std::streamsize p = std::streamsize(size() - 9223372036854775807);
    os.write(s, 9223372036854775807);
    os.write(s + 9223372036854775807, p);
  } else {
    os.write(s, std::streamsize(size()));
  }
  delete[] s;
  os.write("\n", 1);
}
/*! @param is a bemeneti stream */
void String::read(std::istream &is) {
  size_t len;
  while (!(is >> len))
    ;
  is.ignore(1);
  char *p = new char[len + 1];
  if (std::streamsize(len) < 0) {
    std::streamsize l = std::streamsize(len - 9223372036854775807);
    is.read(p, 9223372036854775807);
    is.read(p + 9223372036854775807, l);
  } else {
    is.read(p, std::streamsize(len)).ignore(1);
  }
  p[len] = 0;
  *this = String(p);
  delete[] p;
}
/*! @param s a másolandó String
    @return az objektum referenciája */
String &String::operator=(const String &s) {
  if (this != &s) {
    clear();
    Cell *tmp, *c, *prev = NULL;
    if (s.first != NULL) {
      first = new Cell();
      tmp = first;
      copy(tmp->data, s.first->data);
      tmp->prev = NULL;
      tmp->next = NULL;
      prev = tmp;
      for (c = s.first->next; c != NULL; c = c->next) {
        tmp->next = new Cell();
        tmp = tmp->next;
        copy(tmp->data, c->data);
        tmp->prev = prev;
        tmp->next = NULL;
      }
    } else
      first = NULL;
  }
  return *this;
}
/*! @param str a másolandó c szerű string
    @return az objektum referenciája */
String &String::operator=(const char *str) {
  clear();
  Cell *tmp = first, *prev = NULL;
  unsigned int x = 0;
  while (str[x]) {
    if (x % 20 == 0) {
      if (!x) {
        first = new Cell();
        tmp = first;
      } else {
        prev = tmp;
        tmp->next = new Cell();
        tmp = tmp->next;
      }
      tmp->prev = prev;
      tmp->next = NULL;
    }
    tmp->data[x % 20] = str[x];
    x++;
  }
  return *this;
}
/*! @param c a másolandó karakter
    @return az objektum referenciája */
String &String::operator=(char c) {
  clear();
  first = new Cell();
  first->prev = NULL;
  first->next = NULL;
  first->data[0] = c;
  // first->data[1] = 0;
  return *this;
}
/*! @return size_t - a String-ben tárolt karakter sorozat hossza */
size_t String::size() const {
  size_t sum = 0;
  for (Cell *tmp = first; tmp != NULL; tmp = tmp->next) {
    size_t x = 0;
    while (tmp->data[x] && x < 20)
      x++;
    sum += x;
  }
  return sum;
}
/*! @return size_t - a String-ben tárolt karakter sorozat hossza */
size_t String::length() const {
  size_t sum = 0;
  for (Cell *tmp = first; tmp != NULL; tmp = tmp->next) {
    size_t x = 0;
    while (tmp->data[x] && x < 20)
      x++;
    sum += x;
    if (!tmp->data[x])
      break;
  }
  return sum;
}
/*! @return size_t - a String jelenlegi maximális kapacitása */
size_t String::capacity() const {
  size_t sum = 0;
  for (Cell *tmp = first; tmp != NULL; tmp = tmp->next)
    sum++;
  return sum * 20;
}
void String::clear() {
  Cell *tmp;
  while (first != NULL) {
    tmp = first->next;
    delete first;
    first = tmp;
  }
  first = NULL;
}
bool String::empty() const { return length() == 0; }
/*! @param n a keresett elem pozíciója
    @return a karakter refernciája */
char &String::operator[](size_t n) { return begin().operator[](n); }
/*! @param n a keresett elem pozíciója
    @return a karakter konstans refernciája */
const char &String::operator[](size_t n) const { return begin().operator[](n); }
/*! @param n a keresett elem pozíciója
    @return a karakter refernciája */
char &String::at(size_t n) { return begin().operator[](n); }
/*! @param n a keresett elem pozíciója
    @return a karakter konstans refernciája */
const char &String::at(size_t n) const { return begin().operator[](n); }

/*! @return konstant karaktersorozat a Stringből */
char *String::c_str() const {
  char *str = new char[size() + 1];
  int i = 0;
  for (Cell *tmp = first; tmp != NULL; tmp = tmp->next) {
    int x = 0;
    while (tmp->data[x] && x < 20)
      str[i++] = tmp->data[x++];
    if (x != 20 && !tmp->data[x])
      break;
  }
  str[i] = 0;
  return str;
}
/*! @param s a hozzáfűzendő String
    @return az objektum refernciája */
String &String::operator+=(const String &s) {
  It i1 = end();
  It i2 = s.begin();
  It ie = s.end();
  Cell *tmp = i1.getCell();
  if (tmp == NULL) {
    *this = s;
  } else {
    while (i2 != ie) {
      if (i1.lastInCell()) {
        tmp->next = new Cell();
        tmp->next->prev = tmp;
        tmp->next->next = NULL;
        tmp = tmp->next;
        i1++;
      }
      *i1 = *i2;
      i1++;
      i2++;
    }
  }
  return *this;
}
/*! @param c a hozzáfűzendő c szerű string
    @return az objektum refernciája */
String &String::operator+=(const char *c) { return *this += String(c); }
/*! @param c a hozzáfűzendő karakter
    @return az objektum refernciája */
String &String::operator+=(const char c) { return *this += String(c); }
/*! @param s a hozzáfűzendő String
    @return az új összefűzött objektum */
String String::operator+(const String &s) const { return String(*this) += s; }
/*! @param c a hozzáfűzendő c szerű string
    @return az új összefűzött objektum */
String String::operator+(const char *c) const { return String(*this) += c; }
/*! @param c a hozzáfűzendő karakter
    @return az új összefűzött objektum */
String String::operator+(const char c) const { return String(*this) += c; }
/*! @param c a hozzáfűzendő c szerű string
    @param s a String objektum
    @return az új összefűzött objektum */
String operator+(const char *c, const String &s) { return s + c; }
/*! @param c a hozzáfűzendő karakter
    @param s a String objektum
    @return az új összefűzött objektum */
String operator+(const char c, const String &s) { return s + c; }

/*! @param os a stream amire kiírja
    @param s a kiírandó String
    @return a stream referenciája */
std::ostream &operator<<(std::ostream &os, const String &s) {
  const char *str = s.c_str();
  os << str;
  delete[] str;
  return os;
}
/*! @param s a vizsgálandó String
    @return igaz, ha megyezik, egyébként hamis */
bool String::operator==(const String &s) const {
  if (this->size() != s.size())
    return false;
  else {
    size_t l = this->size();
    for (size_t i = 0; i < l; i++)
      if (this->operator[](i) != s[i])
        return false;
  }
  return true;
}
/*! @param s a vizsgálandó String
    @return hamis, ha megyezik, egyébként igaz */
bool String::operator!=(const String &s) const { return !(*this == s); }

bool String::operator<(const String &s) const {
  if (*this == s)
    return false;
  bool it = size() > s.size();
  It it1 = it ? begin() : s.begin();
  It it2 = it ? s.begin() : begin();
  It it1e = it ? end() : s.end();
  It it2e = it ? s.end() : end();
  char c = *it2;
  while (it1 != it1e) {
    if ((it && *it1 > c) || (!it && *it1 < c))
      return false;
    if (it2 != it2e) {
      it2++;
      c = *it2;
    } else
      c = 0;
    it1++;
  }
  return true;
}
bool String::operator>(const String &) const {
  if (*this == s)
    return false;
  bool it = size() > s.size();
  It it1 = it ? begin() : s.begin();
  It it2 = it ? s.begin() : begin();
  It it1e = it ? end() : s.end();
  It it2e = it ? s.end() : end();
  char c = *it2;
  while (it1 != it1e) {
    if ((it && *it1 < c) || (!it && *it1 > c))
      return false;
    if (it2 != it2e) {
      it2++;
      c = *it2;
    } else
      c = 0;
    it1++;
  }
  return true;
} // hibás
bool String::operator<=(const String &s) const { return !(*this > s); }
bool String::operator>=(const String &s) const { return !(*this < s); }

/*! @param is a stream amiről beolvasni szeretnénk
    @param s a beolvasás célja
    @return a stream referenciája */
std::istream &operator>>(std::istream &is, String &s) {
  char c;
  String s2;
  while (!isspace(c = char(is.get())))
    s2 + c;
  is.putback(c);
  s = s2;
  return is;
}
/*! @return Iterátor a kezdetére */
It String::begin() const { return It(this, 0, first); }
/*! @return Iterátor a vége után */
It String::end() const {
  It a(this, 0, first);
  while (a.val() != 0)
    a++;
  return a;
}

/*! @param i a másolandó Iterátor
    @return az objektum referenciája */
It &It::operator=(const It &i) {
  parent = i.parent;
  cell = i.cell;
  num = i.num;
  return *this;
}
/*! Az Iterátor a következő elemre vált
    @return az objektum referenciája */
It &It::operator++() {
  if (num == 19) {
    if (cell->next == NULL)
      num = 20;
    else {
      num = 0;
      cell = cell->next;
    }
  } else if (num == 20) {
    if (cell->next == NULL)
      throw "túl az utolsó utánin";
    else {
      cell = cell->next;
      num = 0;
    }
  } else
    num++;
  return *this;
}
/*! Az Iterátor a következő elemre vált
    @return az objektum másolata */
It It::operator++(int) {
  It tmp(*this);
  ++(*this);
  return tmp;
}
/*! @return a mutatott elem refernciája */
char &It::operator*() {
  if (num == 20)
    throw "Túl a végén";
  return cell->data[num];
}
/*! @return a mutatott elem értéke */
char It::val() {
  if (num == 20)
    return 0;
  return cell->data[num];
}
/*! @return a mutatott elem konstans refernciája */
const char &It::operator*() const {
  if (num == 20)
    throw "Túl a végén";
  return cell->data[num];
}
/*! @param pos a relatív pozíció
    @return referencia a kért elemre */
char &It::operator[](size_t pos) {
  Cell *tmp = cell;
  pos += num;
  while (pos >= 20)
    if (tmp->next != NULL) {
      tmp = tmp->next;
      pos -= 20;
    } else
      throw "nincs ilyen indexű elem";
  return tmp->data[pos];
}
/*! @param pos a relatív pozíció
    @return konstans referencia a kért elemre */
char It::operator[](size_t pos) const {
  Cell *tmp = cell;
  pos += num;
  while (pos >= 20)
    if (tmp->next != NULL) {
      tmp = tmp->next;
      pos -= 20;
    } else
      throw "nincs ilyen indexű elem";
  return tmp->data[pos];
}
/*! @param pos a relatív pozíció
    @return referencia a kért elemre */
char &It::operator[](long long pos) {
  Cell *tmp = cell;
  if (pos > 0) {
    pos += num;
    while (pos >= 20)
      if (tmp->next != NULL) {
        tmp = tmp->next;
        pos -= 20;
      } else
        throw "nincs ilyen indexű elem";
  } else if (pos < 0) {
    pos += num;
    pos *= -1;
    while (pos >= 20)
      if (tmp->prev != NULL) {
        tmp = tmp->prev;
        pos -= 20;
      } else
        throw "nincs ilyen indexű elem";
  } else
    return tmp->data[num];
  return tmp->data[pos];
}
/*! @param pos a relatív pozíció
    @return konstans referencia a kért elemre */
char It::operator[](long long pos) const {
  Cell *tmp = cell;
  if (pos > 0) {
    pos += num;
    while (pos >= 20)
      if (tmp->next != NULL) {
        tmp = tmp->next;
        pos -= 20;
      } else
        throw "nincs ilyen indexű elem";
  } else if (pos < 0) {
    pos += num;
    pos *= -1;
    while (pos >= 20)
      if (tmp->prev != NULL) {
        tmp = tmp->prev;
        pos -= 20;
      } else
        throw "nincs ilyen indexű elem";
  } else
    return tmp->data[num];
  return tmp->data[pos];
}
/*! @param rhs a vizsgált Iterátor
    @return igaz, ha megegyezik, egyébként hamis */
bool It::operator==(const Iterator &rhs) const {
  return (cell == rhs.cell && num == rhs.num);
}
/*! @param rhs a vizsgált Iterátor
    @return hamis, ha megegyezik, egyébként igaz */
bool It::operator!=(const Iterator &rhs) const {
  return !(cell == rhs.cell && num == rhs.num);
}
/*! @param rhs a vizsgált Iterátor
    @return igaz, ha a String megegyezik, egyébként hamis */
bool It::operator^(const Iterator &rhs) const {
  return (this->parent == rhs.parent);
}
/*! @param n a szám amivel növelünk
    @return az Iterátor másolata */
It It::operator+(size_t n) {
  Cell *tmp = cell;
  if (n != 0) {
    n += num;
    while (n >= 20)
      if (tmp->next != NULL) {
        tmp = tmp->next;
        n -= 20;
      } else
        throw "túl a határon";
  }
  return It(parent, n, tmp);
}
/*! @param n a szám amivel növelünk
    @return az Iterátor másolata */
It It::operator+(long long n) {
  Cell *tmp = cell;
  if (n != 0) {
    if (n > 0) {
      n += num;
      while (n >= 20)
        if (tmp->next != NULL) {
          tmp = tmp->next;
          n -= 20;
        } else
          throw "túl a határon";
    } else {
      n -= num;
      while (n >= (long long)-20) //
        if (tmp->prev != NULL) {
          tmp = tmp->prev;
          n += 20;
        } else
          throw "túl a határon";
    }
  }
  return It(parent, size_t(n), tmp);
}
/*! @param n a szám amivel növelünk
    @return az Iterátor referenciája */
It &It::operator+=(size_t n) {
  Cell *tmp = cell;
  if (n != 0) {
    n += num;
    while (n >= 20)
      if (tmp->next != NULL) {
        tmp = tmp->next;
        n -= 20;
      } else
        throw "túl a határon";
  }
  cell = tmp;
  num = n;
  return *this;
}
/*! @param n a szám amivel növelünk
    @return az Iterátor referenciája */
It &It::operator+=(long long n) {
  Cell *tmp = cell;
  if (n != 0) {
    if (n > 0) {
      n += num;
      while (n >= 20)
        if (tmp->next != NULL) {
          tmp = tmp->next;
          n -= 20;
        } else
          throw "túl a határon";
    } else {
      n -= num;
      while (n >= -20)
        if (tmp->prev != NULL) {
          tmp = tmp->prev;
          n += 20;
        } else
          throw "túl a határon";
    }
  }
  cell = tmp;
  num = (size_t)n;
  return *this;
}
/*! @param n a szám amivel csökkentünk
    @return az Iterátor másolata */
It It::operator-(size_t n) {
  // hibás
  Cell *tmp = cell;
  if (n != 0) {
    n -= num;
    while (n >= 20)
      if (tmp->prev != NULL) {
        tmp = tmp->prev;
        n -= 20;
      } else
        throw "túl a határon";
  }
  return It(parent, n, tmp);
}

/*! @param n a szám amivel csökkentünk
    @return az Iterátor másolata */
It It::operator-(long long n) { return *this + (-1) * n; }

/*! @param n a szám amivel csökkentünk
    @return az Iterátor referenciája */
It &It::operator-=(size_t n) {
  Cell *tmp = cell;
  if (n != 0) {
    n -= num;
    while (n >= 20)
      if (tmp->prev != NULL) {
        tmp = tmp->prev;
        n -= 20;
      } else
        throw "túl a határon";
  }
  cell = tmp;
  num = n;
  return *this;
}
/*! @param n a szám amivel csökkentünk
    @return az Iterátor referenciája */
It &It::operator-=(long long n) { return *this += (-1) * n; }

/*! @param i a kivont Iterátor
    @return a távolságuk */
size_t It::operator-(Iterator &i) {
  size_t tav = 0;
  if (*this != i) {
    if (*this < i) {
      for (Cell *tmp = cell; tmp != i.cell; cell = cell->next)
        tav += 20;
      tav += num;
      tav -= i.num;
    } else {
      for (Cell *tmp = cell; tmp != i.cell; cell = cell->prev)
        tav += 20;
      tav -= num;
      tav += i.num;
    }
  }
  return tav;
}
/*! @param i az összehasonlítandó Iterátor
    @return igaz, ha i pozíciója nagyobb, hamis ha nem */
bool It::operator<(const Iterator &i) const {
  if (this->parent != i.parent)
    throw "nem ugyanaz a string";
  Cell *tmp = cell;
  if (tmp == i.cell)
    return num < i.num;
  while (tmp != i.cell && tmp != NULL)
    tmp = tmp->next;
  if (tmp == i.cell)
    return true;
  return false;
}
/*! @param i az összehasonlítandó Iterátor
    @return igaz, ha i pozíciója kisebb, hamis ha nem */
bool It::operator>(const Iterator &i) const { return !(*this <= i); }
/*! @param i az összehasonlítandó Iterátor
    @return igaz, ha i pozíciója nagyobb-egyenlő, hamis ha nem */
bool It::operator<=(const Iterator &i) const {
  if (this->parent != i.parent)
    throw "nem ugyanaz a string";
  Cell *tmp = cell;
  if (tmp == i.cell)
    return num <= i.num;
  while (tmp != i.cell && tmp != NULL)
    tmp = tmp->next;
  if (tmp == i.cell)
    return true;
  return false;
}
/*! @param i az összehasonlítandó Iterátor
    @return igaz, ha i pozíciója kisebb-egyenlő, hamis ha nem */
bool It::operator>=(const Iterator &i) const { return !(*this < i); }
/*! @param n a szám amivel növelni akarjuk az Iterátor
    @param i az Iterátor referenciája
    @return az Iterátor másolata */
It operator+(size_t n, It &i) { return i + n; }

//} // namespace NHF
