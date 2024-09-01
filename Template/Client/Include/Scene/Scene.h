#pragma once

#include "../Core/GameInfo.h"

// 추상 클래스 선언 - 인스턴스화 불가 (abstract 키워드로 명시 안하더라도, 순수 가상 함수가 있으면 자동으로 추상 클래스)
class CScene abstract	
{
	friend class CSceneManager;

protected:
	CScene();
	// 가상 소멸자: 다형성 지원, 파생 클래스를 들고 있는 CScene 변수가 소멸 시, 파생 클래스 소멸자도 올바르게 호출됨.
	virtual ~CScene();

public:
	// Enter()와 Exit()은 순수 가상 함수
	virtual bool Enter() = 0;
	virtual bool Exit()  = 0;
	virtual void Update(float DeletaTime);
	virtual void Render(SDL_Renderer* Renderer);
};