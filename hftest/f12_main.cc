/**
 * foprogram az F12 osztaly kiprobalasahoz.
 * Stork Gabor, NO047V reszere
 * Datum: 2018-02-22 09:26:18
 * Ez az allomany tetszes szerint modosithato
 */

#include <iostream>
#include "f12.h"

using namespace std;

/*
 * F2 interfeszt varunk
 */ 
void solveF2(const F2& f2) {
  cout << f2.myId << endl;
  cout << "Feladat = 2" << endl;

  double d;
  while (cin >> d) 
    cout << f2.f(d) << endl;
}

/*
 * Queue interfeszt varunk
 */ 
void printQ(Queue& t) {
  for (Queue::myIterator i1 = t.begin(); i1 != t.end(); ) 
     std::cout << *i1++;
}


int main() {
  F12 s0;
  F12 s1("it sutsz kis szucs");
  F12 s2 = s1;

 
  try {
    s2.push_back('?');
    s2.push_back('\n');
    s2.push_front('M');

    cout << "2. feladat tesztelese. double olvasas EOF-ig:" << endl;
    solveF2(s1);

    printQ(s2);

    while (1) s1.pop_front();
    
  } catch (underflow_error e) {
    cout << "undeflow_error: " << e.what() << endl;
  }

  return 0;
}
