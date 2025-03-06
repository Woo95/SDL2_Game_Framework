#include "SpriteComponent.h"
#include "../../Manager/Resource/AssetManager.h"
#include "../../Manager/Resource/TextureManager.h"
#include "../../Manager/Resource/SpriteManager.h"
#include "../../Manager/Resource/AnimationManager.h"
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
}

CSpriteComponent::~CSpriteComponent()
{
	mTexture = nullptr;
	
	if (mAnimation)
		mAnimation->Release();
}

bool CSpriteComponent::Init()
{
	return CComponent::Init();
}

void CSpriteComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	if (mAnimation)
		mAnimation->Update(DeltaTime);
}

void CSpriteComponent::LateUpdate(float DeltaTime)
{
	CComponent::LateUpdate(DeltaTime);
}

void CSpriteComponent::Render(SDL_Renderer* Renderer)
{
	CComponent::Render(Renderer);

	if (mTexture)
	{
		const SDL_Rect& frame = GetFrame();
		const SDL_Rect  dest  = GetDest();

		SDL_RenderCopyEx(Renderer, mTexture.get()->GetTexture(), &frame, &dest, 0.0, nullptr, mFlip);
	}
}

void CSpriteComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSpriteComponent>(this);
}

void CSpriteComponent::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
}

void CSpriteComponent::SetSprite(const std::string& key)
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
	// 월드 좌표와 스케일을 사용해 좌상단 좌표 계산
	const FVector2D& scale = mTransform->GetWorldScale();
	FVector2D topLeft = mTransform->GetWorldPos() - mTransform->GetPivot() * scale;

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	CCamera* camera = GetObject()->GetScene()->GetCamera();
	if (camera)
		topLeft = camera->GetRenderPos(topLeft);

	// 사각형 정보 생성
	return { (int)topLeft.x, (int)topLeft.y, (int)scale.x, (int)scale.y };
}