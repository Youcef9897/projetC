CC = gcc
CFLAGS = -Wall -Wextra
SRC = main.c graphe.c mission1.c mission2.c mission3.c simulation.c affichage.c
OBJ = $(SRC:.c=.o)
EXEC = falcon_eye
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)