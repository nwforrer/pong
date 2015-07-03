#include "Scene.h"

Scene::Scene(std::stack<Scene*> *scenes, SDL_Renderer *renderer)
{
	mScenes = scenes;
	mRenderer = renderer;
}

Scene::~Scene()
{

}