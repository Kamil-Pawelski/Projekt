#include <iostream>
#include "TC.h"
//zrobic do mnożenia jak w dzieleniu czyli przesunac liczbe zeby byla bez przecinka
//wyniki od razu wypisywac  

int main(){

vector<uint8_t> ab = {126}; 
vector<uint8_t> ac = {2}; 
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);    
 //TC::div(a,b)s;

 TC result = TC::sub(a,b);
std::cout << std::endl;
//std::cout << "sub = " << TC::printTC(result);
std::cout << std::endl;
/*result = TC::add(a,b);
std::cout << "add = " << TC::printTC(result);
std::cout << std::endl;
result = TC::mul(a,b);
std::cout << "mul = " << TC::printTC(result);
std::cout << std::endl;
result = TC::mul(a,b);
std::cout << "mul2 = " << TC::printTC(result);
std::cout << std::endl;*/
result = TC::div(a,b);
std::cout << "div = " << TC::printTC(result);
std::cout << std::endl;
return 0;
}
//ZNAKI RÓWNE 1 -
//ZNAKI RÓŻNE 0 +