#include <iostream>
#include "TC.h"
int main(){
	 vector<uint8_t> firstNumber = {0x12, 0x7e, 0x60};
     vector<uint8_t> secondNumber = {0x20, 0x3a, 0x2b, 0x6e};

	TC numb1(firstNumber, 0);
	TC numb2(secondNumber, -8);
	vector<uint8_t> numb32 = TC::getNumber(numb2);
		std::cout << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < numb32.size(); i++){
		std::cout << (int)numb32[i] << std::endl;
	}
		std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	TC numb3 = TC::add(numb1, numb2);
	TC::printTC(numb3);
	vector<uint8_t> numb33 = TC::getNumber(numb3);
	std::cout << std::endl;
	for(int i = 0; i < 5; i++){
		std::cout << (int)numb33[i] << std::endl;
	}
return 0;
}
