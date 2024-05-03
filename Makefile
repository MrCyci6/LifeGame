LifeGame: lifeGame.o main.c
	gcc $^ -o $@

lifeGame.o: code/lifeGame.c code/lifeGame.h
	gcc -Wall -c $< -o $@

clean:
	rm -rf *.o LifeGame