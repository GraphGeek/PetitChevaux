CC = gcc
OBJ = game_controller.o init.o main.o
CFLAGS = -W -Wall

petitschevaux : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o petitschevaux

game_controller.o : game_controller.c game_controller.h
	$(CC) $(CFLAGS) -c game_controller.c

init.o : init.c init.h
	$(CC) $(CFLAGS) -c init.c

main.o : main.c main.h
	$(CC) $(CFLAGS) -c main.c

clean :
	rm *.o