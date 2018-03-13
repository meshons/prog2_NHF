#include <iostream>

#include "string.hpp"

using namespace NHF;

int main(){
    String a;
    String s("valamiamihosszuszovegmuahahahahahashashashdhasdhasdhahsdhasdhashdashd");
    String b = s;
    std::cout << s.length() << std::endl;
    std::cout << s.size() << std::endl;
    std::cout << s.capacity() << std::endl;
    s.clear();
    std::cout << s.length() << std::endl;
    std::cout << s.size() << std::endl;
    std::cout << s.capacity() << std::endl;
    return 0;
}