#include <iostream>
#include "TC.h"
//zrobic do mnożenia jak w dzieleniu czyli przesunac liczbe zeby byla bez przecinka
//wyniki od razu wypisywac  
int main(){

vector<uint8_t> ab = {1,0b10000010}; 
vector<uint8_t> ac = {1}; 
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);    
 //TC::div(a,b);
 TC mul = TC::mul(a,b);
 TC sub = TC::sub(a,b);
 TC add = TC::add(a,b);

std::cout << std::endl;
std::cout << "add = ";
TC::printTC(add);
std::cout << std::endl;

std::cout << "sub = ";
TC::printTC(sub);
std::cout << std::endl;

std::cout << "mul = ";
TC::printTC(mul);
std::cout << std::endl;
return 0;
}
