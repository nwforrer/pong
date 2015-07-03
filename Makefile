OBJS = source/main.cpp \
	   source/Game.cpp \
	   source/MainMenuScene.cpp \
	   source/MainScene.cpp \
	   source/Physics.cpp \
	   source/Scene.cpp \
	   source/SDLTexture.cpp \
	   source/SDLTimer.cpp \
	   source/Sprite.cpp

CC = g++

COMPILER_FLAGS  = -std=c++11 -g -Wall -Werror

INCLUDE_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
LINKER_FLAGS = -L/usr/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread

OBJ_NAME = build/pong

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean :
	rm $(OBJ_NAME)
