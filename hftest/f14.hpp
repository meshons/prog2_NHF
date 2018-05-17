#ifndef F14_H
#define F14_H

#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>


template <typename T> class F14 {
  T *v;
  int cap, used;

public:
  typedef T *iterator;
  F14(int n = 20) {
    v = new T[n];
    cap = n;
    used = 0;
  }
  F14(int n, T c) {
    v = new T[n];
    cap = n;
    used = n;
    for (int i = 0; i < n; i++)
      v[i] = c;
  }
  F14(T *b, T *e) {
    int size = (e - b); // / sizeof(T);
    cap = size;
    used = size;
    v = new T[size];
    int i;
    for (i = 0; i < size; i++)
      v[i] = b[i];
  }
  ~F14() { delete[] v; }

  T *begin() {
    if (!used)
      throw std::out_of_range("out_of_range");
    return v;
  }
  T *end() {
    if (!used)
      throw std::out_of_range("out_of_range");
    // if (used == cap)
    //    inc();
    return v + used;
  }

  void inc(int n = 10) {
    T *v2 = new T[cap + n];
    cap += n;
    for (int i = 0; i < cap; i++)
      v2[i] = v[i];

    delete[] v;
    v = v2;
  }
  void dec(int n = 10) {
    T *v2 = new T[cap - 10];
    cap -= n;
    for (int i; i < cap; i++)
      v2[i] = v[i];

    delete[] v;
    v = v2;
  }

  T &back() {
    if (used < 0)
      throw std::out_of_range("out_of_range");
    return v[used == 0 ? used : used - 1];
  }
  T back2() {
    if (used < 0)
      throw std::out_of_range("out_of_range");
    return v[used == 0 ? used : used - 1];
  }
  T &front() { return v[0]; }
  void push_back(T c) {
    if (used == cap)
      inc();
    v[used++] = c;
  }
  void pop_back() {
    if (used <= 0)
      throw std::out_of_range("out_of_range");
    // v[used-1] = 0;
    used--;
    // if (used < (cap - 15))  dec();
  }
  T get_back() {
    T s = back2();
    pop_back();
    return s;
  }
  void resize(int size) {
    if (size < cap) {
      T *ujv = new T[size];
      for (int i = 0; i < size; i++)
        ujv[i] = v[i];
      delete[] v;
      v = ujv;
      used = (used > size ? size : used);
      cap = size;
    } else if (size > cap) {
      T *ujv = new T[size];
      for (int i = 0; i < used; i++)
        ujv[i] = v[i];
      delete[] v;
      v = ujv;
      cap = size;
    }
  }
  void resize(int size, T val) {
    delete[] v;
    v = new T[size];
    for (int i = 0; i < size; i++)
      v[i] = val;
    used = size;
    cap = size;
  }
};

template <> int F14<int>::get_back() {
  int s = back() - 14;
  pop_back();
  // pop_back();
  return s;
}

template <> std::string F14<std::string>::get_back() {
  return "Stork Gabor,1MI,IMSC3,L3p <storkgaborka98@gmail.com> NO047V";
}

template <typename T> class osFunctor {
  std::ostream &o;
  char s[10];

public:
  osFunctor(std::ostream &os = std::cout, const char *str = "") : o(os) {
    int i = 0;
    while (str[i] && i < 10) {
      s[i] = str[i];
      i++;
    }
    s[i] = 0;
  }

  void operator()(T &a) { o << a << s; }
  ~osFunctor() {}
};

#endif