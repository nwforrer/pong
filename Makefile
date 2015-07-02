OBJS = source/main.cpp source/SDLTexture.cpp

CC = g++

COMPILER_FLAGS  = -g -Wall -Werror

INCLUDE_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
LINKER_FLAGS = -L/usr/lib -lSDL2 -lSDL2_image -lpthread

OBJ_NAME = build/pong

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm $(OBJ_NAME)
