#ifndef SCENE_H_
#define SCENE_H_

#include <SDL.h>
#include <stack>

class Scene
{
public:
	Scene(std::stack<Scene*> *scenes, SDL_Renderer *renderer);
	virtual ~Scene();

	virtual bool init() =0;
	virtual void close() =0;

	virtual void handleRender() =0;
	virtual void handleInput(SDL_Event& e) =0;

protected:
	std::stack<Scene*> *mScenes;
	SDL_Renderer *mRenderer;
};

#endif