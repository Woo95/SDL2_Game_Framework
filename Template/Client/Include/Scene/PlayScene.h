#pragma once

#include "Scene.h"

class CPlayScene : public CScene
{
    friend class CSceneManager;

private:
    CPlayScene();
    ~CPlayScene();

public:
    virtual bool Enter() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(SDL_Renderer* Renderer) override;
    virtual bool Exit()  override;
};