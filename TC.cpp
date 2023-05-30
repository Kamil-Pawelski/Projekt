#include "TC.h"

TC::TC() { 
    _number.push_back(0);
    _position = 0;
}

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

bool TC::isNumberZero(TC number){
    for (const auto& el : number._number)
    {  
        if(el != 0) return false;
    }
    return true;
}

bool TC::isNumberZero(vector<uint8_t> number){
    for (const auto& el : number)
    {  
        if(el != 0) return false;
    }
    return true;
}

vector<uint8_t> TC::getNumber(TC number){
    return number._number;
}



uint8_t TC::rightShift(const uint8_t& number, int n)
{
    return number >> n; 
}

uint8_t TC::leftShift(const uint8_t& number, int n)
{
    return number << n;
}


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




std::string TC::printTC(TC number) 
{
    std::string numb = "";
    int mostSignificant = (number._position + number._number.size() * 8);
    if (number._position == 0) { 
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

void TC::negateBits(vector<uint8_t>& number){
    if(isNumberZero(number)){
        return;
    }
    for(int i = 0; i < number.size(); i++){
       number[i] = ~(number[i]);
    } 
    uint8_t one = 1;
    vectorAdd(&number[number.size() - 1], &one, 0);
}

void TC::negateBits(TC& number){
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
        negateBits(number1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        vectorSub(&newTC._number[index1], &number1._number[0], number1._number.size()-1);        
    } else if(number1._number[0] < 127 && number2._number[0] > 127){
        negateBits(number2);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorSub(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
    } else if(number1._number[0] > 127 && number2._number[0] > 127){
        negateBits(number1);
        negateBits(number2);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        negateBits(newTC);
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
        negateBits(number1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        negateBits(newTC);
    } else if(number1._number[0] < 127 && number2._number[0] > 127){
        negateBits(number2);
        vectorAdd(&newTC._number[index1], &number1._number[0], number1._number.size()-1);
        vectorAdd(&newTC._number[index2], &number2._number[0], number2._number.size()-1);
    } else if(number1._number[0] > 127 && number2._number[0] > 127){
        negateBits(number1);
        negateBits(number2);
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

    if(isNumberZero(number1) || isNumberZero(number2)){
        vector<uint8_t> zero = {0};
        return TC(zero, 0);
    }
        
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
        negateBits(number1);
        negateBits(number2);
    }
    else if (number1._number[0] > 127 && number2._number[0] < 127){
        negateBits(number1);
        negate = true;
    }
    else if (number1._number[0] < 127 && number2._number[0] > 127){
        negateBits(number2);
        negate = true;
    } 

    for (int i = number2._number.size() - 1; i >= 0; i--) {
       vectorMul(&number1._number[0], &number2._number[i], &newNumber[0], number1._number.size(), i);
    }
    TC newTC(newNumber, 0);
    
    if(negate){
        negateBits(newTC);
    }
    newTC._position = leastSignificant - (8 * comma);
    return  newTC;
}

TC TC::div(TC number1, TC number2) {
    TC copyNumber1 = number1;    
    if((isNumberZero(number1) && isNumberZero(number2)) || (isNumberZero(number1))){
        vector<uint8_t> zero = {0};
        return TC(zero, 0);
    }
    else if(isNumberZero(number2)){
        throw std::invalid_argument( "Division by 0. End of program execution" );
    }
    unsigned int comma = 0;
    bool negate = false;
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
    if(number1._number[0] > 127 && number2._number[0] > 127){
        negateBits(number1);
        negateBits(number2);
    }
    else if (number1._number[0] > 127 && number2._number[0] < 127){
        negateBits(number1);
        negate = true;
    }
    else if (number1._number[0] < 127 && number2._number[0] > 127){
        negateBits(number2);
        negate = true;
    } 

    int mostSignificantNumber1 = (number1._position - 1 + (number1._number.size() * 8));
    int mostSignificantNumber2 = (number2._position - 1 + (number2._number.size() * 8));
    while (mostSignificantNumber1 <= mostSignificantNumber2)
    {
        if (number1._number[0] > 127)
            number1._number.insert(number1._number.begin(), 255);
        else
            number1._number.insert(number1._number.begin(), 0);
        mostSignificantNumber1 += 8;
    }

    unsigned int loop = number1._number.size() - number2._number.size();
    vector<uint8_t> numberA(number1._number.begin(), number1._number.begin() + number2._number.size());
    vector<uint8_t> loopResult(number2._number.size()); 
    vector<uint8_t> result(number1._number.size()); 
    TC numberB(numberA, number1._position);
    TC loopResultB(loopResult, number1._position);
    unsigned int size = number2._number.size();

    if ((numberA[0] > 127 && number2._number[0] > 127) || (numberA[0] < 128 && number2._number[0] < 128)) {
        numberB = sub(numberB, number2);
    }
    else {
        numberB = add(numberB, number2);
    }

    if ((numberB._number[0] > 127 && number2._number[0] > 127) || (numberB._number[0] < 128 && number2._number[0] < 128)) {
        result[size - 1] = 1;
    }
    else {
        result[size - 1] = 0;
    }
    
    bool negateNumberA = false;
    for(int i = 0; i < loop; i++){
        for(int j = 0; j < 8; j++){
            shiftDiv(numberB._number, number1._number[numberA.size() + i]);
 
            if ((numberB._number[0] > 127 && number2._number[0] > 127) || (numberB._number[0] < 128 && number2._number[0] < 128)) {
                 numberB = sub(numberB, number2);
            }
            else {
                 numberB = add(numberB, number2);
            }
            if ((numberB._number[0] > 127 && number2._number[0] > 127) || (numberB._number[0] < 128 && number2._number[0] < 128)) {
                result[size + i] = result[size + i] << 1;
                result[size + i] += 1;
            }
            else {
                result[size + i] = result[size + i] << 1;
            }      
        }

    }
    
    TC newTC(result, 0); 

    if(negate){
        negateBits(newTC);
    }
    
    TC mulResult = mul(newTC, number2);
    
    if(mulResult._number[0] > 127 && copyNumber1._number[0] < 128){
        negateBits(mulResult);
    }
    shorterString(mulResult);
    shorterString(copyNumber1);
    if(!(mulResult == copyNumber1)){
        uint8_t zero = 0;
        result.push_back(0);
        for(int i = loop; i < loop + 1; i++){
        for(int j = 0; j < 8; j++){
            shiftDiv(numberB._number, zero);
 
            if ((numberB._number[0] > 127 && number2._number[0] > 127) || (numberB._number[0] < 128 && number2._number[0] < 128)) {
                 numberB = sub(numberB, number2);
            }
            else {
                 numberB = add(numberB, number2);
            }
            if ((numberB._number[0] > 127 && number2._number[0] > 127) || (numberB._number[0] < 128 && number2._number[0] < 128)) {
                result[size + i] = result[size + i] << 1;
                result[size + i] += 1;
            }
            else {
                result[size + i] = result[size + i] << 1;
            }  
           
        }
         int position = leastSignificant - (8 * comma) - 8;
         TC newTC2(result, 0);
         if(negate){
         negateBits(newTC2);
         }  
         newTC2._position = leastSignificant - (8 * comma) - 8;
         return newTC2;  
    }
    }
    newTC._position = leastSignificant - (8 * comma);
    return newTC;

}

void TC::shorterString(TC& number){
    int i = 1;
    while((number._position + number._number.size() * 8) > 0 && number._number.size() > 1){
         if(number._number[i] > 127 && number._number[0] > 127){
            number._number.erase(number._number.begin());
            continue;
        } else if(number._number[i] < 128 && number._number[0] == 0) {
            number._number.erase(number._number.begin());
            continue;
        }
        break;
    }

    while(number._position < 0 && number._number.size() > 1){
         if(number._number[number._number.size() - 1] == 0){
            number._number.pop_back();
            number._position += 8;
            continue;
         }
        break;
    }
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
        vec[i] = (vec[i] << 1);  
        vec[i] = vec[i] + new_carry; 
    }
    uint8_t carry = (value >> 7) & 1;
    value = value << 1;
    vec[vec.size() - 1] = (vec[vec.size() - 1]) << 1;
    vec[vec.size() - 1] += carry;

}