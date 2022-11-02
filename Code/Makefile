all: compile link

compile:
	g++ -Iinclude -c src/main.cpp

link:
	g++ -O3 main.o StrategyManager.cpp Utils.cpp BaseStrategy.cpp Strategy.cpp Game.cpp Movement.cpp -o main -Linclude -lsfml-system -lsfml-window -lsfml-graphics