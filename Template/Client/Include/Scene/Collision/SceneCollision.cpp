#include "SceneCollision.h"
#include "QuadTree.h"
#include "../../Entity/Component/Collider/Collider.h"

CSceneCollision::CSceneCollision(int width, int height)	:
	mWidth(width),
	mHeight(height)
{
	mQuadTree = new CQuadTree;

	mQuadTree->Init((float)mWidth, (float)mHeight);
}

CSceneCollision::~CSceneCollision()
{
	SAFE_DELETE(mQuadTree);
}

void CSceneCollision::Update(float DeltaTime)
{
	mQuadTree->Update(DeltaTime);

	CleanPairs();
}

void CSceneCollision::LateUpdate(float DeltaTime)
{
}

void CSceneCollision::Render(SDL_Renderer* Renderer)
{
	mQuadTree->Render(Renderer);
}

void CSceneCollision::AddCollider(CCollider* collider)
{
	mQuadTree->AddCollider(collider);
}

void CSceneCollision::CleanPairs()
{
	std::unordered_map<FColliderPair, bool>::iterator iter    = mPairs.begin();
	std::unordered_map<FColliderPair, bool>::iterator iterEnd = mPairs.end();

	while (iter != iterEnd)
	{
		CCollider* collider1 = iter->first.collider1;
		CCollider* collider2 = iter->first.collider2;

		if (collider1->GetActive() == false ||
			collider2->GetActive() == false)
		{
			collider1->OnCollisionExit(collider2);
			collider2->OnCollisionExit(collider1);

			iter = mPairs.erase(iter);
			continue;
		}
		iter++;
	}
}

void CSceneCollision::HandleCollision(CCollider* collider1, CCollider* collider2)
{
	FColliderPair pair = { collider1, collider2 };
	
	// pair가 존재하지 않을 경우
	if (mPairs.find(pair) == mPairs.end())
	{
		mPairs[pair] = false;
	}

	if (collider1->Intersect(collider2))
	{
		if (mPairs[pair] == false)
		{
			collider1->OnCollisionEnter(collider2);
			collider2->OnCollisionEnter(collider1);

			mPairs[pair] = true;
		}
		else
		{
			collider1->OnCollisionStay(collider2);
			collider2->OnCollisionStay(collider1);
		}
	}
	else
	{
		if (mPairs[pair] == true)
		{
			collider1->OnCollisionExit(collider2);
			collider2->OnCollisionExit(collider1);

			mPairs.erase(pair);
		}
	}
}