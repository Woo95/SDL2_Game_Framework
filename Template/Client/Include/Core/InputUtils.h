#pragma once

#include "GameInfo.h"

class CScene;

typedef bool Ctrl;
typedef bool Alt;
typedef bool Shift;

//////////////////////////////////////////////////////////////////////////////////////////

                                    ///// STATES /////

namespace EInput
{
	enum Type : unsigned char
	{
		MOUSE,
		KEYBOARD
	};
}

namespace EKey
{
	// 키 상태를 나타내는 열거형
	enum State : unsigned char
	{
		PRESS,
		HOLD,
		RELEASE,
		MAX
	};
}

//////////////////////////////////////////////////////////////////////////////////////////

                              ///// MOUSE & KEYBOARDS /////

// 바인드된 함수에 대한 정보를 담는 구조체 //
struct FBindFunction
{
	CScene* scene = nullptr;    // 씬 객체의 포인터를 저장하는 변수
	void*   obj   = nullptr;    // 모든 타입의 포인터를 범용적으로 저장하는 변수
	std::function<void()> func; // 호출할 함수를 저장하는 변수
};

//////////////////////////////////////////////////////////////////////////////////////////

                                    ///// MOUSE /////

// "특정" 마우스 버튼 상태 정보 + 마우스 바인딩 정보를 담는 구조체
struct FMouse
{
	// current mouse state
	bool Press   = false;
	bool Hold    = false;
	bool Release = false;

	// std::tuple<Ctrl, Alt, Shift> - mouse binds
	std::map<std::tuple<Ctrl, Alt, Shift>, std::vector<FBindFunction*>> Actions[EKey::State::MAX];
};

//////////////////////////////////////////////////////////////////////////////////////////

                                    ///// KEYBOARDS /////

// "특정" 키 상태 정보 + 키 바인딩 정보를 담는 구조체
struct FKey
{
	// current key state
	bool Press   = false;
	bool Hold    = false;
	bool Release = false;

	// modifierKey bindings for the specific key
	std::map<std::tuple<Ctrl, Alt, Shift>, std::vector<FBindFunction*>> Actions[EKey::State::MAX];
};

//////////////////////////////////////////////////////////////////////////////////////////