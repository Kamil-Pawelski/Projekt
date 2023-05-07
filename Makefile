main: main.cpp TC.cpp vectorAdd.s vectorSub.s vectorMul.s vectorDiv.s
	gcc -m32 -g main.cpp TC.cpp vectorAdd.s vectorSub.s vectorMul.s vectorDiv.s -o main -lstdc++
	
