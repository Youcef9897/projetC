CC = gcc
CFLAGS = -Wall -Wextra

SRC = main.c graphe.c mission1.c mission2.c mission3.c simulation.c affichage.c
OBJ = $(SRC:.c=.o)

EXEC = falcon_eye.exe

LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -lm
RM = del /f /q

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(EXEC)