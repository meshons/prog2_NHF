#include <iostream>
#include <string>

#include "gtest_lite.h"
#include "memtrace.h"
#include "string.hpp"

int main()
{
  TEST(Teszt1, konstruktor)
  {
    char *my = NHF::String("valami").c_str();
    EXPECT_STREQ(std::string("valami").c_str(), my);
    delete[] my;
    my = NHF::String('a').c_str();
    EXPECT_STREQ(std::string("a").c_str(), my);
    delete[] my;
    NHF::String a("valami hosszu");
    my = NHF::String(a.begin(), a.begin() + (size_t)6).c_str();
    EXPECT_STREQ(std::string("valami").c_str(), my);
    delete[] my;
    NHF::String ab("valami hosszu");
    NHF::String b(ab);
    my = b.c_str();
    EXPECT_STREQ(std::string("valami hosszu").c_str(), my);
    delete[] my;
  }
  ENDM

      TEST(Teszt2, basicoperators)
  {
    char *my;
    NHF::String a("valami");
    a = "nem valami";
    my = a.c_str();
    EXPECT_STREQ(std::string("nem valami").c_str(), my);
    delete[] my;
    NHF::String b(" meg valami");
    a = a + b;
    my = a.c_str();
    EXPECT_STREQ("nem valami meg valami", my);
    delete[] my;
    a = a + " haha";
    my = a.c_str();
    EXPECT_STREQ("nem valami meg valami haha", my);
    delete[] my;
    a = "mi " + a;
    my = a.c_str();
    EXPECT_STREQ("mi nem valami meg valami haha", my);
    delete[] my;
    a = a + 'b';
    my = a.c_str();
    EXPECT_STREQ("mi nem valami meg valami hahab", my);
    delete[] my;
    a = 'a' + a;
    my = a.c_str();
    EXPECT_STREQ("ami nem valami meg valami hahab", my);
    delete[] my;
    a += 'a';
    my = a.c_str();
    EXPECT_STREQ("ami nem valami meg valami hahaba", my);
    delete[] my;
    a += "muhaha";
    my = a.c_str();
    EXPECT_STREQ("ami nem valami meg valami hahabamuhaha", my);
    delete[] my;
    a += b;
    my = a.c_str();
    EXPECT_STREQ("ami nem valami meg valami hahabamuhaha meg valami", my);
    delete[] my;
    a = "valami";
    my = a.c_str();
    EXPECT_STREQ("valami", my);
    delete[] my;
    a = 'c';
    my = a.c_str();
    EXPECT_STREQ("c", my);
    delete[] my;
  }
  ENDM

      TEST(Teszt3, elementacces)
  {
    NHF::String a("valami hosszu ami tobb mint 20 karakter");
    EXPECT_EQ('i', a[24]);
    EXPECT_EQ('2', a.at(28));
    a[28] = 'c';
    a.at(24) = 'K';
    EXPECT_EQ('K', a[24]);
    EXPECT_EQ('c', a.at(28));
    char *my = a.c_str();
    EXPECT_STREQ("valami hosszu ami tobb mKnt c0 karakter", my);
    delete[] my;
  }
  ENDM

      TEST(Teszt4, stringlength)
  {
    NHF::String a("valami hosszu ami tobb mint 20 karakter, de tobb is mint 40 egy kicsivel");
    EXPECT_EQ(size_t(73), a.size());
    EXPECT_EQ(size_t(73), a.length());
    EXPECT_EQ(size_t(80), a.capacity());
  }
  ENDM

      return 0;
}
