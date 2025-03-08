#pragma once

#include "../Core/GameInfo.h"
#include "../Manager/MemoryPoolManager.h"
#include "../Core/Utils/LayerUtils.h"
#include "Layer.h"

class CSceneCollision;
class CCamera;
class CSceneUI;
class CTexture;

// 추상 클래스 선언 - 인스턴스화 불가 (abstract 키워드로 명시 안하더라도, 순수 가상 함수가 있으면 자동으로 추상 클래스)
class CScene abstract	
{
	friend class CSceneManager;

protected:
	CScene();
	// 가상 소멸자: 다형성 지원, 파생 클래스를 들고 있는 CScene 변수가 소멸 시, 파생 클래스 소멸자도 올바르게 호출됨.
	virtual ~CScene();

protected:
    std::vector<CLayer*> mLayers;

    CSceneCollision* mSceneCollision;
    CCamera*  mCamera;
    CSceneUI* mSceneUI;

    std::unordered_set<std::string> mTextureKeys;

protected:
	virtual bool Enter() = 0;
	virtual bool Exit()  = 0;

    virtual void Update(float DeltaTime);
    virtual void LateUpdate(float DeltaTime);
    virtual void Render(SDL_Renderer* Renderer);

    virtual void LoadTextures() = 0;

public:
    CSceneCollision* GetCollision() const { return mSceneCollision; }
    CCamera*  GetCamera()  const { return mCamera; }
    CSceneUI* GetSceneUI() const { return mSceneUI; }

    template <typename T, int initialCapacity = 50>
    T* AllocateObject(const std::string& name, ELayer::Type type = ELayer::Type::OBJECT)
    {
        // 해당 타입의 메모리 풀이 없으면 새로 생성
        if (!CMemoryPoolManager::GetInst()->HasPool<T>())
        {
            CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
        }

        T* gameObject = CMemoryPoolManager::GetInst()->Allocate<T>();

        gameObject->SetName(name);
        gameObject->mScene = this;
        gameObject->mLayer = mLayers[type];

        if (!gameObject->Init())
        {
            // 초기화 실패 시, gameObject는 container에 저장 안되니 deallocate
            CMemoryPoolManager::GetInst()->Deallocate<T>(gameObject);
            return nullptr;
        }

        mLayers[type]->AddObject(gameObject);

        return gameObject;
    }

    template <typename T>
    void CallEventByType(void(T::*func)())
    {
        for (CLayer* layer : mLayers)
        {
            std::vector<CObject*> objVec = layer->GetObjectVec();

            for (CObject* obj : objVec)
            {
                if (T* castedObj = dynamic_cast<T*>(obj))
                {
                    (castedObj->*func)();
                }
            }
        }
    }

protected:
    void LoadTexture(const std::string& key, const char* fileName);
    void UnloadTextures();
};