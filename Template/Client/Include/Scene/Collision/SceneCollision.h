#pragma once

#include "../../Core/GameInfo.h"
#include "../../Core/ColliderPair.h"

class CCollider;
class CCamera;
class CQuadTree;

class CSceneCollision
{
	friend class CScene;

public:
	CSceneCollision() = delete;	// 기본 생성자 사용 못하게 방지.
	CSceneCollision(CCamera* camera);
	~CSceneCollision();

private:
	CQuadTree* mQuadTree;

	std::unordered_map<FColliderPair, EPair::Status> mPairs;

public:
	void Update(float DeltaTime);
	void Render(SDL_Renderer* Renderer);

public:
	void AddCollider(CCollider* collider);
	void CleanPairs();
	void HandleCollision(CCollider* collider1, CCollider* collider2);
};