#pragma once

#include "../Core/GameInfo.h"
#include "../Manager/MemoryPoolManager.h"
#include "Layer.h"

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

	class CSceneUI* mSceneUI;
	class CCamera* mCamera;
    class CSceneCollision* mSceneCollision;

    // Resources //
    std::vector<std::shared_ptr<class CTexture>> mTextures;
    std::vector<std::shared_ptr<class CFont>>    mFonts;
    std::vector<std::shared_ptr<class CSFX>>     mSFXs;
    std::vector<std::shared_ptr<class CBGM>>     mBGMs;

protected:
	virtual bool Enter() = 0;
	virtual bool Exit()  = 0;

    virtual void Update(float deltaTime);
    virtual void LateUpdate(float deltaTime);
    virtual void Render(SDL_Renderer* renderer);

    virtual void LoadResources() = 0;

public:
	CSceneUI* GetSceneUI() const { return mSceneUI; }
	CCamera*  GetCamera()  const { return mCamera; }
    CSceneCollision* GetCollision() const { return mSceneCollision; }

    // Object 생성 및 Scene에 등록
    template <typename T, int initialCapacity = 50>
    T* InstantiateObject(const std::string& name, ELayer::Type type = ELayer::Type::OBJECT)
    {
        // 해당 타입의 메모리 풀이 없으면 새로 생성
        if (!CMemoryPoolManager::GetInst()->HasPool<T>())
        {
            CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
        }

        T* obj = CMemoryPoolManager::GetInst()->Allocate<T>();

        obj->SetName(name);
        obj->mScene = this;
        obj->mLayer = mLayers[type];

        if (!obj->Init())
        {
            // 초기화 실패 시, gameObject는 container에 저장 안되니 deallocate
            CMemoryPoolManager::GetInst()->Deallocate<T>(obj);
            return nullptr;
        }

        mLayers[type]->AddObject(obj);

        return obj;
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
    void LoadFont(const std::string& key, const char* fileName, int fontSize);
    void LoadSFX(const std::string& key, const char* fileName);
    void LoadBGM(const std::string& key, const char* fileName);

private:
    void UnloadResources();
};