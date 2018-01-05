#pragma once
#include "Scene.h"
#include <vector>

using namespace std;

class SceneManager
{
private:
	vector<Scene*> _listScenes;
public:
	SceneManager();
	~SceneManager();

	void addScene(Scene* scene);
	void removeScene();
	void replaceScene(Scene* scene);
	void clearScenes();

	void Release();
	Scene* getCurrentScene();
};
