#include "SceneCollision.h"
#include "QuadTree.h"
#include "../Camera.h"
#include "../../Entity/Object/Object.h"
#include "../../Entity/Component/Collider/Collider.h"
#include "../../Manager/PhysicsManager.h"
#include "../../Entity/Component/Rigidbody.h"

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

			ResolveOverlapIfPushable(collider1, collider2);
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

// "Pushable Object": DYNAMIC Rigidbody이며, 상대 Collider와 BLOCK 상호작용일 때 
void CSceneCollision::ResolveOverlapIfPushable(CCollider* collider1, CCollider* collider2)
{
	FCollisionProfile* profile1 = collider1->GetProfile();
	FCollisionProfile* profile2 = collider2->GetProfile();

	ECollision::Interaction response1to2 = profile1->collisionResponses[profile2->channel];
	ECollision::Interaction response2to1 = profile2->collisionResponses[profile1->channel];

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