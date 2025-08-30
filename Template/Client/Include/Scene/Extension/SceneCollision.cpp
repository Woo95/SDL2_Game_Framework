#include "SceneCollision.h"
#include "QuadTree.h"
#include "Camera.h"
#include "../../Entity/Component/Collider/Collider.h"
#include "../../Manager/PhysicsManager.h"

CSceneCollision::CSceneCollision(CCamera* camera) :
	mQuadTree(nullptr)
{
	mQuadTree = new CQuadTree(camera);
}

CSceneCollision::~CSceneCollision()
{
	SAFE_DELETE(mQuadTree);
}

void CSceneCollision::Update(float deltaTime)
{
	mQuadTree->Update(deltaTime);

	CleanPairs();
}

void CSceneCollision::Render(SDL_Renderer* renderer)
{
	mQuadTree->Render(renderer);
}

void CSceneCollision::AddCollider(CCollider* collider)
{
	mQuadTree->AddCollider(collider);
}

void CSceneCollision::HandleCollision(CCollider* collider1, CCollider* collider2)
{
	// collider 쌍을 key로 사용하여 상태를 가져옴 (없으면 enum의 첫 번째 값, EPair::DNE 자동 삽입)
	FColliderPair  pair = { collider1, collider2 };
	EPair::Status& status = mPairs[pair];

	if (status == EPair::DNE)
		status = EPair::NOT_COLLIDED;

	if (collider1->Intersect(collider2))
	{
		if (status == EPair::NOT_COLLIDED)
		{
			collider1->OnCollisionEnter(collider2);
			collider2->OnCollisionEnter(collider1);

			status = EPair::COLLIDED;
		}
		else
		{
			collider1->OnCollisionStay(collider2);
			collider2->OnCollisionStay(collider1);

			CPhysicsManager::GetInst()->ResolveOverlapIfPushable(collider1, collider2);
		}
	}
	else
	{
		if (status == EPair::COLLIDED)
		{
			collider1->OnCollisionExit(collider2);
			collider2->OnCollisionExit(collider1);
		}
		// 비충돌 pair는 제거
		mPairs.erase(pair);
	}
}

void CSceneCollision::CleanPairs()
{
	std::unordered_map<FColliderPair, EPair::Status>::iterator iter = mPairs.begin();
	std::unordered_map<FColliderPair, EPair::Status>::iterator iterEnd = mPairs.end();

	while (iter != iterEnd)
	{
		CCollider* collider1 = iter->first.collider1;
		CCollider* collider2 = iter->first.collider2;
		const EPair::Status& status = iter->second;

		if (!collider1->GetActive() || !collider2->GetActive())
		{
			if (status == EPair::COLLIDED)
			{
				collider1->OnCollisionExit(collider2);
				collider2->OnCollisionExit(collider1);
			}
			iter = mPairs.erase(iter);
			continue;
		}
		iter++;
	}
}