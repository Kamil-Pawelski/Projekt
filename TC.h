#ifndef TC_H_
#define TC_H_
#include<iostream>
#include <algorithm>
#include <string> 
#include<vector>

extern "C" void vectorAdd(uint8_t * a, uint8_t * b, unsigned int c);
extern "C" void vectorSub(uint8_t * a, uint8_t * b, unsigned int c);
extern "C" void vectorMul(uint8_t * a, uint8_t * b, uint8_t * c, unsigned int d, unsigned int e);


using std::vector;

class TC {
private:
    vector<uint8_t> _number;
    int _position;
    static void setNegative(uint8_t& byt, int n);
    static bool isNegativeBigger(TC a, TC b, unsigned int c, unsigned int d); //do usuniecia
    static void printVector(const vector<uint8_t>& number);

public:

    TC();
    TC(vector<uint8_t>& number, int position);
    static vector<uint8_t> getNumber(TC number);
    static bool isNumberZero(TC number);
    static uint8_t rightShift(const uint8_t& number, int n);
    static uint8_t leftShift(const uint8_t& number, int n);
    static std::string printTC(TC number);
    static void negateBits(TC& number);
    static void negateIntegerBits(TC& number);
    static TC add(TC number1, TC number2);
    static TC sub(TC number1, TC number2);
    static TC mul(TC number1, TC number2);
    static void div(TC number1, TC number2);
    static void changeIndex(int& a, int& b);
    static void changeIndex2(int& a);
    static void shiftDiv(vector<uint8_t>& a, uint8_t& b);
    TC& operator=(const TC& other) {
        _number = other._number;
        _position = other._position;
        return *this;
    }

};
#endif