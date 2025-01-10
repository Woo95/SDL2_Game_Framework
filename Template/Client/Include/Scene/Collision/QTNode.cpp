#include "QTNode.h"
#include "QuadTree.h"
#include "../../Entity/Component/BoxCollider.h"
#include "../../Entity/Component/CircleCollider.h"
#include "../../Entity/Object/Object.h"
#include "../../Scene/Collision/SceneCollision.h"

CQTNode::CQTNode()
{
}

CQTNode::~CQTNode()
{
}

void CQTNode::Update(float DeltaTime)
{
	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			mChilds[i]->Update(DeltaTime);
		}
	}
	else
	{
		size_t size = mColliders.size();
		if (size >= 2)
		{
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = i + 1; j < size; j++)
				{
					FCollisionProfile* profile1 = mColliders[i]->GetProfile();
					FCollisionProfile* profile2 = mColliders[j]->GetProfile();

					if (profile1->mInteractArr[profile2->mChannel] == ECollisionInteraction::DISABLE_COLLISION ||
						profile2->mInteractArr[profile1->mChannel] == ECollisionInteraction::DISABLE_COLLISION)
					{
						continue;
					}
					if (mColliders[i]->Intersect(mColliders[j]))
					{
						mColliders[i]->OnCollision(mColliders[j]);
						mColliders[j]->OnCollision(mColliders[i]);
					}
				}
			}
		}
	}
}

void CQTNode::Render(SDL_Renderer* Renderer)
{
#ifdef _DEBUG	
	// 렌더 색상 설정
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	// 사각형 그리기
	SDL_RenderDrawRectF(Renderer, &mBoundary);

	if (HasChild())
	{
		for (int i = 0; i < 4; ++i)
		{
			mChilds[i]->Render(Renderer);
		}
	}
#endif
}

bool CQTNode::HasChild()
{
	return mChilds[0] != nullptr;
}

bool CQTNode::ShouldSplit()
{
	return mColliders.size() > MAX_COLLIDERS_PER_NODE && mDepthLevel < mMaxDepth;
}

void CQTNode::Split()
{
	float halfW = mBoundary.w * 0.5f;
	float halfH = mBoundary.h * 0.5f;

	float x[2] = { mBoundary.x, mBoundary.x + halfW };
	float y[2] = { mBoundary.y, mBoundary.y + halfH };

	for (int i = 0; i < 4; i++)
	{
		mChilds[i] = CMemoryPoolManager::GetInst()->Allocate<CQTNode>();

		mChilds[i]->mParent	    = this;
		mChilds[i]->mBoundary   = { x[i % 2], y[i / 2], halfW, halfH };
		mChilds[i]->mDepthLevel = mDepthLevel + 1;
		mChilds[i]->mMaxDepth   = mMaxDepth;
	}
}

bool CQTNode::IsWithinNode(CCollider* collider)
{
	if (collider->GetColliderType() == ECollider::Type::BOX)
	{
		const SDL_FRect& box1 = mBoundary;
		const SDL_FRect& box2 = ((CBoxCollider*)collider)->GetRect();

		if (box1.x + box1.w < box2.x ||
			box1.x > box2.x + box2.w ||
			box1.y + box1.h < box2.y ||
			box1.y > box2.y + box2.h)
		{
			return false;
		}
		return true;
	}
	else if (collider->GetColliderType() == ECollider::Type::CIRCLE)
	{
		const SDL_FRect& box  = mBoundary;
		const FCircle& circle = ((CCircleCollider*)collider)->GetCircle();

		FVector2D closestPointOnBox = circle.center.Clamp(box.x, box.x + box.w, box.y + box.h, box.y);

		float distance = circle.center.Distance(closestPointOnBox);

		if (circle.radius < distance)
		{
			return false;
		}
		return true;
	}
	return false;
}

void CQTNode::AddCollider(CCollider* collider)
{
	if (!IsWithinNode(collider))
		return;

	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			if (mChilds[i]->IsWithinNode(collider))
			{
				mChilds[i]->AddCollider(collider);
			}
		}
	}
	else
	{
		mColliders.push_back(collider);

		if (ShouldSplit())
		{
			Split();

			MoveCollidersToChildren();
		}
	}
}

void CQTNode::MoveCollidersToChildren()
{
	for (size_t i = mColliders.size(); i > 0; i--)
	{
		CCollider* collider = mColliders[i - 1];
		for (int j = 0; j < 4; j++)
		{
			if (mChilds[j]->IsWithinNode(collider))
			{
				mChilds[j]->mColliders.push_back(collider);
			}
		}
		mColliders.pop_back();
	}
	mColliders.clear();
}

void CQTNode::Clear()
{
	if (HasChild())
	{
		for (int i = 0; i < 4; i++)
		{
			mChilds[i]->Clear();
			mChilds[i] = nullptr;
		}
	}
	mColliders.clear();

	if (mParent)
		CMemoryPoolManager::GetInst()->Deallocate<CQTNode>(this);
}