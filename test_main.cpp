#include <iostream>

#include "memtrace.h"
#include "string.hpp"

using namespace NHF;
void Teszt_konstruktor();

void Teszt_konstruktor()
{
  try
  {
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
    delete s5;
  }
  catch (const char *s)
  {
    std::cout << s << std::endl;
  }
}

int main()
{
  try
  {
    Teszt_konstruktor();
    String s2 = "20-nal nagyobb cuccot probalok beleírni nemtudom miert ";
    String s3 = "hazi 20nal nagyobb cuccal megy e roli kedveert";
    std::cout << s2 + s3 << std::endl;
    s2 += s3;
    std::cout << s2 << std::endl;
    s2 += s2;
    std::cout << s2 << std::endl;
    String s4 = "valami ";
    String s5 = "x";
    s4 = s4 + s4;
    std::cout << s4 << std ::endl;
    s4.write(std::cout);
    String::Iterator it = s2.end();
    std::cout << *(it - (long long)80) << std::endl;
    s2 += "valami";
    s2 += 'c';
    s2[10] = 'c';
    std::cout << s2 << std::endl;
    String s6;
    s6.read(std::cin);
    std::cout << s6 << std::endl;
  }
  catch (const char *str)
  {
    std::cout << str << std::endl;
  }
  return 0;
}
