#pragma once

#include "../Core/GameInfo.h"
#include "../Core/ObjectType.h"

// 추상 클래스 선언 - 인스턴스화 불가 (abstract 키워드로 명시 안하더라도, 순수 가상 함수가 있으면 자동으로 추상 클래스)
class CScene abstract	
{
	friend class CSceneManager;

protected:
	CScene();
	// 가상 소멸자: 다형성 지원, 파생 클래스를 들고 있는 CScene 변수가 소멸 시, 파생 클래스 소멸자도 올바르게 호출됨.
	virtual ~CScene();

private:
	// unique_ptr로 CObject의 메모리 자동 해제
	std::vector<std::unique_ptr<class CObject>> mObjVec[(int)ObjectType::END];

protected:
	// Enter()와 Exit()은 순수 가상 함수
	virtual bool Enter() = 0;
	virtual bool Exit()  = 0;

	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

public:
    template <typename T>
    T* CreateObject(const std::string& name, ObjectType type)
    {
        std::unique_ptr<T> gameObject = std::make_unique<T>();

        gameObject->SetName(name);
        gameObject->mScene = this;

        if (!gameObject->Init())
        {
            // 초기화 실패 시, gameObject는 container에 저장 안되니 함수 종료 시 자동 해제됨.
            return nullptr;
        } 
        // move로 unique_ptr을 mObjVec[]에 이동
        mObjVec[(int)type].push_back(std::move(gameObject));

        return (T*)mObjVec[(int)type].back().get();
    }
};