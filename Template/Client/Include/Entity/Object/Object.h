#pragma once

#include "../../Core/DataContainer.h"
#include "../../Manager/MemoryPoolManager.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"
#include "../../Scene/Scene.h"

class CObject abstract	: public CDataContainer
{
	friend class CScene;

protected:
	CObject();
	CObject(const CObject& objRef);	// 복사 생성자 (함수 내 구현에 따라서 "깊은 또는 얕은 복사 생성자"가 된다)
	virtual ~CObject();
		
protected:
	CScene* mScene;

	CComponent* mRootComponent;

protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() = 0;	// Scene.h에서 object memoryPool usage 위하여

public:
	CScene*     GetScene() const { return mScene; }
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
	void Destroy();
};