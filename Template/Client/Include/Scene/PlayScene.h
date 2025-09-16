#pragma once

#include "Scene.h"

class CPlayScene : public CScene
{
    friend class CSceneManager;

private:
    CPlayScene();
    ~CPlayScene();

public:
    virtual bool Enter(void* payload = nullptr) final;
    virtual bool Exit()  final;

    virtual void Update(float deltaTime)        final;
    virtual void LateUpdate(float deltaTime)    final;
    virtual void Render(SDL_Renderer* renderer) final;

    virtual void LoadResources() final;
};