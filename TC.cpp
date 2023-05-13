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
vector<uint8_t> TC::getNumber(TC number){
    return number._number;
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
void TC::setNegative(uint8_t& number, int n) //do wywalenia po prostu = xd
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
void TC::printTC(TC& number) // nie działa XD
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
    } 
    uint8_t one = 1;
    vectorAdd(&number._number[number._number.size() - 1], &one, 0);
}

TC TC::add(TC& number1, TC& number2){

    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2; 
    int number3Size = ((mostSignificant - leastSignificant) + 9) / 8 ; 
    uint8_t one = 1;
    vector<uint8_t> newNumber(number3Size);
    TC newTC(newNumber, leastSignificant);
    int tempLS = mostSignificant;
    unsigned int index = 1;

    while(mostSignificantNumber1/ 8 != tempLS / 8){
        tempLS -= 8;
        index++;
    }
    vectorAdd(&newTC._number[index], &number1._number[0], number1._number.size()-1);
    
    tempLS = mostSignificant;
    index = 1;
    
    while(mostSignificantNumber2/ 8 != tempLS / 8){
        tempLS -= 8;
        index++;
    }
    vectorAdd(&newTC._number[index], &number2._number[0], number2._number.size()-1);
    if(number1._number[0] > 127 && number2._number[0] > 127){
        negateBits(newTC);
    } else if (number1._number[0] > 127 && number1._number[0] < 127) {
        if(isNegativeBigger(number1, number2, mostSignificantNumber1, mostSignificantNumber2)){
            negateBits(newTC);
        }
    } else if(number1._number[0] < 127 && number1._number[0] > 127){
        if(isNegativeBigger(number2, number1, mostSignificantNumber1, mostSignificantNumber2)){
            negateBits(newTC);
        }
    }
    
    //sprawdzenie która większa ujemna czy dodatnia spoko
    //jeśli ujemna i przepełnienie to zmieniamy 1 na 255 a jak nie to spoko nic ok
    //i jak nie ma przeniesienia [0] = 0 to erase like
   
    return newTC; 
}
    

 TC TC::sub(TC& number1, TC& number2){
   
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2; 
    int number3Size = ((mostSignificant - leastSignificant) + 9) / 8 ; 
    vector<uint8_t> newNumber(number3Size);
    int tempLS = mostSignificant;
    unsigned int index = 1;
    while(mostSignificantNumber1/ 8 != tempLS / 8){
        tempLS -= 8;
        index++;
    }
    vectorAdd(&newNumber[index], &number1._number[0], number1._number.size()-1);
    tempLS = mostSignificant;
    index = 1;
    std::cout <<(int) newNumber[2];
    std::cout << (int) number2._number[1];
    while(mostSignificantNumber2/ 8 != tempLS / 8){
        tempLS -= 8;
        index++;
    }
    vectorSub(&newNumber[index], &number2._number[0], number2._number.size()-1);

    //sprawdzenie która większa ujemna czy dodatnia spoko //analogia coś do dodawania
    //jeśli ujemna i przepełnienie to zmieniamy 1 na 255 a jak nie to spoko nic ok
    //i jak nie ma przeniesienia [0] = 0 to erase like
    return TC(newNumber, leastSignificant); 
}

 TC TC::mul(TC& number1, TC& number2){
   
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    int number3Size = number1._number.size() + number2._number.size(); 
    vector<uint8_t> newNumber(number3Size);

    for (int i = number2._number.size() - 1; i >= 0; i--) {
       vectorMul(&number1._number[0], &number2._number[i], &newNumber[0], number1._number.size(), i + 1);
       }
    //tu też manipulacja 1 znakiem
    TC tc(newNumber, leastSignificant);
    if((number1._number[0] > 127 && number2._number[0] < 127) || (number1._number[0] < 127 && number2._number[0] > 127))
        negateBits(tc); 
    return  tc;
}

TC TC::div(TC& number1, TC& number2){
    vector<uint8_t> quotient;
    return TC(quotient , 0);
}

bool TC::isNegativeBigger(TC number1, TC number2, unsigned int mostSignificantNumber1, unsigned int mostSignificantNumber2){
    if(mostSignificantNumber1 / 8 > mostSignificantNumber2 / 8){
        return true;
    } else if (mostSignificantNumber1 / 8 < mostSignificantNumber2 / 8){
        return false;
    }

    negateBits(number1  );

    for(int i = 0; i < number1._number.size() && i < number2._number.size(); i++){
        if(number1._number[i] > number2._number[i]){
            return true;
        } else if(number1._number[i] < number2._number[i]){
            return false;
        }
    }

    if(number1._number.size() <= number2._number.size()){
        return false;
    } 

    return true;
}