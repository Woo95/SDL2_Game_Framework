#pragma once

#include "../GameInfo.h"

//////////////////////////////////////////////////////////////////////////////////////////

                              ///// MOUSE & KEYBOARDS /////

// 키 액션 타입을 나타내는 열거형
enum class EKeyAction : unsigned char
{
	PRESS,
	HOLD,
	RELEASE,
	MAX
};

// 단일 입력상태 정보를 담는 구조체
struct FKeyState
{
	bool Press   = false;
	bool Hold    = false;
	bool Release = false;
};

//////////////////////////////////////////////////////////////////////////////////////////

// 바인드된 함수에 대한 정보를 담는 구조체
struct FBindFunction
{
	void* obj = nullptr; // 모든 타입의 포인터를 범용적으로 저장하는 변수
	std::function<void()> func; // 호출할 함수를 저장하는 변수
};

// 키보드와 마우스 입력값을 조합하고 해당 입력에 대한 동작(함수)을 묶어주는 구조체
struct FBinder
{
	std::vector<std::pair<SDL_Scancode, EKeyAction>> Keys;
	std::vector<std::pair<Uint8, EKeyAction>> Mouses;

	std::vector<FBindFunction*> Functions;
};