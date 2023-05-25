#include <iostream>
#include "TC.h"

int main(){

vector<uint8_t> ab = {0b11111111,0b10000010}; 
vector<uint8_t> ac = {1}; 
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,-8);
 TC b(ac,0);
 //TC::div(a,b);
// TC mul = TC::mul(a,b);
 //TC sub = TC::sub(a,b);
 TC add = TC::sub(a,b);

std::cout << std::endl;
std::cout << "add = ";
TC::printTC(add);
std::cout << std::endl;

std::cout << "sub = ";
//TC::printTC(sub);
std::cout << std::endl;

std::cout << "mul = ";
//TC::printTC(mul);
std::cout << std::endl;
return 0;
}
