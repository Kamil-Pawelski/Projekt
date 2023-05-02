#include "TC.h"
/// <summary>
/// Konstruktor domyślny
/// </summary>
TC::TC() { 
    _number.push_back(0);
    _position = 0;
}


bool TC::isNumberZero(TC number){
    for (const auto& el : number._number)
    {  
        if(el != 0) return false;
    }
    return true;
}
/// <summary>
/// Konstruktor
/// </summary>
/// <param name="number">Nasza liczba</param>
/// <param name="position">Pozycja najmniej znaczącego bitu</param>
TC::TC(vector<uint8_t>& number, int position) {

    if (position % 8 != 0) {
        uint8_t shiftR;
        uint8_t shiftL;
        int fract = position - 1 + number.size() * 8;
        vector<uint8_t> shiftNumber(number.size() + 1);
        if (position < 0) { // wypadek gdy pozycja jest ujemna
            shiftR = -position % 8;
            shiftL = 8 - shiftR;
            for (int i = number.size(); i > 0; i--) {
                shiftNumber[i] ^= TC::leftShift(number[i - 1], shiftL);
                shiftNumber[i - 1] ^= TC::rightShift(number[i - 1], shiftR);
            }
            if (number[0] > 127 && fract > 0) {
                setNegative(shiftNumber[0], shiftR);
            } 
        }
        else {
            shiftL = position % 8;
            shiftR = 8 - shiftL;
            for (int i = number.size(); i > 0; i--) {
                shiftNumber[i] ^= TC::leftShift(number[i - 1], shiftL);
                shiftNumber[i - 1] ^= TC::rightShift(number[i - 1], shiftR);
            }
            if (number[0] > 127 && fract > 0) {
                setNegative(shiftNumber[0], shiftR);
            }
        }
        _number = shiftNumber;
        _position = position;
    }
    else {
        _number = number;
        _position = position;
    }
}
/// <summary>
/// Przesunięcie bajta o n pozycji w prawo
/// </summary>
/// <param name="number">Liczba do przesunięcia</param>
/// <param name="n">Określa o ile przesuniemy</param>
/// <returns></returns>
uint8_t TC::rightShift(const uint8_t& number, int n)
{
    return number >> n; //przeuniecie liczby o n miejsc w prawo
}
/// <summary>
/// Przesunięcie bajta o n pozycji w lewo
/// </summary>
/// <param name="number">Liczba do przesunięcia</param>
/// <param name="n">Określa o ile przesuniemy</param>
/// <returns></returns>
uint8_t TC::leftShift(const uint8_t& number, int n)
{
    return number << n; //przeuniecie liczby o n miejsc w lewo
}

/// <summary>
/// W przypadku ujemnej liczby w niektórych sytuacjach zamienia bity z 0 na 1
/// </summary>
/// <param name="byt">Liczba do zamiany</param>
/// <param name="n">Liczba 1 do dopisania</param>
void TC::setNegative(uint8_t& number, int n)
{
    switch (n) {
    case 1:
        number ^= 0b10000000;
        return;
    case 2:
        number ^= 0b11000000;
        return;
    case 3:
        number ^= 0b11100000;
        return;
    case 4:
        number ^= 0b11110000;
        return;
    case 5:
        number ^= 0b11111000;
        return;
    case 6:
        number ^= 0b11111100;
        return;
    case 7:
        number ^= 0b11111110;
        return;
    }
}



/// <summary>
/// Wypisuje naszą liczbę w U2
/// </summary>
/// <param name="number">Liczba do wypisania</param>
void TC::printTC(TC& number)
{
    if (number._position >= 0) { //dla pozycji nieujemnych
        for (int i = 0; i < number._number.size(); i++) {
            for (int j = 7; j >= 0; j--) {
                std::cout << ((number._number[i] >> j) & 1);
            }
        }
    }
    else{  //pozycja ujemna
        int comma;
        int size = number._number.size() * 8 - 8 + number._position;
        if ( size < 0) { //warunki gdy najstarszy bit jest na ujemnej
            comma = number._position + number._number.size() * 8;
            if (number._position % 8 == 0) { //gdy  jest co pełny bajt 

                if (comma == 0) {
                    std::cout << 0;
                }
                for (int i = 0; i < number._number.size(); i++) {
                    for (int j = 7; j >= 0; j--) {
                        if (comma == 0) {
                            std::cout << ',';
                        }
                        std::cout << ((number._number[i] >> j) & 1);
                        comma--;
                    }

                }
           }
           else { //gdy trzeba 0 dopisywać bo większa niż -1
                std::cout << "0,";
                while (comma < 0) {
                    for (int j = 7; j >= 0; j--) {
                        std::cout << 0;
                    }
                    comma += 8;
                }
                for (int i = 0; i < number._number.size(); i++) {
                    for (int j = 7; j >= 0; j--) {
                        std::cout << ((number._number[i] >> j) & 1);
                    }
                }
           }
        } 
        else {// gdy najstarszy jest na dodatniej
            comma = number._number.size() * 8 - 8;
            for (int i = 0; i < number._number.size(); i++) {
                for (int j = 7; j >= 0; j--) {
                    
                    std::cout << ((number._number[i] >> j) & 1);
                }
                comma -= 8;
                if (comma == 0) {
                    std::cout << ',';
                }
            }
        }
        
         
    }
}

void TC::negateBits(TC& number){
    for(int i = 0; i < number._number.size(); i++){
       number._number[i] = ~(number._number[i]);
    } // dodać 1 asemblerem bo negacja (w wypadku 1000000000 00000000 wyjdzie tak samo w wypadku 00000100 000000000 wyjdzie 11111100 00000000)

}

TC TC::add(TC& number1, TC& number2){
    vector<uint8_t> newNumber;
    int leastSignificant = number1._position < number2._position ? number2._position : number2._position;
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2; 
    int diffBettwenLeastAndMost = mostSignificant + leastSignificant ;
    while (diffBettwenLeastAndMost >= 0) { 
        newNumber.push_back(0);
        diffBettwenLeastAndMost -= 8;
    }
    return TC(newNumber, 2); //zwracanie losowej
}
    

 