#include "QuadTree.h"
#include "../../Core/Vector2D.h"
#include "../../Entity/Component/Collider/Collider.h"
#include "../../Manager/MemoryPoolManager.h"

CQuadTree::CQuadTree() :
	mRoot(nullptr),
	MAX_DEPTH(0)
{
}

CQuadTree::~CQuadTree()
{
	CMemoryPoolManager::GetInst()->Deallocate<CQTNode>(mRoot);
	CMemoryPoolManager::GetInst()->DeletePool<CQTNode>();
}

void CQuadTree::Init(float width, float height)
{
	CreateNodePool(width, height);

	if (!mRoot)
		mRoot = CMemoryPoolManager::GetInst()->Allocate<CQTNode>();

	mRoot->mBoundary = { 0, 0, width, height };
	mRoot->mMaxDepth = MAX_DEPTH;
}

void CQuadTree::Update(float DeltaTime)
{
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
	mRoot->Update(DeltaTime);
}

void CQuadTree::Render(SDL_Renderer* Renderer)
{
	mRoot->Render(Renderer);

	mRoot->Clear();
}

void CQuadTree::AddCollider(CCollider* collider)
{
	mColliders.push_back(collider);
}

void CQuadTree::CreateNodePool(float width, float height)
{
	int area = (int)(width * height);

	MAX_DEPTH = 3; // temporary depth

	/*
	// approximately optimal depth for each area
	if (area < 1000000)
		MAX_DEPTH = 1;
	else if (area < 2500000)
		MAX_DEPTH = 2;
	else if (area < 5000000)
		MAX_DEPTH = 3;
	*/

	int totalNodes = (int)((pow(4, MAX_DEPTH + 1) - 1) / 3);
	CMemoryPoolManager::GetInst()->CreatePool<CQTNode>(totalNodes);
}