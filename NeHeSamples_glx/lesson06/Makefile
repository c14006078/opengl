CC = gcc -Wall -pedantic -ansi -std=c99 -I TextureAnalysis/include -I TextureAnalysis/src

all:
	$(CC) lesson06.c -o lesson06 -L/usr/X11R6/lib -lGL -lGLU -lX11 -lXxf86vm -lssl -lcrypto

clean:
	@echo Cleaning up...
	@rm lesson06
	@echo Done.
