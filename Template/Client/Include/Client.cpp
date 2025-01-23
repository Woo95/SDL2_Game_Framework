#include "Manager/GameManager.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")

int main(int argc, char* argv[])
{
    // 메모리 할당 문제를 디버그할 때 사용한다.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // 특정 할당 요청 번호에서 중단점을 설정한다.
    //_CrtSetBreakAlloc(5900);

    if (!CGameManager::GetInst()->Init())
    {
        CGameManager::DestroyInst();
        return 0;
    }

    int returnVal = CGameManager::GetInst()->Run();
    CGameManager::DestroyInst();

    return returnVal;
}