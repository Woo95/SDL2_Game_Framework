#pragma once

#include "../../Core/GameInfo.h"

#define MAX_COLLIDERS_PER_NODE 10

class CQTNode
{
	friend class CQuadTree;

public:
	CQTNode();
	~CQTNode();

private:
	CQTNode* mParent = nullptr;
	CQTNode* mChilds[4] = {};
	std::vector<class CCollider*> mColliders;

	SDL_FRect mBoundary = {};

	int mDepthLevel = 0;
	int mMaxDepth   = 0;

public:
	void Update(float DeltaTime);
	void Render(SDL_Renderer* Renderer);

public:
	bool HasChild();
	bool ShouldSplit();
	void Split();

	bool IsWithinNode(CCollider* collider);
	void AddCollider(CCollider* collider);

	void MoveCollidersToChildren();

	void Clear();
};