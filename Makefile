OBJS = source/main.cpp

CC = g++

COMPILER_FLAGS  = -g -Wall

INCLUDE_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
LINKER_FLAGS = -L/usr/lib -lSDL2 -lpthread

OBJ_NAME = build/pong

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
