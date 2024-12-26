#include "MemoryReleaseManager.h"
#include "../Entity/Object/Object.h"
#include "../Entity/Component/Component.h"

CMemoryReleaseManager* CMemoryReleaseManager::mInst = nullptr;

CMemoryReleaseManager::CMemoryReleaseManager()
{
}

CMemoryReleaseManager::~CMemoryReleaseManager()
{
	for (size_t i = mGarbage.size(); i > 0; i--)
	{
		DataContainer* ptr = mGarbage[i - 1];

		std::swap(mGarbage[i - 1], mGarbage.back());
		mGarbage.pop_back();

		ptr->Release();
	}
}

void CMemoryReleaseManager::Update(float DeltaTime)
{
	for (size_t i = mGarbage.size(); i > 0; i--)
	{
		DataContainer* ptr = mGarbage[i - 1];

		std::swap(mGarbage[i - 1], mGarbage.back());
		mGarbage.pop_back();

		ptr->Release();
	}
}