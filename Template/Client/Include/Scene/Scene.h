#pragma once

#include "../Core/GameInfo.h"
#include "../Manager/MemoryPoolManager.h"

// 추상 클래스 선언 - 인스턴스화 불가 (abstract 키워드로 명시 안하더라도, 순수 가상 함수가 있으면 자동으로 추상 클래스)
class CScene abstract	
{
	friend class CSceneManager;

protected:
	CScene() = default;
	// 가상 소멸자: 다형성 지원, 파생 클래스를 들고 있는 CScene 변수가 소멸 시, 파생 클래스 소멸자도 올바르게 호출됨.
	virtual ~CScene();

protected:
    class CSceneCollision* mSceneCollision = nullptr;

    std::unordered_map<std::type_index, std::vector<class CObject*>> mObjMap;

protected:
	// Enter()와 Exit()은 순수 가상 함수
	virtual bool Enter() = 0;
	virtual bool Exit()  = 0;

	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
    CSceneCollision* GetCollision() const { return mSceneCollision; }

    template <typename T>
    T* CreateObject(const std::string& name)
    {
        if (CMemoryPoolManager::GetInst()->HasPool<T>())
            return nullptr;

        T* gameObject = new T;

        gameObject->SetName(name);
        gameObject->mScene = this;

        if (!gameObject->Init())
        {
            // 초기화 실패 시, gameObject는 container에 저장 안되니 delete 
            SAFE_DELETE(gameObject);
            return nullptr;
        }

        std::type_index key = typeid(T);
        mObjMap[key].push_back(gameObject);
        return gameObject;
    }
    template <typename T, int initialCapacity = 50>
    T* AllocateObject(const std::string& name)
    {
        // 해당 타입의 메모리 풀이 없으면 새로 생성
        if (!CMemoryPoolManager::GetInst()->HasPool<T>())
        {
            CreatePoolAndSync<T>(initialCapacity);
        }

        T* gameObject = CMemoryPoolManager::GetInst()->Allocate<T>();

        gameObject->SetName(name);
        gameObject->mScene = this;

        if (!gameObject->Init())
        {
            // 초기화 실패 시, gameObject는 container에 저장 안되니 deallocate
            CMemoryPoolManager::GetInst()->Deallocate<T>(gameObject);
            return nullptr;
        }

        std::type_index key = typeid(T);
        mObjMap[key].push_back(gameObject);
        return gameObject;
    }

    template <typename T>
    void DeleteObjectByType()
    {
        std::type_index key = typeid(T);

        std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iter    = mObjMap.find(key);
        std::unordered_map<std::type_index, std::vector<CObject*>>::iterator iterEnd = mObjMap.end();

        if (iter != iterEnd)    // if pool found
        {
            std::vector<CObject*>& typeObjVec = iter->second;

            for (size_t j = typeObjVec.size(); j > 0; j--)
            {
                T* obj = dynamic_cast<T*>(typeObjVec[j - 1]);   // starts from last idx

                if (!obj->Release())
                {
                    SAFE_DELETE(obj);
                }
            }
            mObjMap.erase(iter);
        }
    }

private:
    template <typename T>
    void CreatePoolAndSync(int initialCapacity)
    {
        std::type_index key = typeid(T);
        mObjMap.emplace(key, std::vector<CObject*>());  // mObjMap[key]가 존재하지 않을 경우 빈 벡터를 추가

        CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
    }
};