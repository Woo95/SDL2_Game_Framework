#pragma once

#include "GameInfo.h"

namespace EKeyType
{
	// 키 상태를 나타내는 열거형
	enum Type : unsigned char
	{
		Press,
		Hold,
		Release,
		Max
	};
}

// 키 상태 정보를 담는 구조체
struct FKeyInfo
{
	// SDL_SCANCODE enum 값을 저장하는 Key 변수
	SDL_Scancode Key = SDL_SCANCODE_UNKNOWN;
	bool	Press	= false;
	bool	Hold	= false;
	bool	Release	= false;
};

// 바인드된 함수에 대한 정보를 담는 구조체
struct FBindFunction
{
#pragma region void*
/*
	void*는 어떤 데이터 타입의 포인터도 가리킬 수 있는 포인터 타입으로,
	특정 타입에 종속되지 않고 범용적으로 사용할 수 있다.
	Obj 변수는 현재 어떤 객체도 가리키고 있지 않음을 나타내기 위해 nullptr로 초기화했다.
*/
#pragma endregion
	void* Obj = nullptr;	// 모든 타입의 포인터를 범용적으로 저장하는 변수
#pragma region std::function<void()> 
/*
	std::function은 C++ 표준 라이브러리 #include <functional>에서 제공하는 템플릿 클래스다.
	std::function<void()>는 반환값이 없고 매개변수가 없는 함수 타입을 저장할 수 있다.
*/ #pragma endregion
	std::function<void()>	func;	// 호출할 함수를 저장하는 변수
#pragma region class CScene*
/*
	CScene 클래스의 전방 선언을 사용하여, 씬 객체의 포인터를 선언했다.
	이를 통해 CScene 클래스의 세부 구현을 포함한 헤더 파일을 직접적으로 포함하지 않고도
	포인터 변수를 선언하고 초기화할 수 있다.
*/
#pragma endregion
	class CScene* Scene = nullptr;  // 씬 객체의 포인터를 저장하는 변수
};

// 키 바인딩에 대한 정보를 담는 구조체
struct FBindKey	// FBindKeyInfoAndFunction
{
	std::string Name;
	FKeyInfo* Key	= nullptr;
	// Ctrl, Alt, Shift는 조합 키 입력을 위해 사용
	bool	Ctrl	= false;
	bool	Alt     = false;
	bool	Shift	= false;

#pragma region std::vector<FBindFunction*> vecFunction[EKeyType::Max];
/*
	std::vector<FBindFunction*> 타입으로 구성된 배열을 선언한다.
	배열의 크기는 EKeyType::Max 개수만큼이며, 각 요소는 독립적인 std::vector<FBindFunction*>를 가리킨다.
	각 vector는 필요에 따라 동적으로 메모리를 할당하여 FBindFunction* 포인터들을 저장할 수 있다.

	vecFunction[i]:		vecFunction 배열의 i번째 요소로 std::vector<FBindFunction*> 타입의 객체다.
	vecFunction[i][j]:	vecFunction[i] 벡터의 j번째 요소를 나타내며, 이는 FBindFunction* 타입의 포인터다.
*/
#pragma endregion
	std::vector<FBindFunction*> vecFunction[EKeyType::Max];	// 각 키 상태에 따라 함수 바인딩 정보를 관리하는 벡터 배열
};

class CInput
{
private:
	CInput();
	~CInput();

private:
#pragma region std::unordered_map
/* 
	키 - 값 쌍을 저장하는 해시 테이블. 
	키는 중복될 수 없으며, 각 키는 하나의 값과 연결된다.
*/
#pragma endregion
	std::unordered_map<SDL_Scancode, FKeyInfo*> mMapKeyInfo;
	std::unordered_map<std::string, FBindKey*>  mMapBindKey;
	bool	mCtrl	= false;
	bool	mAlt	= false;
	bool	mShift	= false;

public:
	bool Init();
	void Update();

private:
	void UpdateKeyInfo();
	void UpdateBindFunction();

private:
	FKeyInfo* FindKeyInfo(SDL_Scancode Key);
	FBindKey* FindBindKey(const std::string& Key);

public:
	bool CreateBindKey(const std::string& Key, SDL_Scancode Value);

public:
	// !AddBindFunction()이 template인 이유는, 등록할 클래스의 함수 타입을 알 수 없기 때문!
	// void (T::*Func)(): "void 리턴 타입의 인자가 없는" 클래스의 멤버 함수 포인터 타입의 매개변수
	template <typename T>
	void AddBindFunction(const std::string& Key, EKeyType::Type Type,
		T* Obj, void (T::*Func)(), class CScene* Scene)
	{
		FBindKey* BindKey = FindBindKey(Key);

		if (!BindKey)
			return;

		FBindFunction* Function = new FBindFunction;

		Function->Obj = Obj;
		Function->Scene = Scene;
#pragma region std::bind(Func, Obj)
/*
	std::bind는 C++ 표준 라이브러리 #include <functional>에서 제공하는 템플릿 클래스다.
	함수나 함수 객체를 다른 함수나 객체와 결합하여 새로운 함수 객체를 생성하는 역할을 한다.
	std::bind(Func, Obj)는 Func와 Obj를 결합하여, 새로운 함수 객체를 생성하고 
	이를 Function 구조체(또는 클래스)의 func 멤버 변수에 할당한다.

	Function->func()를 호출하면 Obj객체의 Func함수를 호출한다.
*/
#pragma endregion
		Function->func = std::bind(Func, Obj);

		BindKey->vecFunction[Type].push_back(Function);
	}

	template <typename T>
	void DeleteBindFunction(const std::string& Key, EKeyType::Type Type, T* Obj)
	{
		FBindKey* BindKey = FindBindKey(Key);

		if (!BindKey)
			return;

		// BindKey->vecFunction[Type].begin();는 FBindFunction*를 들고있는 iter 객체를 리턴해준다. 
		auto	iter = BindKey->vecFunction[Type].begin();	// 첫번째 추가된 노드를 가지고 있는 iter를 반환
		auto	iterEnd = BindKey->vecFunction[Type].end();	// 제일 마지막에 추가된 노드의 다음 노드를 가지고 있는 iter를 반환

		for (; iter != iterEnd;)
		{
#pragma region (*iter)->
/*
			*iter에서 *는 STL에서 사용되는 역참조 연산자다. 
			
			*iter는 iter 객체가 현재 저장하고 있는 "노드가 가지고 있는 값"을 의미한다.
			현재 노드가 가지고 있는 값은 FBindFunction*타입이다.
*/
#pragma endregion
			if ((*iter)->Obj == Obj)
			{
				SAFE_DELETE((*iter));
				iter = BindKey->vecFunction[Type].erase(iter);
				iterEnd = BindKey->vecFunction[Type].end();
				continue;
			}
			++iter;
		}
	}

private:
	static CInput* mInst;

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