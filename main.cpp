#include <iostream>
#include "TC.h"
//zrobic do mnożenia jak w dzieleniu czyli przesunac liczbe zeby byla bez przecinka
//wyniki od razu wypisywac  
int main(){

vector<uint8_t> ab = {0b11111111,0b11111101}; 
vector<uint8_t> ac = {0b11111111}; 
 std::cout << std::endl;
 TC a(ab, -8);
 TC b(ac,0);    
 //TC::div(a,b)s;
 std::cout << TC::printTC(b);
 std::cout << std::endl;
 //TC::negateIntegerBits(b);
 std::cout << TC::printTC(b);
 TC result = TC::sub(a,b);
std::cout << std::endl;
std::cout << "sub = " << TC::printTC(result);
std::cout << std::endl;
result = TC::add(a,b);
std::cout << "add = " << TC::printTC(result);
std::cout << std::endl;
result = TC::mul(a,b);
std::cout << "mul = " << TC::printTC(result);
std::cout << std::endl;
result = TC::mul(a,b);
std::cout << "mul2 = " << TC::printTC(result);
std::cout << std::endl;
return 0;
}
