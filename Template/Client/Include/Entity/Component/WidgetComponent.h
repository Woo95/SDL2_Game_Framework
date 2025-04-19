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
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

public:
	void SetWidget(CWidget* widget);
};