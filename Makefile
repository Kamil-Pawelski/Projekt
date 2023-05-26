main: main.cpp TC.cpp vectorMul.s vectorSub.s vectorAdd.s 
	gcc -m32 -g main.cpp TC.cpp vectorMul.s vectorSub.s vectorAdd.s -o main -lstdc++

