#pragma once

#include "../../Core/GameInfo.h"

class CCollider;

class CSceneCollision
{
	friend class CScene;

public:
	CSceneCollision() = delete;	// 기본 생성자 사용 못하게 방지.
	CSceneCollision(int width, int height);
	~CSceneCollision();

private:
	class CQuadTree* mQuadTree;

	std::unordered_map<uintptr_t, bool> mColliderPair;

	int mWidth;
	int mHeight;

public:
	void Update(float DeltaTime);
	void Render(SDL_Renderer* Renderer);

public:
	void AddCollider(CCollider* collider);
	void HandleCollision(CCollider* collider1, CCollider* collider2);
};