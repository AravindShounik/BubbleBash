main : main.o AssetManager.o Game.o InputManager.o SplashState.o StateMachine.o
	g++ -std=c++2a main.o AssetManager.o Game.o InputManager.o SplashState.o StateMachine.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp AssetManager.cpp Game.cpp InputManager.cpp SplashState.cpp StateMachine.cpp
	g++ -std=c++2a -c main.cpp AssetManager.cpp Game.cpp InputManager.cpp SplashState.cpp StateMachine.cpp

clean :
	rm *.o main
