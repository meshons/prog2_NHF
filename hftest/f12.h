/*
 * f12.h
 * Stork Gabor, NO047V reszere
 * Datum: 2018-02-22 09:26:18
 * NE modositsa ezt az allmomanyt! 
 */


#ifndef F12_H
#define F12_H

#include <deque>
#include <stdexcept>		// kivetelkezeleshez kell

/**
 * Queue osztaly 
 */
class Queue {
  std::deque<char> q;
public:  
  typedef std::deque<char>::iterator myIterator;
  // Konstruktor nullaval lezart tringre mutato pointerrel
  // Letrehozza a sort
  Queue(const char *p = 0);

  // A sor vegere tesz egy karaktert
  void push_back(const char c) { 
     q.push_back(c); // visszavezetjuk a tarolo muveletere
  }

  // Kiveszi a sorbol a legutolso karaktert es visszadja azt.
  // ha a sor ures underflow_error() kivetelt dob.
  //                  throw std::underflow_error("Empty");  
  char pop_back();

  // A sor elejere tesz egy karaktert
  void push_front(const char c);

  // Kiveszi a sorbol a legelso karaktert es visszadja azt.
  // ha a sor ures underflow_error() kivetelt dob.
  //                  throw std::underflow_error("Empty");  
  char pop_front();

  // true, ha ures a sor
  bool empty();

  // tarolt karakterek szamat adja
  int size() {
    return q.size(); // visszavezetjuk a tarolo muveletere
  } 

  // Letrehoz egy iteratort es a sor elejere allitja
  myIterator begin();

  // Letrehoz egy iteratort es a sor vegere allitja
  myIterator end();
};

/**
 * F2 osztaly 
 */
class F2 {
public:  
  // A hftest elso azonositosoranak cimere mutat.
  static const char *myId;

  // hftest 2. feladatanak fuggvenye:
  //    f(X) = X/99.65, ha X > 14,
  //    f(X) = 0.389*X^4 - 0.777*X^3 + 49.75*X^2 + 14*X - 14, ha X <= 14
  double f(double) const;
};


/**
 * F12 osztaly
 * Ket arca van: F2 es Queue
 */
class F12 :public Queue, public F2 {
public:
   // Konstruktor, hogy kozvetlenul lehessen inicializalni a sort
   F12(const char *p = 0):Queue(p) {}   

   // A tobbi tagfuggveny publikusan oroklodik
   // A masolo kontruktor az osok megfelelo kontruktore lesz. 
   // Az ertekadas is az osok megfelelo fuggvenye lesz.
   // Igy ha azok jol mukodnek, akkor itt is jol fognak.
};

#endif

