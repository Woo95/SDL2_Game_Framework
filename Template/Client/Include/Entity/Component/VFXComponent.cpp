#include "VFXComponent.h"
#include "../Object/Object.h"
#include "../../Manager/Data/Resource/AssetManager.h"
#include "../../Manager/Data/Resource/TextureManager.h"
#include "../../Manager/Data/Resource/AnimationManager.h"
#include "../../Resource/Texture.h"
#include "../../Resource/Animation.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Extension/Camera.h"

CVFXComponent::CVFXComponent() :
	mTexture(nullptr),
	mAnimation(nullptr),
	mPlayVFX(false)
{
	mTypeID = typeid(CVFXComponent).hash_code();
}

CVFXComponent::~CVFXComponent()
{
	mTexture = nullptr;

	if (mAnimation)
		mAnimation->Release();
}

void CVFXComponent::Update(float deltaTime)
{
	CComponent::Update(deltaTime);

	if (!mPlayVFX || !mAnimation)
		return;

	mAnimation->Update(deltaTime);

	if (mAnimation->IsPlayedOnce())
	{
		mPlayVFX = false;
		mAnimation->ResetPlayedOnce();
	}
}

void CVFXComponent::Render(SDL_Renderer* renderer)
{
	if (mPlayVFX && mTexture && IsVisibleToCamera())
	{
		const SDL_Rect& frame = mAnimation->GetFrame();
		const SDL_Rect  dest  = GetCameraSpaceRect();

		SDL_RenderCopy(renderer, mTexture->GetTexture(), &frame, &dest);
	}
	CComponent::Render(renderer);
}

void CVFXComponent::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CVFXComponent>(this);
}

void CVFXComponent::SetTexture(const std::string& key)
{
	mTexture = CAssetManager::GetInst()->GetTextureManager()->GetTexture(key);
}

void CVFXComponent::SetAnimation(const std::string& key)
{
	CAnimation* base = CAssetManager::GetInst()->GetAnimationManager()->GetAnimation(key);

	if (base)
	{
		mAnimation = base->Clone();
		mAnimation->mTransform = mTransform;
	}
}

void CVFXComponent::PlayVFX(const FVector2D& pos)
{
	if (mPlayVFX || !mAnimation)
		return;

	mPlayVFX = true;

	mTransform->SetWorldPos(pos);
	mAnimation->mCurrIdx = 0;
	mAnimation->mFrameInterval = 0.0f;
}

SDL_Rect CVFXComponent::GetDest() const
{
	// 월드 스케일, 위치, 피벗을 반환
	const FVector2D& scale = mTransform->GetWorldScale();
	const FVector2D& pos   = mTransform->GetWorldPos();
	const FVector2D& pivot = mTransform->GetPivot();

	// 좌상단 좌표 계산
	FVector2D topLeft = pos - pivot * scale;

	// 사각형 정보 생성
	return { (int)topLeft.x, (int)topLeft.y, (int)scale.x, (int)scale.y };
}

bool CVFXComponent::IsVisibleToCamera() const
{
	if (CCamera* camera = mObject->GetScene()->GetCamera())
	{
		SDL_Rect spriteRect = GetDest();
		SDL_Rect cameraRect = camera->GetViewRect();

		if (!SDL_HasIntersection(&spriteRect, &cameraRect))
			return false;
	}
	return true;
}

SDL_Rect CVFXComponent::GetCameraSpaceRect() const
{
	// 월드 스케일, 위치, 피벗을 반환
	const FVector2D& scale = mTransform->GetWorldScale();
	const FVector2D& pos   = mTransform->GetWorldPos();
	const FVector2D& pivot = mTransform->GetPivot();

	// 좌상단 좌표 계산
	FVector2D topLeft = pos - pivot * scale;

	// 카메라가 있을 경우, 카메라 좌표계를 반영한 렌더링 좌표로 변환
	if (CCamera* camera = mObject->GetScene()->GetCamera())
		topLeft = camera->GetRenderPos(topLeft);

	// 사각형 정보 생성
	return { (int)topLeft.x, (int)topLeft.y, (int)scale.x, (int)scale.y };
}