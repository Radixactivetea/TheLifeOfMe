all : compile link run clear

compile:
	g++ -c -I"include" main.cpp Animation.cpp

link:
	g++ main.o Animation.o -o Main -L"lib" -lglew32 -lglfw3 -lopengl32 -lgdi32 -lassimp.dll

run:
	.\Main.exe

clear:
	del main.o  Animation.o