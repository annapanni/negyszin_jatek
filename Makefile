game: main.o graphics.o map.o linked_list.o geometry.o utilities.o
	gcc main.o graphics.o map.o geometry.o linked_list.o utilities.o `sdl2-config --cflags --libs` -lSDL2_gfx -lm -o game

main.o: main.c
	gcc -c main.c `sdl2-config --cflags --libs` -o main.o

graphics.o: graphics.c graphics.h
	gcc -c graphics.c `sdl2-config --cflags --libs` -o graphics.o

map.o: map.c map.h
	gcc -c  map.c -o map.o

geometry.o: geometry.c geometry.h
	gcc -c geometry.c -o geometry.o

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c -o linked_list.o

utilities.o: utilities.c utilities.h
	gcc -c utilities.c -o utilities.o

start: game
	./game

clean:
	rm *.o
