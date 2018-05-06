#include <iostream>

#include "string.hpp"

using namespace NHF;

void Teszt_konstruktor() {
  try {
    String s1;
    String s2("val ami");
    String s3('c');
    String s4(s2);
    String *s5 = new String(s4);
    String s6(s2.begin(), s2.end());
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;
    std::cout << *s5 << std::endl;
    std::cout << s6 << std::endl;
  } catch (const char *s) {
    std::cout << s << std::endl;
  }
}

int main() {
  Teszt_konstruktor();
  String s2 = "Kecske ";
  String s3 = "hazi";
  std::cout << s2 + s3 << std::endl;
  return 0;
}
