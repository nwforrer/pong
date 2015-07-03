#ifndef GAME_OVER_SCENE_H_
#define GAME_OVER_SCENE_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "Scene.h"
#include "SDLTexture.h"

class GameOverScene : public Scene
{
public:
	GameOverScene(std::stack<Scene*> *scenes, SDL_Renderer *renderer);
	~GameOverScene();

	bool init();
	void close();

	void handleRender();
	void handleInput(SDL_Event& e);

private:
	TTF_Font* mFont;

	SDLTexture mGameOverTextTexture;
	SDLTexture mMainMenuTextTexture;
};

#endif