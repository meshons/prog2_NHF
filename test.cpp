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
    EXPECT_STREQ(my, std::string("valami").c_str());
    delete[] my;
    my = NHF::String('a').c_str();
    EXPECT_STREQ(my, std::string("a").c_str());
    delete[] my;
    NHF::String a("valami hosszu");
    my = NHF::String(a.begin(), a.begin() + (size_t)6).c_str();
    EXPECT_STREQ(my, std::string("valami").c_str());
    delete[] my;
    NHF::String ab("valami hosszu");
    NHF::String b(ab);
    my = b.c_str();
    EXPECT_STREQ(my, std::string("valami hosszu").c_str());
    delete[] my;
  }
  ENDM

      TEST(Teszt2, basicoperators)
  {
    char *my;
    NHF::String a("valami");
    a = "nem valami";
    my = a.c_str();
    EXPECT_STREQ(my, std::string("nem valami").c_str());
    delete[] my;
    NHF::String b(" meg valami");
    a = a + b;
    my = a.c_str();
    EXPECT_STREQ(my, "nem valami meg valami");
    delete[] my;
    a = a + " haha";
    my = a.c_str();
    EXPECT_STREQ(my, "nem valami meg valami haha");
    delete[] my;
    a = "mi " + a;
    my = a.c_str();
    EXPECT_STREQ(my, "mi nem valami meg valami haha");
    delete[] my;
    a = a + 'b';
    my = a.c_str();
    EXPECT_STREQ(my, "mi nem valami meg valami hahab");
    delete[] my;
    a = 'a' + a;
    my = a.c_str();
    EXPECT_STREQ(my, "ami nem valami meg valami hahab");
    delete[] my;
    a += 'a';
    my = a.c_str();
    EXPECT_STREQ(my, "ami nem valami meg valami hahaba");
    delete[] my;
    a += "muhaha";
    my = a.c_str();
    EXPECT_STREQ(my, "ami nem valami meg valami hahabamuhaha");
    delete[] my;
    a += b;
    my = a.c_str();
    EXPECT_STREQ(my, "ami nem valami meg valami hahabamuhaha meg valami");
    delete[] my;
  }
  ENDM

      return 0;
}
