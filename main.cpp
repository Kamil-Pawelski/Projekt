#include <iostream>
#include "TC.h"

extern "C" void vectorDiv( uint8_t *a, uint8_t *b, uint8_t *c);

int main(){

vector <uint8_t> ab = {0b10000100}; //126
vector<uint8_t> ac = {0b00000010};
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);
TC add = TC::add(a,b);

 TC sub = TC::mul(a,b);

//TC::div(a,b);
std::cout << std::endl;


//TC add = TC::add(a,b);

std::cout << std::endl;
std::cout << "add = ";
//TC::printTC(add);
std::cout << std::endl;

std::cout << "mul = ";
TC::printTC(sub);
std::cout << std::endl;

TC::printTC(sub);
std::cout << std::endl;
return 0;
}
