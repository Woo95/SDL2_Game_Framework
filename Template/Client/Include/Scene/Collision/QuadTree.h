#pragma once

#include "QTNode.h"

class CCollider;
class CCamera;

class CQuadTree
{
	friend class CSceneCollision;

private:
	CQuadTree() = delete;	// 기본 생성자 사용 못하게 방지.
	CQuadTree(CCamera* camera);
	~CQuadTree();

private:
	CQTNode* mRoot = nullptr;
	std::vector<CCollider*> mColliders;

public:
	void Update(float DeltaTime);
	void Render(SDL_Renderer* Renderer);

public:
	void AddCollider(CCollider* collider);

private:
	void UpdateBoundary();
};