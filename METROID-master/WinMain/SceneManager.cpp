#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::addScene(Scene * scene)
{
	_listScenes.push_back(scene);
}

void SceneManager::removeScene()
{
	if (!_listScenes.empty())
	{
		_listScenes.back()->Release();
		delete _listScenes.back();
		_listScenes.pop_back();
	}
}

void SceneManager::replaceScene(Scene * scene)
{
	this->removeScene();
	this->addScene(scene);
}

void SceneManager::clearScenes()
{
	if (!_listScenes.empty())
	{
		_listScenes.back()->Release();
		delete _listScenes.back();
		_listScenes.pop_back();
	}
}

void SceneManager::Release()
{
	if (!_listScenes.empty())
	{
		_listScenes.back()->Release();
		delete(_listScenes.back());
	}
}

Scene * SceneManager::getCurrentScene()
{
	if (!_listScenes.empty())
		return _listScenes.back();
	return nullptr;
}
