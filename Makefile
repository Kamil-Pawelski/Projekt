main: main.cpp TC.cpp vectorAdd.s
	gcc -m32 main.cpp TC.cpp vectorAdd.s -o main -lstdc++
	
