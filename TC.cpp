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
        if (position < 0) { 
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
        if(shiftNumber[0] == 0 && shiftNumber[1] < 128)
            shiftNumber.erase(shiftNumber.begin());
        else if(shiftNumber[0] == 255 && shiftNumber[1] > 127)
            shiftNumber.erase(shiftNumber.begin());
        changeIndex2(position);
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
std::string TC::printTC(TC number) 
{
    std::string numb = "";
    int mostSignificant = (number._position + number._number.size() * 8);
    if (number._position == 0) { //dla pozycji nieujemnych
        for (int i = 0; i < number._number.size(); i++) {
            for (int j = 7; j >= 0; j--) {
                numb += std::to_string(((number._number[i] >> j) & 1));
            }
        }
        return numb;
    }
    else if (number._position > 7) {
        for (int i = 0; i < number._number.size(); i++) {
            for (int j = 7; j >= 0; j--) {
                numb += std::to_string(((number._number[i] >> j) & 1));
            }
        }
        while (number._position != 0) {
            for (int i = 0; i < 8; i++)
                numb += "0";
            number._position -= 8;
        }
        return numb;
    }
    else if (number._position < 0 && mostSignificant > 0) {

        int comma = number._position + number._number.size() * 8;
        int size = number._number.size();
        int i = 0;
        while (true) {
            for (i; i < size; i++) {
                for (int j = 7; j >= 0; j--) {
                    numb += std::to_string(((number._number[i] >> j) & 1));
                }
                comma -= 8;
                if (comma == 0) {
                    i++;
                    break;              
                }      
            }
            break;
        }
        numb += ",";
        for (i; i < size; i++) {
            for (int j = 7; j >= 0; j--) {
                numb += std::to_string(((number._number[i] >> j) & 1));
            }
        }
        return numb;
    }
    else if (number._position < 0 && mostSignificant == 0) {
        numb += "0,";
        for (int i = 0; i < number._number.size(); i++) {
            for (int j = 7; j >= 0; j--) {
                numb += std::to_string(((number._number[i] >> j) & 1));
            }
        }
        return numb;
    }
    else {
        mostSignificant = -mostSignificant;
        numb += "0.";
        while (mostSignificant != 0) {
            numb +=  "0";
            mostSignificant--;
        }
        for (int i = 0; i < number._number.size(); i++) {
            for (int j = 7; j >= 0; j--) {
                numb += std::to_string(((number._number[i] >> j) & 1));
            }
        }
        return numb;
    }
}

void TC::negateBits(TC& number){
   
    for(int i = 0; i < number._number.size(); i++){
       number._number[i] = ~(number._number[i]);
    } 
    uint8_t one = 1;
    vectorAdd(&number._number[number._number.size() - 1], &one, 0);
}

void TC::negateIntegerBits(TC& number){
int mostSignificant = number._position - 1 + (number._number.size() * 8);  
if(mostSignificant > 0){
        unsigned int size = number._number.size() - 1;
        int tempPos = number._position;
        uint8_t one = 1;
        if(tempPos < 0){
        while(tempPos != 0){
            size--;
            tempPos += 8;
        }
        }
        for(int i = 0; i <= size; i++){
            number._number[i] = ~(number._number[i]);
        }
        vectorAdd(&number._number[size], &one, 0); 
}
}
TC TC::add(TC number1, TC number2){

    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2;
    int number3Size = ((mostSignificant - leastSignificant) + 9) / 8 ; 
    vector<uint8_t> newNumber(number3Size);
    TC newTC(newNumber, leastSignificant);
    int tempLS = mostSignificant;
    unsigned int index1 = 1, index2 = 1;

    while(mostSignificantNumber1 != tempLS){
        tempLS -= 8;
        index1++;
    }
    tempLS = mostSignificant;
    while(mostSignificantNumber2 != tempLS){
        tempLS -= 8;
        index2++;
    }
    if (number1._number[0] > 127 && number2._number[0] < 127 && mostSignificantNumber1 >= 0) {
        negateIntegerBits   (number1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        vectorSub(&newTC._number[index1], &number1._number[0], number1._number.size()-1);        
    } else if(number1._number[0] < 127 && number2._number[0] > 127){
        negateIntegerBits(number2);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorSub(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
       // negateBits(newTC);
    } else if(number1._number[0] > 127 && number2._number[0] > 127){
        negateIntegerBits(number1);
        negateIntegerBits(number2);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        negateIntegerBits(newTC);
    } else {
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
    } 

    if(newTC._number[1] > 127 && newTC._number[0] > 127){
            newTC._number.erase(newTC._number.begin());
    } else if(newTC._number[1] < 128 && newTC._number[0] == 0) {
            newTC._number.erase(newTC._number.begin());
    } else if(isNumberZero(number1) && number2._number[0] < 127){
        newTC._number.erase(newTC._number.begin());
    }
    
    return newTC; 
}
    

 TC TC::sub(TC number1, TC number2){
   
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2; 
    int number3Size = ((mostSignificant - leastSignificant) + 9) / 8 ; 
    vector<uint8_t> newNumber(number3Size);
    TC newTC(newNumber, leastSignificant);
    int tempLS = mostSignificant;
    unsigned int index1 = 1, index2 = 1;
    while(mostSignificantNumber1 != tempLS){
        tempLS -= 8;
        index1++;
    }
    tempLS = mostSignificant;
    while(mostSignificantNumber2 != tempLS){
        tempLS -= 8;
        index2++;
    }
    if (number1._number[0] > 127 && number2._number[0] < 127) {
        negateIntegerBits(number1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        negateIntegerBits(newTC);
    } else if(number1._number[0] < 127 && number2._number[0] > 127){
        negateIntegerBits(number2);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
    } else if(number1._number[0] > 127 && number2._number[0] > 127){
        negateIntegerBits(number1);
        negateIntegerBits(number2);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        vectorSub(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
    } else {
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorSub(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
    } 
    if(newTC._number[1] > 127 && newTC._number[0] > 127){
            newTC._number.erase(newTC._number.begin());
    } else if(newTC._number[1] < 128 && newTC._number[0] == 0) {
            newTC._number.erase(newTC._number.begin());
    } else if(isNumberZero(number1) && number2._number[0] < 127){
        newTC._number.erase(newTC._number.begin());
    }
    return newTC; 
}

 TC TC::mul(TC number1, TC number2){
   
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    vector<uint8_t> newNumber(number1._number.size() + number2._number.size());
    bool negate = false;
    if(number1._number[0] > 127 && number2._number[0] > 127){
        negateIntegerBits(number1);
        negateIntegerBits(number2);
    }
    else if (number1._number[0] > 127 && number2._number[0] < 127){
        negateIntegerBits(number1);
        negate = true;
    }
    else if (number1._number[0] < 127 && number2._number[0] > 127){
        negateIntegerBits(number2);
        negate = true;
    } 

    for (int i = number2._number.size() - 1; i >= 0; i--) {
       vectorMul(&number1._number[0], &number2._number[i], &newNumber[0], number1._number.size(), i);
    }
    TC newTC(newNumber, leastSignificant);
    
    if(negate){
        negateIntegerBits(newTC);
    }
    
    return  newTC;
}

void TC::div(TC number1, TC number2){
   
    if(number1._position < 0 || number2._position < 0){
        number1._position += 8;
        number2._position += 8;
        if(number1._position > 7){
            number1._number.push_back(0);
             number1._position = 0;
        }
        if(number2._position > 7){
            number2._number.push_back(0);
            number2._position = 0;
        }
    }
    vector<uint8_t> quotient(number1._number.size());
    vector<uint8_t> remainder;
    unsigned int power;
    bool negative;
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    uint8_t one = 1;
     if(number1._number[0] < 127 && number2._number[0] > 127){
        negateBits(number2);
        negative = true;
    } else if(number1._number[0] > 127 && number2._number[0] < 127){
        negateBits(number1);
        negative = true;
    } else if (number1._number[0] > 127 && number2._number[0] > 127){
        negateBits(number1);
        negateBits(number2);
    }
    TC number3;
    while(true){
        remainder = number1._number;
        number3 = sub(number1, number2);
        if( number3._number[0] > 127){
            break;
        } else {
            number1._number = number3._number;
            vectorAdd(&quotient[quotient.size() - 1], &one, 0);
        }
    }

std::cout << "Quotient = "; printVector(quotient);
std::cout << std::endl;
std::cout << "Reminder = "; printVector(remainder);
}

bool TC::isNegativeBigger(TC number1, TC number2, unsigned int mostSignificantNumber1, unsigned int mostSignificantNumber2){
    if(mostSignificantNumber1 / 8 > mostSignificantNumber2 / 8){
        return true;
    } else if (mostSignificantNumber1 / 8 < mostSignificantNumber2 / 8){
        return false;
    }

    negateBits(number1);

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

void TC::printVector(const vector<uint8_t>&  number){
    for(int i = 0; i < number.size(); i++){
        for (int j = 7; j >= 0; j--) {
            std::cout << ((number[i] >> j) & 1);
        }
    }
}

void TC::changeIndex(int& a, int& b){
    int modA = a % 8;
    if(a < 0)
        a = a - modA -1;
    else
        a = a + 7 - modA;
       
    int modB = b % 8;
    if(b < 0)
        b = b - modB -1;
    else 
        b = b + 7 - modB;
}

void TC::changeIndex2(int& a) {
    int modA = a % 8;
    if (a > 0)
        a = a - modA;
    else
        a = a - 8 - modA;
}