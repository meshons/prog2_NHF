#include <iostream>
#include <string>

#include "gtest_lite.h"
#include "memtrace.h"
#include "string.hpp"

int main()
{
  TEST(Teszt1, construktor)
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
    EXPECT_EQ(size_t(72), a.size());
    EXPECT_EQ(size_t(72), a.length());
    EXPECT_EQ(size_t(80), a.capacity());
    EXPECT_FALSE(a.empty());
    a.clear();
    EXPECT_TRUE(a.empty());
  }
  ENDM

      TEST(Teszt5, comperators)
  {
    NHF::String a("valami");
    NHF::String b("valami");
    EXPECT_EQ(a, b);
    b += 'c';
    EXPECT_NE(a, b);
    EXPECT_TRUE(a != b);
    EXPECT_TRUE(b > a);
    EXPECT_FALSE(b < a);
    EXPECT_TRUE(b >= a);
    EXPECT_FALSE(b <= a);
    //maybe more
  }
  ENDM

      TEST(Teszt6, persistent)
  {
    std::stringstream ss;
    NHF::String a("valami amiben van szokoz es hosszu, mondjuk 40 feletti");
    a.write(ss);
    EXPECT_STREQ("54;valami amiben van szokoz es hosszu, mondjuk 40 feletti\n", ss.str().c_str());
    a.read(ss);
    char *my = a.c_str();
    EXPECT_STREQ("valami amiben van szokoz es hosszu, mondjuk 40 feletti", my);
    delete[] my;
  }
  ENDM

      TEST(Teszt7, iostream)
  {
    std::stringstream ss;
    NHF::String a("valami amiben van szokoz");
    ss << a;
    EXPECT_STREQ("valami amiben van szokoz", ss.str().c_str());
    ss >> a;
    char *my = a.c_str();
    EXPECT_STREQ("valami", my);
    delete[] my;
  }
  ENDM

      //iteratortests

      TEST(Teszt8, iteratorconstructor)
  {
  }
  ENDM

      return 0;
}
