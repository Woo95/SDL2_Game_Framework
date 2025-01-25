#include "SpriteComponent.h"
#include "../../../Manager/Resource/AssetManager.h"
#include "../../../Manager/Resource/TextureManager.h"
#include "../../../Manager/Resource/AnimationManager.h"
#include "../../../Resource/Texture.h"
#include "../../../Resource/Animation.h"

CSpriteComponent::CSpriteComponent() :
	mTexture(nullptr),
	mAnimation(nullptr),
	mFlip(SDL_FLIP_NONE)
{
}

CSpriteComponent::~CSpriteComponent()
{
	mTexture   = nullptr;
	mAnimation = nullptr;
}

bool CSpriteComponent::Init()
{
	if (!CComponent::Init())
		return false;

	return true;
}

void CSpriteComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	if (mAnimation)
		mAnimation->Update(DeltaTime);
}

void CSpriteComponent::Render(SDL_Renderer* Renderer)
{
	CComponent::Render(Renderer);

	if (mTexture)
	{
		SDL_Rect frame = GetFrame();
		SDL_Rect dest  = GetDest();

		SDL_RenderCopyEx(Renderer, mTexture.get()->GetTexture(), &frame, &dest, 0.0, nullptr, mFlip);
	}
}

void CSpriteComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSpriteComponent>(this);
}

SDL_Rect CSpriteComponent::GetDest() const
{
	const FVector2D& scale   = mTransform->GetWorldScale();
	const FVector2D& topLeft = mTransform->GetWorldPos() - mTransform->GetPivot() * scale;

	return { (int)topLeft.x, (int)topLeft.y, (int)scale.x, (int)scale.y };
}

const SDL_Rect& CSpriteComponent::GetFrame() const
{
	return mAnimation ? mAnimation->GetCurrentFrame() : mTexture->GetTextureFrame();
}

void CSpriteComponent::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(key);
}

void CSpriteComponent::SetAnimation(const std::string& key)
{
	mAnimation = CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(key);
	mAnimation->mOwner = this;
}