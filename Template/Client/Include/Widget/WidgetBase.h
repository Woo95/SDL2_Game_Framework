#pragma once

#include <string>
#include "../Core/Transform.h"

class CWidgetBase abstract
{
	friend class CSceneUI;
	friend class CUserWidget;
	friend class CWidget;
	friend class CWidgetComponent;

public:
	CWidgetBase() = default;
	virtual ~CWidgetBase() = default;

protected:
	std::string mName;
	size_t mID = -1;
	bool mActive = true;	// handle object/component to be deleted
	bool mEnable = true;	// handle object/component to be rendered

	SDL_Rect    mRect = { 0, 0, 0, 0 };
	CTransform* mTransform = nullptr;

protected:
	virtual void Update(float DeltaTime)     = 0;
	virtual void LateUpdate(float DeltaTime) = 0;
	virtual void Render(SDL_Renderer* Renderer, const FVector2D& topLeft = FVector2D::ZERO) = 0;

public:
	const std::string& GetName() const { return mName; }
	size_t   GetID() const { return mID; }
	bool GetActive() const { return mActive; }
	bool GetEnable() const { return mEnable; }

	const SDL_Rect& GetRect()  const { return mRect; }
	CTransform* GetTransform() const { return mTransform; }

protected:
	void SetName(const std::string& name)
	{
		mName = name;
		mID = std::hash<std::string>()(name);
	}
	void SetActive(bool active)
	{
		mActive = active;
	}
	void SetEnable(bool enable)
	{
		mEnable = enable;
	}

	void UpdateRect()
	{
		const FVector2D& scale   = mTransform->GetWorldScale();
		const FVector2D& topLeft = mTransform->GetWorldPos() - mTransform->GetPivot() * scale;

		mRect = { (int)topLeft.x, (int)topLeft.y, (int)scale.x, (int)scale.y };
	}
};