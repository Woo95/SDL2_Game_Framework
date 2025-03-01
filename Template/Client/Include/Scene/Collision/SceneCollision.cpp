#include "SceneCollision.h"
#include "QuadTree.h"
#include "../../Entity/Component/Collider/Collider.h"
#include "../Camera.h"

CSceneCollision::CSceneCollision(CCamera* camera)
{
	mQuadTree = new CQuadTree(camera);
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
	std::unordered_map<FColliderPair, EPair::Status>::iterator iter    = mPairs.begin();
	std::unordered_map<FColliderPair, EPair::Status>::iterator iterEnd = mPairs.end();

	while (iter != iterEnd)
	{
		CCollider* collider1 = iter->first.collider1;
		CCollider* collider2 = iter->first.collider2;

		if (iter->second == EPair::COLLIDED)
		{
			if (!collider1->GetActive() || !collider2->GetActive())
			{
				collider1->OnCollisionExit(collider2);
				collider2->OnCollisionExit(collider1);
			}
		}
		else if (iter->second == EPair::NOT_COLLIDED)
		{
			if (!collider1->GetActive()) collider1->OnCollisionExit(collider2);
			if (!collider2->GetActive()) collider2->OnCollisionExit(collider1);
		}

		if (!collider1->GetActive() || !collider2->GetActive())
		{
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
		mPairs[pair] = EPair::NOT_COLLIDED;
	}

	if (collider1->Intersect(collider2))
	{
		if (mPairs[pair] == EPair::NOT_COLLIDED)
		{
			collider1->OnCollisionEnter(collider2);
			collider2->OnCollisionEnter(collider1);

			mPairs[pair] = EPair::COLLIDED;
		}
		else
		{
			collider1->OnCollisionStay(collider2);
			collider2->OnCollisionStay(collider1);
		}
	}
	else
	{
		if (mPairs[pair] == EPair::COLLIDED)
		{
			collider1->OnCollisionExit(collider2);
			collider2->OnCollisionExit(collider1);

			mPairs.erase(pair);
		}
	}
}