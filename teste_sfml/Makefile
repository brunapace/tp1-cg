
# My first makefile
 
all: game
 
game: main.o GameObject.o Mage.o Enemy.o EnemyManager.o
	g++ -o game main.o GameObject.o Mage.o Enemy.o EnemyManager.o -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp GameObject.h Mage.h Enemy.h EnemyManager.h 
	g++ -o main.o main.cpp -c -W -Wall -ansi -std=gnu++11 -pedantic

EnemyManager.o: EnemyManager.cpp Enemy.h
	g++ -o EnemyManager.o EnemyManager.cpp -c -W -Wall -ansi -std=gnu++11 -pedantic

Enemy.o: Enemy.cpp GameObject.h
	g++ -o Enemy.o Enemy.cpp -c -W -Wall -ansi -std=gnu++11 -pedantic

Mage.o: Mage.cpp GameObject.h
	g++ -o Mage.o Mage.cpp -c -W -Wall -ansi -std=gnu++11 -pedantic

GameObject.o: GameObject.cpp GameObject.h
	g++ -o GameObject.o GameObject.cpp -c -W -Wall -ansi -std=gnu++11 -pedantic

clean:
	rm -rf *.o *~ game