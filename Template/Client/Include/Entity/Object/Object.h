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
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual void Release() = 0;	// Scene.h에서 object memoryPool usage 위하여

public:
	CScene* GetScene() const { return mScene; }
	CTransform* GetTransform() const { return mRootComponent->GetTransform(); }
	CComponent* GetComponent(const std::string& name = "")
	{
		if (name.empty())
		{
			return mRootComponent;
		}
		else
		{
			size_t hashID = std::hash<std::string>()(name);

			return mRootComponent->FindComponent(hashID);
		}
	}
	template <typename T>
	T* GetComponent()
	{
		return mRootComponent->FindComponent<T>();
	}

public:
	template <typename T, int initialCapacity = 10>
	T* AllocateComponent(const std::string& name, CComponent* parentComponent = nullptr)
	{
		// 해당 타입의 메모리 풀이 없으면 새로 생성
		if (!CMemoryPoolManager::GetInst()->HasPool<T>())
		{
			CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
		}

		T* component = CMemoryPoolManager::GetInst()->Allocate<T>();

		component->SetName(name);
		component->mObject = this;

		if (!component->Init())
		{
			// 초기화 실패 시, component는 container에 저장 안되니 deallocate
			CMemoryPoolManager::GetInst()->Deallocate<T>(component);
			return nullptr;
		}

		if (parentComponent)
			parentComponent->AddChild(component);

		return component;
	}

public:
	void Enable();
	void Disable();
	void Destroy();
};