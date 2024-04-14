#pragma once
#include "../Common.h"

class Scene
{
public:
	virtual ~Scene() {};
	virtual void OnCreate() {};
	virtual void OnActivate() {};
	virtual void OnDeactivate() {};
	virtual void OnProcessInput(f32 elapsed_time) {};
	virtual void OnUpdate(f32 elapsed_time) {};
	virtual void OnRender() {};
};