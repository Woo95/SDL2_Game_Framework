#pragma once

#include "External/SDL/SDL.h"
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <typeinfo>
#include <crtdbg.h>     // 디버깅 도구 제공, 메모리 누수 감지 등
#include <functional>   // 함수 포인터를 쉽게 쓰기 위한 기능들
#include <unordered_map>
#include <memory>       // for smartPtr
#include <typeindex>

#define	SAFE_DELETE(p) if(p) { delete p; p = nullptr; }

#define BASE_PATH       "BasePath"
#define TEXTURE_PATH    "TexturePath"
#define SOUND_PATH      "SoundPath"