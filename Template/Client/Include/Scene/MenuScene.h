#pragma once

#include "Scene.h"

class CMenuScene :
    public CScene
{
    friend class CSceneManager;

private:
    CMenuScene();
    ~CMenuScene();

public:
    virtual bool Enter() override;
    virtual bool Exit()  override;
};

