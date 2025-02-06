#pragma once

#include "../Core/GameInfo.h"
#include "../Core/LayerUtils.h"

class CLayer
{
	friend class CScene;

public:
	CLayer();
	~CLayer();

private:
    std::vector<class CObject*> mObjects;

	ESort::Type mSort = ESort::Y;

protected:
	void Update(float DeltaTime);
	void LateUpdate(float DeltaTime);
	void Render(SDL_Renderer* Renderer);

public:
	const std::vector<CObject*>& GetObjectVec() { return mObjects; }

	void AddObject(CObject* obj)
	{
		mObjects.emplace_back(obj);
	}

private:
	static bool SortY(CObject* a, CObject* b);
};