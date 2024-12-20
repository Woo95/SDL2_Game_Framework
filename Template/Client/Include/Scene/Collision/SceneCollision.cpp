#include "SceneCollision.h"
#include "QuadTree.h"
#include "../../Entity/Component/Collider.h"

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
	uintptr_t key = std::hash<CCollider*>()(collider1) ^ std::hash<CCollider*>()(collider2);
	bool& isColliding = mColliderPair[key];

	if (collider1->Collision(collider2))
	{
		if (!isColliding)
		{
			collider1->OnCollisionEnter(collider2);
			collider2->OnCollisionEnter(collider1);
			isColliding = true;
		}
		else
		{
			collider1->OnCollisionStay(collider2);
			collider2->OnCollisionStay(collider1);
		}
	}
	else
	{
		if (isColliding)
		{
			collider1->OnCollisionExit(collider2);
			collider2->OnCollisionExit(collider1);
			isColliding = false;
		}
	}
}