CC = gcc
ALLEGRO = `pkg-config allegro-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 --libs --cflags`
.PHONY: all clean

main : main.o candy.o audio.o global.o init.o menu.o states.o
	$(CC)  main.o candy.o audio.o global.o init.o menu.o states.o $(ALLEGRO) -o main

main.o : main.c 
	$(CC)  -c main.c 

candy.o : candy.h candy.c 
	$(CC)  -c candy.c 

audio.o : audio.h audio.c 
	$(CC)  -c audio.c 

states.o : states.h states.c 
	$(CC)  -c states.c 

global.o : global.h global.c 
	$(CC)  -c global.c 

menu.o : menu.h menu.c 
	$(CC)  -c menu.c 

init.o : init.h init.c 
	$(CC)  -c init.c 

clean :
	rm *.o *~ all

purge:
	rm *.o main