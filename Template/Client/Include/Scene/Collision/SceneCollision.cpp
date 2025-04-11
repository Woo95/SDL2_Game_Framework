#include "SceneCollision.h"
#include "QuadTree.h"
#include "../../Entity/Component/Collider/Collider.h"
#include "../../Entity/Component/Rigidbody.h"
#include "../Camera.h"
#include "../../Entity/Object/Object.h"
#include "../../Manager/PhysicsManager.h"

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

void CSceneCollision::HandleCollision(CCollider* collider1, CCollider* collider2)
{
	FColliderPair  pair = { collider1, collider2 };
	EPair::Status& status = mPairs[pair]; // pair가 없으면 EPair::DNE(=enum 첫 값)으로 자동 삽입

	if (status == EPair::DNE)
		status = EPair::NOT_COLLIDED;

	if (collider1->Intersect(collider2))
	{
		if (status == EPair::NOT_COLLIDED)
		{
			collider1->OnCollisionEnter(collider2);
			collider2->OnCollisionEnter(collider1);

			status = EPair::COLLIDED;

			// behaviour for the rigidbody
			ResolveOverlapIfPushable(collider1, collider2);
		}
		else
		{
			collider1->OnCollisionStay(collider2);
			collider2->OnCollisionStay(collider1);
		}
	}
	else
	{
		if (status == EPair::COLLIDED)
		{
			collider1->OnCollisionExit(collider2);
			collider2->OnCollisionExit(collider1);

			mPairs.erase(pair);
		}
	}
}

void CSceneCollision::ResolveOverlapIfPushable(CCollider* collider1, CCollider* collider2)
{
	FCollisionProfile* profile1 = collider1->GetProfile();
	FCollisionProfile* profile2 = collider2->GetProfile();

	ECollision::Interaction response1to2 = profile1->collisionResponses[profile2->channel];
	ECollision::Interaction response2to1 = profile2->collisionResponses[profile1->channel];

	// Unity: 양쪽 모두 Block이 아닌 경우, 물리반응 발생 X
	if (response1to2 != ECollision::Interaction::BLOCK && response2to1 != ECollision::Interaction::BLOCK)
		return;

	// Unreal: 양쪽 모두 Overlap인 경우, 물리반응 발생 X
	//if (response1to2 == ECollision::Interaction::OVERLAP && response2to1 == ECollision::Interaction::OVERLAP)
	//	return;

	CRigidbody* rb1 = nullptr;
	CRigidbody* rb2 = nullptr;

	if (response1to2 == ECollision::Interaction::BLOCK)
		rb1 = collider1->GetObject()->GetComponent<CRigidbody>();

	if (response2to1 == ECollision::Interaction::BLOCK)
		rb2 = collider2->GetObject()->GetComponent<CRigidbody>();

	bool pushObj1 = rb1 != nullptr && rb1->GetType() == ERigidbodyType::DYNAMIC;
	bool pushObj2 = rb2 != nullptr && rb2->GetType() == ERigidbodyType::DYNAMIC;

	// 양쪽 모두 밀지 않아도 될 경우, 물리반응 발생 X
	if (!pushObj1 && !pushObj2)
		return;

	CPhysicsManager::GetInst()->ResolveOverlap(collider1, collider2, pushObj1, pushObj2);
}

void CSceneCollision::CleanPairs()
{
	std::unordered_map<FColliderPair, EPair::Status>::iterator iter = mPairs.begin();
	std::unordered_map<FColliderPair, EPair::Status>::iterator iterEnd = mPairs.end();

	while (iter != iterEnd)
	{
		CCollider* collider1  = iter->first.collider1;
		CCollider* collider2  = iter->first.collider2;
		EPair::Status& status = iter->second;

		if (status == EPair::COLLIDED)
		{
			if (!collider1->GetActive() || !collider2->GetActive())
			{
				collider1->OnCollisionExit(collider2);
				collider2->OnCollisionExit(collider1);
			}
		}
		else if (status == EPair::NOT_COLLIDED)
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