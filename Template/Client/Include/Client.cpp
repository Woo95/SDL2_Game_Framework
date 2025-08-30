#include <windows.h>
#include "Engine.h"

class CClient
{
private:
	CClient()  = delete;
	~CClient() = delete;

public:
	static void Launch()
	{
		// 기본적으로 콘솔 창 숨기기
		ShowWindow(GetConsoleWindow(), SW_HIDE);

#ifdef _DEBUG
		// 디버그 모드에서 콘솔 창 표시
		ShowWindow(GetConsoleWindow(), SW_SHOW);

		// 메모리 할당 문제를 디버그할 때 사용
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		// 특정 할당 요청 번호에서 중단점을 설정
		//_CrtSetBreakAlloc(5900);
#endif

		if (CEngine::GetInst()->Init())
			CEngine::GetInst()->Run();

		CEngine::DestroyInst();
	}
};

int main(int argc, char* argv[])
{
    CClient::Launch();

	return 0;
}