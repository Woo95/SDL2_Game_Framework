#pragma once

#include "External/SDL/SDL.h"
#include <iostream>
#include <string>
#include <list>
#include <typeinfo>
#include <vector>
#include <crtdbg.h>     // 디버깅 도구 제공, 메모리 누수 감지 등
#include <functional>   // 함수 포인터를 쉽게 쓰기 위한 기능들
#include <unordered_map>
#include <math.h>
#include "SharedPtr.h"

#define	SAFE_DELETE(p) if(p) { delete p; p = nullptr; }
#define	SAFE_RELEASE(p)	if(p)	{ p->Release(); p = nullptr; }