#include <SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gStickGuy = NULL;

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    gWindow = SDL_CreateWindow("Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }

  return success;
}

bool loadMedia()
{
  bool success = true;

  gStickGuy = loadSurface("stick-guy.bmp");
  if (gStickGuy == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "stick-guy.bmp", SDL_GetError());
    success = false;
  }

  return success;
}

void close()
{
  SDL_FreeSurface(gStickGuy);
  gStickGuy = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
  SDL_Surface* optimizedSurface = NULL;

  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if (loadedSurface == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
  }
  else
  {
    optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimizedSurface == NULL)
    {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
  }

  return optimizedSurface;
}

int main(int argc, char **argv)
{
  if (!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    if (!loadMedia())
    {
      printf("Failed to load media!\n");
    }
    else
    {
      bool quit = false;
      SDL_Event e;

      while (!quit)
      {
        while (SDL_PollEvent(&e) != 0)
        {
          if (e.type == SDL_QUIT)
          {
            quit = true;
          }
          else if (e.type == SDL_KEYDOWN)
          {
            switch(e.key.keysym.sym)
            {
              case SDLK_ESCAPE:
              {
                quit = true;
              } break;
            }
          }
        }
        
        SDL_BlitSurface(gStickGuy, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }

  close();

  return 0;
}
