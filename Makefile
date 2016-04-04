all : executable
executable : 
	gcc -o simu simu.c `sdl-config --cflags --libs` 
clean :
	rm simu
