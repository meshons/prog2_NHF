#include "string.hpp"

namespace NHF {

typedef String::Iterator It;

inline static void copy(char *to, char *from) {
  for (int i = 0; i < 20; i++)
    to[i] = from[i];
}

String::String() { first = NULL; }

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
String::String(char c) {
  first = new Cell();
  first->data[0] = c;
}
String::String(It begin, It end) {
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

String::~String() {
  Cell *tmp = first;
  while (first != NULL) {
    tmp = first->next;
    delete first;
    first = tmp;
  }
}
void String::print(std::ostream &os) { os << *this; }
void String::read(std::istream &is) { is >> *this; }

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
String &String::operator=(char c) {
  clear();
  first = new Cell();
  first->prev = NULL;
  first->next = NULL;
  first->data[0] = c;
  // first->data[1] = 0;
  return *this;
}

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
char &String::operator[](unsigned int n) { return begin().operator[](n); }
const char &String::operator[](unsigned int n) const {
  return begin().operator[](n);
}

char &String::at(unsigned int n) { return begin().operator[](n); }
const char &String::at(unsigned int n) const { return begin().operator[](n); }

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

String &String::operator+=(const String &s) {
  It i1 = end();
  It i2 = s.begin();
  It ie = s.end();
  Cell *tmp = first;
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
  return *this;
}
String &String::operator+=(const char *c) { return *this += String(c); }
String &String::operator+=(const char c) { return *this += String(c); }

String String::operator+(const String &s) const { return String(*this) += s; }
String String::operator+(const char *c) const { return String(*this) += c; }
String String::operator+(const char c) const { return String(*this) += c; }
String operator+(const char *c, const String &s) { return s + c; }
String operator+(const char c, const String &s) { return s + c; }

std::ostream &operator<<(std::ostream &os, String &s) {
  const char *str = s.c_str();
  os << str;
  delete[] str;
  return os;
}

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

std::istream &operator>>(std::istream &is, String &s) {
  char c;
  while (!isspace(c = is.get()))
    s + c;
  is.putback(c);
  return is;
}

It String::begin() const { return It(this, first); }
It String::end() const {
  It a(this, first);
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
  return It(parent, tmp, n);
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
