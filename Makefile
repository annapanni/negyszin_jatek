game: main.o graphics.o map.o linked_list.o geometry.o event_handler.o
	gcc main.o graphics.o map.o geometry.o linked_list.o utilities.o event_handler.o `sdl2-config --cflags --libs` -lSDL2_gfx -lm -o game

main.o: main.c utilities.o controls.h
	gcc -c main.c `sdl2-config --cflags --libs` -o main.o

graphics.o: graphics.c graphics.h controls.h
	gcc -c graphics.c `sdl2-config --cflags --libs` -o graphics.o

map.o: map.c map.h
	gcc -c  map.c -o map.o

event_handler.o: event_handler.c event_handler.h
	gcc -c event_handler.c -o event_handler.o

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
