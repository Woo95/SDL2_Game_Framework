#pragma once

#include "Scene.h"

class CPlayScene : public CScene
{
    friend class CSceneManager;

private:
    CPlayScene();
    ~CPlayScene();

public:
    virtual bool Enter() final;
    virtual bool Exit()  final;

    virtual void Update(float DeltaTime)        final;
    virtual void LateUpdate(float DeltaTime)    final;
    virtual void Render(SDL_Renderer* Renderer) final;
};