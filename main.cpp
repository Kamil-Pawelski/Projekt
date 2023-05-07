#include <iostream>
#include "TC.h"
extern "C" void vectorDiv(uint8_t* a, uint8_t* b,uint8_t* w, unsigned int c, unsigned int ca); //tu potem zeby pierwsza dodac i druga odjac od razu

int main(){

 vector <uint8_t> ab = {163};
vector<uint8_t> ac = {254};
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);
 TC sum = TC::sub(a,b);
TC::printTC(sum);
 std::cout << "------------------------------------------" << std::endl;
	
return 0;
}
