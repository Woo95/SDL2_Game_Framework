#pragma once

#include "QTNode.h"

class CQuadTree
{
	friend class CSceneCollision;

private:
	CQuadTree();
	~CQuadTree();

private:
	CQTNode* mRoot = nullptr;
	std::vector<class CCollider*> mColliders;

	int MAX_DEPTH;

public:
	void Init(float width, float height);
	void Update(float DeltaTime);
	void Render(SDL_Renderer* Renderer);

public:
	void AddCollider(CCollider* collider);

private:
	void CreateNodePool(float width, float height);
};