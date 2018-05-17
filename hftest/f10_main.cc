/**
 * foprogram az F10 osztaly kiprobalasahoz.
 * Stork Gabor, NO047V reszere
 * Datum: 2018-02-22 14:36:26
 * Ez az allomany tetszes szerint modosithato
 */

#include <iostream>
#include "f10.h"

using namespace std;

int main() {
  F10 a, c;

  cout << a.ident() << endl;
  cout << a.match("xxa asalakra as \n") << endl;
  for (int i = 0; i < 5; i ++) { 
    F10 b = a;
    cout << b.match(" definialnunk ") << endl;
  }
  F10 b = a;
  a = a;
  c = b;

  cout << c.getLine();
  return 0;
}
