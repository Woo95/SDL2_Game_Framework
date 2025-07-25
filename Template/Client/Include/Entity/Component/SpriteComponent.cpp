#include "SpriteComponent.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/TextureManager.h"
#include "../../Manager/Data/Resource/SpriteManager.h"
#include "../../Manager/Data/Resource/AnimationManager.h"
#include "../../Resource/Texture.h"
#include "../../Resource/Animation.h"
#include "../Object/Object.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Camera.h"

CSpriteComponent::CSpriteComponent() :
	mTexture(nullptr),
	mFrame({}),
	mAnimation(nullptr),
	mFlip(SDL_FLIP_NONE)
{
	mTypeID = typeid(CSpriteComponent).hash_code();
}

CSpriteComponent::~CSpriteComponent()
{
	mTexture = nullptr;
	
	if (mAnimation)
		mAnimation->Release();
}

void CSpriteComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	if (mAnimation)
		mAnimation->Update(deltaTime);
}

void CSpriteComponent::Render(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		const SDL_Rect& frame = GetFrame();
		const SDL_Rect  dest  = GetDest();

		SDL_RenderCopyEx(renderer, mTexture.get()->GetTexture(), &frame, &dest, 0.0, nullptr, mFlip);
	}

	CComponent::Render(renderer);
}

void CSpriteComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSpriteComponent>(this);
}

void CSpriteComponent::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->GetTexture(key);
}

void CSpriteComponent::SetFrame(const std::string& key)
{
	const SDL_Rect* const framePtr = CAssetManager::GetInst()->GetSpriteManager()->GetSpriteFrame(key);

	mFrame = *framePtr;
}

void CSpriteComponent::SetAnimation(const std::string& key)
{
	CAnimation* base = CAssetManager::GetInst()->GetAnimationManager()->GetAnimation(key);

	if (base)
	{
		mAnimation = base->Clone();
		mAnimation->mOwner = this;
	}
}

const SDL_Rect& CSpriteComponent::GetFrame() const
{
	return mAnimation ? mAnimation->GetCurrentFrame() : mFrame;
}

const SDL_Rect CSpriteComponent::GetDest() const
{
	// 월드 스케일, 위치, 피벗을 반환
	const FVector2D& scale = mTransform->GetWorldScale();
	const FVector2D& pos   = mTransform->GetWorldPos();
	const FVector2D& pivot = mTransform->GetPivot();

	// 좌상단 좌표 계산
	FVector2D topLeft = pos - pivot * scale;

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	if (CCamera* camera = GetObject()->GetScene()->GetCamera())
		topLeft = camera->GetRenderPos(topLeft);

	// 사각형 정보 생성
	return { (int)topLeft.x, (int)topLeft.y, (int)scale.x, (int)scale.y };
}