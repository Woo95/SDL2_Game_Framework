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

void CSceneCollision::LateUpdate(float DeltaTime)
{
	mQuadTree->LateUpdate(DeltaTime);
}

void CSceneCollision::Render(SDL_Renderer* Renderer)
{
	mQuadTree->Render(Renderer);
}

void CSceneCollision::AddCollider(CCollider* collider)
{
	mQuadTree->AddCollider(collider);
}