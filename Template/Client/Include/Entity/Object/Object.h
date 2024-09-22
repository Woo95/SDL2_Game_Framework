#pragma once

#include "../../Core/DataContainer.h"
#include "../../Core/GameInfo.h"

class CObject abstract	: public DataContainer
{
	friend class CScene;

public:
	CObject();
	CObject(const CObject& obj);	// 복사 생성자 (함수 내 구현에 따라서 "깊은 또는 얕은 복사 생성자"가 된다)
	virtual ~CObject();

protected:
	class CScene* mScene = nullptr;

protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() = 0;
};