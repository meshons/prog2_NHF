#include "string.hpp"

namespace NHF {

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
  os.write(c_str(), size());
  os.write("\n", 1);
}
/*! @param is a bemeneti stream */
void String::read(std::istream &is) {
  size_t len;
  (is >> len).ignore(1);
  char *p = new char[len + 1];
  is.read(p, len).ignore(1);
  p[len] = 0;
  *this = String(p);
  delete[] p;
}
/*! @param s a másolandó String
    @return az objektum referenciája */
String &String::operator=(const String &s) {
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
    int x = 0;
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
    int x = 0;
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
  Cell *tmp = first;
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
char &String::operator[](unsigned int n) { return begin().operator[](n); }
/*! @param n a keresett elem pozíciója
    @return a karakter konstans refernciája */
const char &String::operator[](unsigned int n) const {
  return begin().operator[](n);
}
/*! @param n a keresett elem pozíciója
    @return a karakter refernciája */
char &String::at(unsigned int n) { return begin().operator[](n); }
/*! @param n a keresett elem pozíciója
    @return a karakter konstans refernciája */
const char &String::at(unsigned int n) const { return begin().operator[](n); }

/*! @return konstant karaktersorozat a Stringből */
const char *String::c_str() const {
  char *str = new char[size() + 1];
  int i = 0;
  for (Cell *tmp = first; tmp != NULL; tmp = tmp->next) {
    int x = 0;
    while (tmp->data[x] && x < 20)
      str[i++] = tmp->data[x++];
    if (!tmp->data[x])
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
  Cell *tmp = first;
  if (tmp == NULL) {
    *this = s;
  } else {
    while (i2 != ie) {
      if (i1.lastInCell()) {
        tmp->next = new Cell();
        tmp->next->prev = tmp;
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
    int l = this->size();
    for (int i = 0; i < l; i++)
      if (this->operator[](i) != s[i])
        return false;
  }
  return true;
}
/*! @param s a vizsgálandó String
    @return hamis, ha megyezik, egyébként igaz */
bool String::operator!=(const String &s) const { return !(*this == s); }

bool String::operator<(const String &s) const {
  // hibás
  if (s.size() == this->size()) {
    int bl = s.size();
    int eq = 0;
    for (int i = 0; i < bl; i++)
      if (this->operator[](i) == s[i])
        eq++;
      else if (this->operator[](i) > s[i])
        return false;
    if (eq == bl)
      return false;
  } else
    return false;
  return true;
}
bool String::operator>(const String &s) const { return true; } // hibás
bool String::operator<=(const String &s) const { return !(*this > s); }
bool String::operator>=(const String &s) const { return !(*this < s); }

/*! @param is a stream amiről beolvasni szeretnénk
    @param s a beolvasás célja
    @return a stream referenciája */
std::istream &operator>>(std::istream &is, String &s) {
  char c;
  String s2;
  while (!isspace(c = is.get()))
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

It &It::operator=(const It &i) {
  cell = i.cell;
  num = i.num;
  return *this;
}

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

It It::operator++(int) {
  It tmp(*this);
  ++(*this);
  return tmp;
}

char &It::operator*() {
  if (num == 20)
    throw "Túl a végén";
  return cell->data[num];
}
char It::val() {
  if (num == 20)
    return 0;
  return cell->data[num];
}
const char &It::operator*() const {
  if (num == 20)
    throw "Túl a végén";
  return cell->data[num];
}

char &It::operator[](unsigned int pos) {
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
const char &It::operator[](unsigned int pos) const {
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
bool It::operator==(const Iterator &rhs) const {
  return (cell == rhs.cell && num == rhs.num);
}
bool It::operator!=(const Iterator &rhs) const {
  return !(cell == rhs.cell && num == rhs.num);
}

bool It::operator^(const Iterator &rhs) const {
  return (this->parent == rhs.parent);
}

It It::operator+(int n) {
  Cell *tmp = cell;
  if (n != 0) {
    if (n > 0) {
      n += num;
      while (n > 20)
        if (tmp->next != NULL) {
          tmp = tmp->next;
          n -= 20;
        } else
          throw "túl a határon";
    } else {
      n -= num;
      while (n > -20)
        if (tmp->prev != NULL) {
          tmp = tmp->prev;
          n += 20;
        } else
          throw "túl a határon";
    }
  }
  return It(parent, n, tmp);
}
It &It::operator+=(int n) {
  Cell *tmp = cell;
  if (n != 0) {
    if (n > 0) {
      n += num;
      while (n > 20)
        if (tmp->next != NULL) {
          tmp = tmp->next;
          n -= 20;
        } else
          throw "túl a határon";
    } else {
      n -= num;
      while (n > -20)
        if (tmp->prev != NULL) {
          tmp = tmp->prev;
          n += 20;
        } else
          throw "túl a határon";
    }
  }
  cell = tmp;
  num = n;
  return *this;
}

It It::operator-(int n) { return *this + (-1 * n); }
It &It::operator-=(int n) { return *this += (-1 * n); }

int It::operator-(Iterator &i) {
  int tav = 0;
  if (*this != i) {
    if (*this < i) {
      for (Cell *tmp = cell; tmp != i.cell; cell = cell->next)
        tav -= 20;
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
bool It::operator>(const Iterator &i) const { return !(*this < i); }

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
bool It::operator>=(const Iterator &i) const { return !(*this <= i); }

It operator+(int n, It &i) { return i + n; }

} // namespace NHF
