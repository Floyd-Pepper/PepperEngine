#include "EngineManager.h"

EngineManager EngineManager::_Instance = EngineManager();

EngineManager::EngineManager() {
	_Camera = Camera();
	_Camera.debug = "debug";
}

EngineManager& EngineManager::Instance()
{
	return _Instance;
}
