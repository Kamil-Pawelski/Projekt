main: main.cpp TC.cpp vectorAdd.s vectorSub.s
	gcc -m32 -g main.cpp TC.cpp vectorAdd.s vectorSub.s -o main -lstdc++
	
