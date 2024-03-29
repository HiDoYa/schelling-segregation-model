OBJ = main.o population.o cell.o
all: GlobalSettings.h game 

game: $(OBJ)
	g++ $(OBJ) -o schelling.out -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./schelling.out -g

main.o: main.cpp
	g++ -std=c++14 -c $<

population.o: include/Population.cpp
	g++ -std=c++14 -c $<

cell.o: include/Cell.cpp
	g++ -std=c++14 -c $<

clean:
	rm *.o

# Even if not .o files exist, won't throw error
GlobalSettings.h:
	rm *.o || true