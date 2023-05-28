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
    unsigned int comma = 0;
    while (number1._position < 0 || number2._position < 0) {
        if (number1._position < 0 && number2._position < 0) {
                number1._position += 8;
                number2._position += 8;
                if(number1._position == 0){ 
                   number1._number.insert(number1._number.begin(), 0);
                }
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }
                comma++;
        }
        else if (number1._position >= 0 && number2._position < 0) {
                number1._number.push_back(0);
                number2._position += 8;
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }  
                comma++;              
        }
        else if (number1._position < 0 && number2._position  >= 0) {
                number2._number.push_back(0);
                number1._position += 8;
                if(number1._position == 0){
                   number1._number.insert(number1._number.begin(), 0);
                }
                comma++;
        }
    }
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2;
    int number3Size = ((mostSignificant - leastSignificant) + 9) / 8 ; 
    vector<uint8_t> newNumber(number3Size);
    TC newTC(newNumber, 0);
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
    newTC._position = leastSignificant - (comma * 8);
    return newTC; 
}
    

 TC TC::sub(TC number1, TC number2){
   
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    unsigned int comma = 0;
    while (number1._position < 0 || number2._position < 0) {
        if (number1._position < 0 && number2._position < 0) {
                number1._position += 8;
                number2._position += 8;
                if(number1._position == 0){ 
                   number1._number.insert(number1._number.begin(), 0);
                }
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }
                comma++;
        }
        else if (number1._position >= 0 && number2._position < 0) {
                number1._number.push_back(0);
                number2._position += 8;
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }  
                comma++;              
        }
        else if (number1._position < 0 && number2._position  >= 0) {
                number2._number.push_back(0);
                number1._position += 8;
                if(number1._position == 0){
                   number1._number.insert(number1._number.begin(), 0);
                }
                comma++;
        }
    }
    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    int mostSignificant =  mostSignificantNumber1 > mostSignificantNumber2 ?
                           mostSignificantNumber1 : mostSignificantNumber2; 
    int number3Size = ((mostSignificant - leastSignificant) + 9) / 8 ; 
    vector<uint8_t> newNumber(number3Size);
    TC newTC(newNumber, 0);
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

    newTC._position = leastSignificant - (comma * 8);
    return newTC; 
}

 TC TC::mul(TC number1, TC number2){
   unsigned int comma = 0;
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    while (number1._position < 0 || number2._position < 0) {
        if (number1._position < 0 && number2._position < 0) {
                number1._position += 8;
                number2._position += 8;
                if(number1._position == 0){ 
                   number1._number.insert(number1._number.begin(), 0);
                }
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }
                comma++;
        }
        else if (number1._position >= 0 && number2._position < 0) {
                number1._number.push_back(0);
                number2._position += 8;
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }  
                comma++;              
        }
        else if (number1._position < 0 && number2._position  >= 0) {
                number2._number.push_back(0);
                number1._position += 8;
                if(number1._position == 0){
                   number1._number.insert(number1._number.begin(), 0);
                }
                comma++;
        }
    }
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
    TC newTC(newNumber, 0);
    
    if(negate){
        negateIntegerBits(newTC);
    }
    newTC._position = leastSignificant - (8 * comma);
    return  newTC;
}

void TC::div(TC number1, TC number2) {

    unsigned int comma = 0;
    int leastSignificant = number1._position < number2._position ? number1._position : number2._position;
    while (number1._position < 0 || number2._position < 0) {
        if (number1._position < 0 && number2._position < 0) {
                number1._position += 8;
                number2._position += 8;
                if(number1._position == 0){ 
                   number1._number.insert(number1._number.begin(), 0);
                }
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }
                comma++;
        }
        else if (number1._position >= 0 && number2._position < 0) {
                number1._number.push_back(0);
                number2._position += 8;
                if(number2._position == 0){
                   number2._number.insert(number2._number.begin(), 0); 
                }  
                comma++;              
        }
        else if (number1._position < 0 && number2._position  >= 0) {
                number2._number.push_back(0);
                number1._position += 8;
                if(number1._position == 0){
                   number1._number.insert(number1._number.begin(), 0);
                }
                comma++;
        }
    }


    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    bool negate = false;
    while (mostSignificantNumber1 <= mostSignificantNumber2)
    {
        if (number1._number[0] > 127)
            number1._number.insert(number1._number.begin(), 255);
        else
            number1._number.insert(number1._number.begin(), 0);
        mostSignificantNumber1 += 8;
    }
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
    
    unsigned int loop = number1._number.size() - number2._number.size();
    vector<uint8_t> numberA(number1._number.begin(), number1._number.begin() + number2._number.size());
    vector<uint8_t> loopResult(number2._number.size()); //tu wynik odejmowania/dodawania
    
    vector<uint8_t> result(number1._number.size()); //tu wymik

    unsigned int size = number2._number.size();
    
    numberA.insert(numberA.begin(), 0);
    if ((numberA[1] > 127 && number2._number[0] > 127) || (numberA[1] < 128 && number2._number[0] < 128)) {
        vectorSub(&numberA[1], &number2._number[0], size - 1);
    }
    else {
        vectorAdd(&numberA[1], &number2._number[0], size - 1);
    }
    numberA.erase(numberA.begin());
    std::cout << std::endl;
    std::cout << std::endl;

    printVector(numberA);
    std::cout << std::endl;
    printVector(number2._number);

    //std::cout << "Looprestult2 przed  " << printTC(number) << std::endl;
    //std::cout << "Looprestult2  number 2 " << printTC(number2) << std::endl;

    //loopResult2 = sub(number, number2);
    //std::cout << "Looprestult2  " << printTC(loopResult2) << std::endl;
   // if ((loopResult2._number[0] > 127 && number2._number[0] < 128) || (loopResult2._number[0] < 128 && number2._number[0] > 127)) {
  //      result[0] = 0;
   // }
//    else {
        //std::cout << "tutaj";
 //       result[0] = 1;
//    }

 //   printVector(result);
 //   std::cout << std::endl << printTC(loopResult2) << std::endl;
    //std::cout << "loop = " << loop << std::endl;
  /*  for (loop; loop > 0; loop--) {
        for (int i = 0; i <= 7; i++) {
            shiftDiv(loopResult2._number, number1._number[size]);
            if ((loopResult2._number[0] > 127 && number2._number[0] < 128) || (loopResult2._number[0] < 128 && number2._number[0] > 127)) {
                //loopResult2 = sub(number, number2);
            }
        }
        std::cout << loop << std::endl;

    }
    */
    TC result2(result, 0);
    //TC mulResult = mul(result2, number2);
    //std::cout << printTC(mulResult) << std::endl;
    //if mnozenie razy to bedzie rowne to nic jak nie to 
   
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

void TC::shiftDiv(std::vector<uint8_t>& vec, uint8_t& value) {
    for (int i = 0; i < vec.size() - 1; i++) {

        uint8_t new_carry = (vec[i+1] >> 7) & 1;  
        vec[i+1] = (vec[i+1] << 1);
        std::cout << (int)new_carry << std::endl;
        vec[i] = (vec[i] << 1);  
        std::cout << (int) vec[i] << std::endl; 
        vec[i] = vec[i] + new_carry; 
    }
    uint8_t carry = (value >> 7) & 1;
    value = value << 1;
    vec[vec.size() - 1] += carry;

}