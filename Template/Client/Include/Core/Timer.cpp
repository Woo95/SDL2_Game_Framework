#include "Timer.h"

Uint64 CTimer::mSecond;
Uint64 CTimer::mTime;
float  CTimer::mDeltaTime = 0.0f;

float CTimer::mFPS = 0.0f;
float CTimer::mFPSTime = 0.0f;
int   CTimer::mFPSTick = 0;

bool CTimer::Init()
{
    // 초당 고해상도 타이머가 얼마나 동작하는지 얻어온다.
    mSecond = SDL_GetPerformanceFrequency();

    // 고해상도 타이머의 현재 값을 받아온다.
    mTime = SDL_GetPerformanceCounter();

    return true;
}

void CTimer::Update()
{
    UpdateDeltaTime();
    UpdateFPS();
}

void CTimer::UpdateDeltaTime()
{
    // 윈도우 고해상도 타이머를 얻어온다.  (매우 작은 시간 간격을 측정할 수 있는 타이머)
    Uint64 time = SDL_GetPerformanceCounter();
#pragma region DeltaTime Explanation
    /*
    Time:       현재 프레임의 타이머 틱 값
    mTime:      이전 프레임의 타이머 틱 값
    mSecond:    타이머가 1초 동안 구성하는 틱 수 (1초 동안의 틱 총 수 (고정된 숫자))

    mDeltaTime = (현재 프레임의 틱 값 - 이전 프레임의 틱 값) / (1초 동안의 타이머 틱 수)
    dt = 다음 1 프레임까지 걸린 시간 (초 단위) | (1 프레임은 프로그램의 한 사이클을 의미)
    */
#pragma endregion
    mDeltaTime = (time - mTime) / (float)mSecond;

    mTime = time;
}

void CTimer::UpdateFPS()
{
    // 누적 시간에 현재 프레임의 경과 시간 추가
    mFPSTime += mDeltaTime;

    // 프레임 카운트를 증가
    ++mFPSTick;

    // 60 프레임이 경과했을 때 FPS를 계산
    if (mFPSTick == 60)
    {
        // 60 프레임 동안 걸린 시간으로 FPS를 계산
        mFPS = mFPSTick / mFPSTime;

        // FPS 계산을 위해 누적 시간과 프레임 카운트 초기화
        mFPSTime = 0.f;
        mFPSTick = 0;
    }
}