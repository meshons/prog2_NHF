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
String::String(It begin, It end) {
  Cell *tmp = first, *prev = NULL;
  unsigned int x = 0;
  while (begin != end) {
    if (x % 20 == 0) {
      if (!x)
        first = new Cell();
      else {
        prev = tmp;
        tmp->next = new Cell();
        tmp = tmp->next;
      }
      tmp->prev = prev;
      tmp->next = NULL;
    }
    tmp->data[x % 20] = *begin;
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
  first->data[1] = 0;
  return *this;
}

It String::begin() { return It(this, first); }
const It String::begin() const { return It(this, first); }
It String::end() {
  It a(this, first);
  while (*a != 0)
    a++;
  return a;
}
const It String::end() const {
  It a(this, first);
  while (*a != 0)
    a++;
  return a;
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
  if (num >= 19 && cell->next == NULL)
    throw "Túl a lezáró 0-án";
  else if (num == 20)
    throw "Túl a végén";
  return cell->data[num];
}
const char &It::operator*() const {
  if (num >= 19 && cell->next == NULL)
    throw "Túl a lezáró 0-án";
  else if (num == 20)
    throw "Túl a végén";
  return cell->data[num];
}
char &It::operator[](unsigned int pos) {
  Cell *tmp = cell;
  pos += num;
  while (pos > 20)
    if (tmp->next != NULL) {
      tmp = tmp->next;
      pos -= 20;
    } else
      throw "nincs ilyen indexű elem";
  if (pos == 19 && tmp->next == NULL)
    throw "lezáró nulla nem írható felül";
  return tmp->data[pos];
}
const char &It::operator[](unsigned int pos) const {
  Cell *tmp = cell;
  pos += num;
  while (pos > 20)
    if (tmp->next != NULL) {
      tmp = tmp->next;
      pos -= 20;
    } else
      throw "nincs ilyen indexű elem";
  if (pos == 19 && tmp->next == NULL)
    throw "lezáró nulla nem írható felül";
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
      // todo
    } else {
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
