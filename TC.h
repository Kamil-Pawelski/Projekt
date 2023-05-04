#ifndef TC_H_
#define TC_H_
#include<iostream>
#include <algorithm>

#include<vector>

extern "C" void vectorAdd(uint8_t* a, uint8_t* b, unsigned int c);
extern "C" void vectorSub(uint8_t* a, uint8_t* b, unsigned int c);


using std::vector;

class TC {
private:
    vector<uint8_t> _number;
    
    static void setNegative(uint8_t& byt, int n); //ustawia reszte bitów na 1 w liczbie (00000001) -> (11111111) tylko w wypadku jak jest ujemna

public:
    int _position;
    TC();
    TC(vector<uint8_t>& number, int position);
    static vector<uint8_t> getNumber(TC number);
    static bool isNumberZero(TC number); //sprawdza czy zero
    static uint8_t rightShift(const uint8_t& number, int n); // Zobaczymy może dam do prywatnych? //przesunięcia
    static uint8_t leftShift(const uint8_t& number, int n); // tak samo jak wyżej
    static void printTC(TC& number);
    static void negateBits(TC& number);
    static TC add(TC& number1, TC& number2);
    static TC sub(TC& number1, TC& number2);

};
#endif