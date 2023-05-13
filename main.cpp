#include <iostream>
#include "TC.h"
extern "C" void vectorDiv(uint8_t* a, uint8_t* b,uint8_t* w, unsigned int c, unsigned int ca); //tu potem zeby pierwsza dodac i druga odjac od razu

int main(){

vector <uint8_t> ab = {0b10001000};
vector<uint8_t> ac = {0b10001000};
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);
 TC add = TC::add(a,b);
 TC sub = TC::sub(a,b);
 std::cout << (int)ab[0] <<std::endl;

 //vectorSub(&ab[0], &ac[0], 0, 0);
 //TC mul = TC::mul(a,b);
 
TC::printTC(sub);
std::cout << std::endl;
TC::printTC(add);
std::cout << std::endl;

std::cout << (int)ab[0] <<std::endl;

//TC::printTC(mul);	
std::cout << std::endl;

return 0;
}
