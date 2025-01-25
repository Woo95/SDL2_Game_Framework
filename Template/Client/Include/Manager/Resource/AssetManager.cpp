#include "AssetManager.h"
#include "TextureManager.h"
#include "AnimationManager.h"
#include "../../Resource/Animation.h"

CAssetManager* CAssetManager::mInst = nullptr;

CAssetManager::CAssetManager() :
	mTextureManager(nullptr),
	mAnimationManager(nullptr)
{
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mAnimationManager);
	SAFE_DELETE(mTextureManager);
}

bool CAssetManager::Init()
{
	mTextureManager   = new CTextureManager;
	mAnimationManager = new CAnimationManager;

	if (!mTextureManager->Init())
		return false;

	LoadTextures();

	return true;
}

void CAssetManager::LoadTextures()
{
	mTextureManager->LoadTexture("Antonio", "Antonio.png");
	mTextureManager->LoadTexture("Imelda", "Imelda.png");
	mTextureManager->LoadTexture("Pasqualina", "Pasqualina.png");

	CreateAnimations();
}

void CAssetManager::CreateAnimations()
{
	std::shared_ptr<CAnimation> animation;
	std::vector<SDL_Rect> frames = { { 0,  0, 31, 32 }, { 31, 0, 31, 32 }, { 62, 0, 31, 32 }, { 94, 0, 31, 32 } };

	mAnimationManager->CreateAnimation("Antonio_Animation", EAnimationType::NONE);
	animation = mAnimationManager->FindAnimation("Antonio_Animation");
	animation->SetAnimationStateInfo(EAnimationState::NONE, true, 0.0f);
	animation->AddFrame(EAnimationState::NONE, frames[0]);

	mAnimationManager->CreateAnimation("Imelda_Animation", EAnimationType::TIME);
	animation = mAnimationManager->FindAnimation("Imelda_Animation");
	animation->SetAnimationStateInfo(EAnimationState::WALK, true, 0.1f);
	animation->AddFrames(EAnimationState::WALK, frames);

	mAnimationManager->CreateAnimation("Pasqualina_Animation", EAnimationType::MOVE);
	animation = mAnimationManager->FindAnimation("Pasqualina_Animation");
	animation->SetAnimationStateInfo(EAnimationState::WALK, true, 150.0f);
	animation->AddFrames(EAnimationState::WALK, frames);
}