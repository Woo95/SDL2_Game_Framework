#pragma once

#include "Component.h"

class CWidgetBase;

class CWidgetComponent : public CComponent
{
public:
	CWidgetComponent();
	virtual ~CWidgetComponent();

private:
	CWidgetBase* mWidget; // Can be either UserWidget or Widget

public:
	virtual bool Init()                         override;
	virtual void Update(float DeltaTime)        override;
	virtual void LateUpdate(float DeltaTime)    override;
	virtual void Render(SDL_Renderer* Renderer) override;

private:
	virtual void Release() final;

public:
	void SetWidget(CWidgetBase* widget);
};