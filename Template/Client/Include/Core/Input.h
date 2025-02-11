#pragma once

#include "InputUtils.h"

class CScene;

class CInput
{
	friend class CGameManager;

private:
	CInput();
	~CInput();

private:
	std::unordered_map<SDL_Scancode, FKeyInfo*> mMapKeyInfo;
	std::unordered_map<std::string, FBindKey*>  mMapBindKey;
	bool	mCtrl	= false;
	bool	mAlt	= false;
	bool	mShift	= false;

private:
	static CInput* mInst;

private:
	bool Init();
	void Update();

	void UpdateKeyInfo();
	void UpdateBindFunction();
	void ExecuteBindFunctions(FBindKey* BindKey, EKey::Type type);

	FKeyInfo* FindKeyInfo(SDL_Scancode key);
	FBindKey* FindBindKey(const std::string& key);

public:
	bool CreateBindKey(const std::string& key, SDL_Scancode value);

	// !AddBindFunction()이 template인 이유는, 등록할 클래스의 함수 타입을 알 수 없기 때문!
	// void (T::*func)(): "void 리턴 타입의 인자가 없는" 클래스의 멤버 함수 포인터 타입의 매개변수
	template <typename T>
	void AddBindFunction(const std::string& key, EKey::Type type,
		T* obj, void (T::*func)(), CScene* scene)
	{
		FBindKey* bindKey = FindBindKey(key);

		if (!bindKey)
			return;

		FBindFunction* bindFunc = new FBindFunction;

		bindFunc->obj = obj;
		bindFunc->scene = scene;
#pragma region std::bind(func, obj)
/*
	std::bind는 C++ 표준 라이브러리 #include <functional>에서 제공하는 템플릿 클래스다.
	함수나 함수 객체를 다른 함수나 객체와 결합하여 새로운 함수 객체를 생성하는 역할을 한다.
	std::bind(func, obj)는 Func와 Obj를 결합하여, 새로운 함수 객체를 생성하고 
	이를 Function 구조체(또는 클래스)의 func 멤버 변수에 할당한다.

	Function->func()를 호출하면 obj객체의 func함수를 호출한다.
*/
#pragma endregion
		bindFunc->func = std::bind(func, obj);

		bindKey->vecFunction[type].push_back(bindFunc);
	}

	template <typename T>
	void DeleteBindFunction(const std::string& key, EKey::Type type, T* obj)
	{
		FBindKey* bindKey = FindBindKey(key);

		if (!bindKey)
			return;

		std::vector<FBindFunction*>& bindFuncs = bindKey->vecFunction[type];

		for (size_t i = bindFuncs.size(); i > 0; i--)
		{
			FBindFunction* bindFunc = bindFuncs[i - 1];

			if (bindFunc->obj == obj)
			{
				std::swap(bindFuncs[i - 1], bindFuncs.back());
				bindFuncs.pop_back();

				SAFE_DELETE(bindFunc);
			}
		}
	}

public:
	static CInput* GetInst()
	{
		if (!mInst)
			mInst = new CInput;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};