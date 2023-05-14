#include <iostream>
#include "TC.h"
/*Notka na później żeby nie zapomnieć
zrobić w dodawaniu odejmowanie i dzieleniu aby przód usuwać jak nie potrzebny
*/
extern "C" void vectorDiv( uint8_t *a, uint8_t *b, uint8_t *c);

int main(){

vector <uint8_t> ab = {4,0};
vector<uint8_t> ac = {1};
 uint8_t result = 0;
 std::cout << std::endl;
 TC a(ab,0);
 TC b(ac,0);


 TC mul = TC::sub(a,b);

  mul = TC::sub(mul,b);
 std::cout << "MULa = ";

TC::printTC(mul);   
std::cout << std::endl;




//std::cout << "SUB = ";
//TC::printTC(sub);
std::cout << std::endl;
	

return 0;
}
