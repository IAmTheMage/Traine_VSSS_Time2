all: compile link

compile:
	g++ -Iinclude -Iinclude\SFML\include -c src\StrategyManager.cpp src\Utils.cpp src\BaseStrategy.cpp src\Strategy.cpp src\Game.cpp src\Movement.cpp src\main.cpp

link:
	g++ main.o Game.o BaseStrategy.o Movement.o Strategy.o StrategyManager.o Utils.o -o main -Linclude\SFML\lib -lsfml-system -lsfml-window -lsfml-graphics