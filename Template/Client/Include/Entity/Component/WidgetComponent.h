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
	virtual bool Init() final;

private:
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

public:
	void SetWidget(CWidgetBase* widget);
};