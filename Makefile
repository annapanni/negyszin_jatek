map: map.o linked_list.o geometry.o utilities.o
	gcc map.o geometry.o linked_list.o utilities.o `sdl2-config --cflags --libs` -lSDL2_gfx -lm -o map

map.o: map.c
	gcc -c  map.c `sdl2-config --cflags --libs` -o map.o

geometry.o: geometry.c geometry.h
	gcc -c geometry.c -o geometry.o

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c -o linked_list.o

utilities.o: utilities.c utilities.h
	gcc -c utilities.c -o utilities.o

start: map
	./map

clean:
	rm *.o
