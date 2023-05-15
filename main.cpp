#include <iostream>
#include "TC.h"
/*Notka na później żeby nie zapomnieć
zrobić w dodawaniu odejmowanie i dzieleniu aby przód usuwać jak nie potrzebny
*/
extern "C" void vectorDiv( uint8_t *a, uint8_t *b, uint8_t *c);

int main(){

vector <uint8_t> ab = {9};
vector<uint8_t> ac = {2};
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,-8);


TC::div(a,b);
std::cout << std::endl;

 TC sub = TC::sub(a,b);





std::cout << std::endl;

std::cout << "SUB = ";
TC::printTC(sub);
std::cout << std::endl;
	sub = TC::sub(sub,b);
    std::cout << "SUB = ";
TC::printTC(sub);
std::cout << std::endl;
return 0;
}
