#include "Core/GameManager.h"

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")

int main(int argc, char* argv[])
{
    if (!CGameManager::GetInst()->Init())
    {
        CGameManager::DestroyInst();
        return 0;
    }

    int returnVal = CGameManager::GetInst()->Run();
    CGameManager::DestroyInst();

    return returnVal;
}