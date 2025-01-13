#pragma once

#include "Scene.h"

class CMenuScene : public CScene
{
    friend class CSceneManager;

private:
    CMenuScene();
    ~CMenuScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void Update(float DeltaTime)        final;
    virtual void LateUpdate(float DeltaTime)    final;
    virtual void Render(SDL_Renderer* Renderer) final;
};