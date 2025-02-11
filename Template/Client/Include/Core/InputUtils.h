#pragma once

#include "GameInfo.h"

class CScene;

namespace EKey
{
	// 키 상태를 나타내는 열거형
	enum Type : unsigned char
	{
		Press,
		Hold,
		Release,
		MAX
	};
}

// 키 상태 정보를 담는 구조체
struct FKeyInfo
{
	// SDL_SCANCODE enum 값을 저장하는 Key 변수
	SDL_Scancode Key = SDL_SCANCODE_UNKNOWN;

	bool	Press    = false;
	bool	Hold     = false;
	bool	Release  = false;
};

// 바인드된 함수에 대한 정보를 담는 구조체
struct FBindFunction
{
	CScene* scene = nullptr;     // 씬 객체의 포인터를 저장하는 변수
	void*   obj   = nullptr;     // 모든 타입의 포인터를 범용적으로 저장하는 변수
	std::function<void()> func;  // 호출할 함수를 저장하는 변수
};

// 키 바인딩에 대한 정보를 담는 구조체
struct FBindKey	// FBindKeyInfoAndFunction
{
	std::string Name;
	FKeyInfo* Key = nullptr;
	// Ctrl, Alt, Shift는 조합 키 입력을 위해 사용
	bool	Ctrl  = false;
	bool	Alt   = false;
	bool	Shift = false;

#pragma region std::vector<FBindFunction*> vecFunction[EKey::Type::MAX];
	/*
		std::vector<FBindFunction*> 타입으로 구성된 배열을 선언한다.
		배열의 크기는 EKeyType::MAX 개수만큼이며, 각 요소는 독립적인 std::vector<FBindFunction*>를 가리킨다.
		각 vector는 필요에 따라 동적으로 메모리를 할당하여 FBindFunction* 포인터들을 저장할 수 있다.

		vecFunction[i]:		vecFunction 배열의 i번째 요소로 std::vector<FBindFunction*> 타입의 객체다.
		vecFunction[i][j]:	vecFunction[i] 벡터의 j번째 요소를 나타내며, 이는 FBindFunction* 타입의 포인터다.
	*/
#pragma endregion
	std::vector<FBindFunction*> vecFunction[EKey::Type::MAX];	// 각 키 상태에 따라 함수 바인딩 정보를 관리하는 벡터 배열
};