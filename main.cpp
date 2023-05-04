#include <iostream>
#include "TC.h"
int main(){
	 vector<uint8_t> firstNumber = {0x12, 0x7e, 0x60};
     vector<uint8_t> secondNumber = {0xf0, 0xfa, 0xfb, 0x6e};

	
	TC numb1(firstNumber, 0);
	TC numb2(secondNumber, -8);
	TC::printTC(numb2);
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

	std::cout << std::endl;std::cout << std::endl;
	std::cout <<"XD" << " " << numb3._position <<std::endl;
	std::cout << std::endl;
	TC::printTC(numb3);
	vector<uint8_t> numb33 = TC::getNumber(numb3);
	std::cout << std::endl;
	for(int i = 0; i < 6; i++){
		std::cout << (int)numb33[i] << std::endl;
	}

	TC numb4 = TC::add(numb1, numb2);
	TC::printTC(numb4);
	vector<uint8_t> numb334 = TC::getNumber(numb3);
	std::cout << std::endl;
	for(int i = 0; i < 5; i++){
		std::cout << (int)numb334[i] << std::endl;
	}

	
	std::cout << std::endl;
	uint8_t ba[2] = {0,24};
	uint8_t cd[2] ={0, 22};
	vectorSub(&cd[0], &ba[0], 1);
	
	vector<uint8_t> firstNumber1 = {12, 132, 13};
    vector<uint8_t> secondNumber2 = {20, 12, 2, 12};
	vector<uint8_t> aaaaa = {0,0,0,0,0,0};

	vectorAdd(&aaaaa[1], &firstNumber1[0], firstNumber1.size() - 1);
	std::cout << (int) aaaaa[0]<< std::endl << (int) aaaaa[1]<< std::endl <<  (int)aaaaa[2]<< std::endl <<  (int) aaaaa[3]<< std::endl<<  (int) aaaaa[4] << std::endl<<  (int) aaaaa[5] << std::endl;
	std::cout << std::endl;

	vectorSub(&aaaaa[2], &secondNumber2[0], secondNumber2.size() - 1);

	std::cout << (int) aaaaa[0]<< std::endl << (int) aaaaa[1]<< std::endl <<  (int)aaaaa[2]<< std::endl <<  (int) aaaaa[3]<< std::endl<<  (int) aaaaa[4] << std::endl<<  (int) aaaaa[5] << std::endl;

return 0;
}
