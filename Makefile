game: main.o graphics.o map.o linked_list.o geometry.o event_handler.o mytime.o utilities.o file_management.o
	gcc main.o graphics.o map.o geometry.o linked_list.o utilities.o event_handler.o mytime.o file_management.o `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lm -o game

main.o: main.c utilities.h controls.h map.h event_handler.h graphics.h mytime.h
	gcc -c main.c `sdl2-config --cflags --libs` -Wall -o main.o

graphics.o: graphics.c graphics.h controls.h linked_list.h map.h geometry.h mytime.h
	gcc -c graphics.c `sdl2-config --cflags --libs` -Wall -o graphics.o

map.o: map.c map.h geometry.h linked_list.h utilities.h
	gcc -c map.c -Wall -o map.o

event_handler.o: event_handler.c event_handler.h controls.h map.h mytime.h
	gcc -c event_handler.c -Wall -o event_handler.o

geometry.o: geometry.c geometry.h
	gcc -c geometry.c `sdl2-config --cflags --libs` -Wall -o geometry.o

linked_list.o: linked_list.c linked_list.h geometry.h
	gcc -c linked_list.c -Wall -o linked_list.o

utilities.o: utilities.c utilities.h
	gcc -c utilities.c -Wall -o utilities.o

mytime.o: mytime.h mytime.c
	gcc -c mytime.c -Wall -o mytime.o

file_management.o: file_management.c file_management.h mytime.h
	gcc -c file_management.c -Wall -o file_management.o

start: game
	./game

clean:
	rm *.o
