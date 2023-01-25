CC = gcc
ALLEGRO = `pkg-config allegro-5 allegro_font-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5 allegro_image-5 --libs --cflags`
.PHONY: all clean

main : main.o candy.o audio.o
	$(CC)  main.o candy.o audio.o $(ALLEGRO) -o main

main.o : main.c 
	$(CC)  -c main.c 

candy.o : candy.h candy.c 
	$(CC)  -c candy.c 

audio.o : audio.h audio.c 
	$(CC)  -c audio.c 

clean :
	rm *.o *~ all

purge:
	rm *.o main