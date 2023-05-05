#include <iostream>
#include "TC.h"
int main(){

	 vector<uint8_t> a = {0x12, 0x34, 0x56, 0x78};
   vector<uint8_t> b = {0x11, 0x22, 0x33};
    TC na(a, -8);
    TC ba(b, 0);
    TC mull = TC::mul(na,ba);
    TC::printTC(mull);
    std::cout << std::endl << mull._position << std::endl;
     vector<uint8_t> c(7);
          vector<uint8_t> e(7);

 uint8_t ab = 2;
 uint8_t ac = 2;
 vector<uint8_t> d = TC::getNumber(mull);
   

 for(int i = b.size()-1; i >= 0; i--)
  vectorMul(&a[0], &b[i], &c[0], a.size(), i +1);


 for(int i = b.size()-1; i >= 0; i--)
  vectorMul(&a[0], &b[i], &e[0], a.size(), i +1);
  for (auto i : c) {
    std::cout << std::hex << (int)i << " ";
  }
    std::cout << std::endl;
  for (auto i : d) {
    std::cout << std::hex << (int)i << " ";
  }
    std::cout << std::endl;
  for (auto i : e) {
    std::cout << std::hex << (int)i << " ";
  }
  std::cout << std::endl;
 std::cout << int(ab) << std::endl;
return 0;
}
