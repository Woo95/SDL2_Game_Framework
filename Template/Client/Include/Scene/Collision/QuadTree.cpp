#include "QuadTree.h"
#include "QTNode.h"
#include "../Camera.h"
#include "../../Entity/Component/Collider/Collider.h"
#include "../../Manager/MemoryPoolManager.h"

CQuadTree::CQuadTree(CCamera* camera) :
	mRoot(nullptr)
{
	int totalNodes = (int)((pow(4, MAX_SPLIT + 1) - 1) / 3);
	CMemoryPoolManager::GetInst()->CreatePool<CQTNode>(totalNodes);

	if (!mRoot)
		mRoot = CMemoryPoolManager::GetInst()->Allocate<CQTNode>();

	mRoot->mCamera = camera;
}

CQuadTree::~CQuadTree()
{
	CMemoryPoolManager::GetInst()->Deallocate<CQTNode>(mRoot);
	CMemoryPoolManager::GetInst()->DeletePool<CQTNode>();
}

void CQuadTree::Update(float deltaTime)
{
	UpdateBoundary();

	for (size_t i = mColliders.size(); i > 0; i--)
	{
		CCollider* collider = mColliders[i - 1];
		
		if (!collider->GetActive())
		{
			std::swap(mColliders[i - 1], mColliders.back());
			mColliders.pop_back();

			continue;
		}
		else if (!collider->GetEnable())
		{
			continue;
		}
		mRoot->AddCollider(collider);
	}
	mRoot->Update(deltaTime);
}

void CQuadTree::Render(SDL_Renderer* renderer)
{
	mRoot->Render(renderer);

	// 디버그용으로 Render()에서 호출하지만 실제 호출은 LateUpdate()
	mRoot->Clear();
}

void CQuadTree::AddCollider(CCollider* collider)
{
	mColliders.emplace_back(collider);
}

void CQuadTree::UpdateBoundary()
{
	const FVector2D& target = mRoot->mCamera->GetLookAt();
	const FVector2D& screen = mRoot->mCamera->GetResolution();

	mRoot->mBoundary = 
	{ 
		target.x - screen.x * 0.5f,
		target.y - screen.y * 0.5f,
		screen.x,
		screen.y
	};
}