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
    virtual bool Exit()  override;
};