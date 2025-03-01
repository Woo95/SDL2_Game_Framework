#pragma once

#include "SceneUI.h"

class CMenuUI : public CSceneUI
{
public:
	CMenuUI();
	virtual ~CMenuUI();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);
};