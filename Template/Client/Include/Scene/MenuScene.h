#pragma once

#include "Scene.h"

class CMenuScene : public CScene
{
    friend class CSceneManager;

private:
    CMenuScene();
    ~CMenuScene();

public:
    virtual bool Enter(void* payload = nullptr) final;
    virtual bool Exit()  final;

    virtual void Update(float deltaTime)        final;
    virtual void LateUpdate(float deltaTime)    final;
    virtual void Render(SDL_Renderer* renderer) final;

    virtual void LoadResources() final;
};