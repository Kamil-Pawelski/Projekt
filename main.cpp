#include <iostream>
#include "TC.h"

extern "C" void vectorDiv( uint8_t *a, uint8_t *b, uint8_t *c);

int main(){

vector <uint8_t> ab = {130}; //126
vector<uint8_t> ac = {4};
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);


TC::div(a,b);
std::cout << std::endl;

 TC sub = TC::add(a,b);


//TC add = TC::add(a,b);

std::cout << std::endl;

std::cout << "SUB = ";
TC::printTC(sub);
std::cout << std::endl;

TC::printTC(sub);
std::cout << std::endl;
return 0;
}
