#pragma once

#include "../EntityBase.h"
#include "../../Manager/MemoryPoolManager.h"
#include "../Component/Component.h"
#include "../../Core/Transform.h"

class CScene;
class CLayer;

class CObject abstract : public CEntityBase
{
	friend class CScene;
	friend class CLayer;

protected:
	CObject();
	virtual ~CObject();
	
protected:
	CScene* mScene;
	CLayer* mLayer;

	CComponent* mRootComponent;

protected:
	virtual bool Init();
	virtual void Update(float deltaTime);
	virtual void LateUpdate(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

private:
	// Scene.h -> Layer.h에서 CObject의 memoryPool을 사용하기 위해서 필요
	virtual void Release() = 0;

public:
	CScene* GetScene() const { return mScene; }
	CTransform* GetTransform() const { return mRootComponent->GetTransform(); }
	CComponent* GetComponent(const std::string& name = "")
	{
		if (name.empty())
			return mRootComponent;

		size_t hashID = std::hash<std::string>()(name);
		return mRootComponent->FindComponent(hashID);
	}
	template <typename T>
	T* GetComponent() const { return mRootComponent->FindComponent<T>(); }

public:
	template <typename T, int initialCapacity = 10>
	T* AllocateComponent(const std::string& name)
	{
		// 해당 타입의 메모리 풀이 없으면 새로 생성
		if (!CMemoryPoolManager::GetInst()->HasPool<T>())
		{
			CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
		}

		T* component = CMemoryPoolManager::GetInst()->Allocate<T>();
		component->SetName(name);

		return component;
	}

public:
	void Enable();
	void Disable();
	void Destroy();
};