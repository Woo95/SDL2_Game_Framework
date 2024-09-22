#pragma once

#include "../../Core/GameInfo.h"

class CObject abstract
{
	friend class CScene;

public:
	CObject();
	CObject(const CObject& obj);	// 복사 생성자 (함수 내 구현에 따라서 "깊은 또는 얕은 복사 생성자"가 된다)
	virtual ~CObject();

protected:
	std::string mName;
	bool mActive = true;	// handle object to be deleted
	bool mEnable = true;	// handle object to be rendered

	class CScene* mScene = nullptr;

public:
	const std::string& GetName() const { return mName; }
	bool GetActive() const { return mActive; }
	bool GetEnable() const { return mEnable; }
	
	void SetName(const std::string& name) { mName = name; }
	void SetEnable(bool enable) { mEnable = enable; }
	void SetActive(bool active) { mActive = active; }

protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() = 0;
};