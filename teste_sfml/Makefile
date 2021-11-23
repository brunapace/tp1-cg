
# My first makefile
 
all: game
 
game: main.o GameObject.o Mage.o Enemy.o EnemyManager.o -lsfml-graphics -lsfml-window -lsfml-system
	g++ -o printy main.o GameObject.o Mage.o Enemy.o EnemyManager.o

main.o: main.c GameObject.h Mage.h Enemy.h EnemyManager.h
	g++ -o main.o main.c -c -W -Wall -ansi -pedantic

EnemyManager.o: EnemyManager.c Enemy.h
	g++ -o EnemyManager.o EnemyManager.c -c -W -Wall -ansi -pedantic

Enemy.o: Enemy.c GameObject.h
	g++ -o Enemy.o Enemy.c -c -W -Wall -ansi -pedantic

Mage.o: Mage.c GameObject.h
	g++ -o Mage.o Mage.c -c -W -Wall -ansi -pedantic

GameObject.o: GameObject.c GameObject.h
	g++ -o GameObject.o GameObject.c -c -W -Wall -ansi -pedantic

clean:
	rm -rf *.o *~ game