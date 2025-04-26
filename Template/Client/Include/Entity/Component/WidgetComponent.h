#pragma once

#include "Component.h"

class CWidget;

class CWidgetComponent : public CComponent
{
public:
	CWidgetComponent();
	virtual ~CWidgetComponent();

private:
	CWidget* mWidget;

public:
	virtual bool Init() final;

private:
	virtual void Update(float deltaTime)        final;
	virtual void LateUpdate(float deltaTime)    final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release()                      final;

public:
	void SetWidget(CWidget* widget);
};