OBJS = build/Game.o \
	   build/GameOverState.o \
	   build/MainState.o \
	   build/MainMenuState.o \
	   build/PauseMenuState.o \
	   build/Physics.o \
	   build/SDLTexture.o \
	   build/SDLTimer.o \
	   build/Sprite.o

CC = g++

COMPILER_FLAGS  = -std=c++11 -g -Wall -Werror `sdl2-config --cflags`

LINKER_FLAGS = `sdl2-config --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_NAME = build/pong

all: main.o $(OBJS)
	$(CC) build/main.o $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)

main.o: source/main.cpp
	$(CC) -c $(COMPILER_FLAGS) source/main.cpp -o build/main.o

$(OBJS): build/%.o : source/%.cpp source/%.h
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

clean :
	rm build/*.o $(OBJ_NAME)
