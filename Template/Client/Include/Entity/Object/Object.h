#pragma once

#include "../../Core/DataContainer.h"
#include "../../Manager/MemoryPoolManager.h"
#include "../Component/Component.h"
#include "../Component/Transform.h"

class CObject abstract	: public DataContainer
{
	friend class CScene;

protected:
	CObject();
	CObject(const CObject& objRef);	// 복사 생성자 (함수 내 구현에 따라서 "깊은 또는 얕은 복사 생성자"가 된다)
	virtual ~CObject();
		
protected:
	class CScene* mScene = nullptr;

	CComponent* mRootComponent;
	// 메모리 풀을 사용하는 컴포넌트 리스트 - Pool을 사용하는 컴포넌트를 지울 때 빠른 탐색을 위해 사용
	std::unordered_map<std::type_index, std::vector<CComponent*>> mPoolCompMap;

protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() = 0;	// Scene.h에서 object memoryPool usage 위하여

public:
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
	template <typename T>
	T* CreateComponent(const std::string& name, CComponent* parentComponent = nullptr)
	{
		if (CMemoryPoolManager::GetInst()->HasPool<T>())
			return nullptr;

		T* component = new T;

		component->SetName(name);
		component->mObject = this;

		if (!component->Init())
		{
			SAFE_DELETE(component);
			return nullptr;
		}

		if (!parentComponent)
		{
			parentComponent = mRootComponent;
		}
		parentComponent->AddChild(component);

		return component;
	}
	template <typename T>
	T* AllocateComponent(const std::string& name, CComponent* parentComponent = nullptr)
	{
		if (!CMemoryPoolManager::GetInst()->HasPool<T>())
			return nullptr;

		T* component = CMemoryPoolManager::GetInst()->Allocate<T>();

		component->SetName(name);
		component->mObject = this;

		if (!component->Init())
		{
			// 초기화 실패 시, component는 container에 저장 안되니 deallocate
			CMemoryPoolManager::GetInst()->Deallocate<T>(component);
			return nullptr;
		}

		std::type_index key = typeid(T);
		mPoolCompMap[key].push_back(component);

		if (!parentComponent)
		{
			parentComponent = mRootComponent;
		}
		parentComponent->AddChild(component);

		return component;
	}
	template <typename T>
	void CreatePoolAndSync(int initialCapacity)
	{
		std::type_index key = typeid(T);
		mPoolCompMap.emplace(key, std::vector<CComponent*>());	// mPoolCompMap[key]가 존재하지 않을 경우 빈 벡터를 추가

		CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
	}
	template <typename T>
	void DeletePoolAndSync()
	{
		std::type_index key = typeid(T);

		std::unordered_map<std::type_index, std::vector<CComponent*>>::iterator iter    = mPoolCompMap.find(key);
		std::unordered_map<std::type_index, std::vector<CComponent*>>::iterator iterEnd = mPoolCompMap.end();

		if (iter != iterEnd)	// if pool found
		{
			std::vector<CComponent*>& typePoolCompVec = iter->second;

			for (size_t j = typePoolCompVec.size(); j > 0; j--)
			{
				T* comp = static_cast<T*>(typePoolCompVec[j - 1]);	// starts from last idx
				
				mRootComponent->DeleteChild(comp);

				CMemoryPoolManager::GetInst()->Deallocate<T>(comp);
			}
			mPoolCompMap.erase(iter);
		}
		CMemoryPoolManager::GetInst()->DeletePool<T>();
	}
};