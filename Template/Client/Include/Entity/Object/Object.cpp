#include "Object.h"
#include "../Component/Component.h"

// mRootComponent는 컴포넌트 간 독립적인 동작과 계층 구조 관리를 위한 기본 구조를 제공하기 위해 사용한다. (기능적 수행 X)
CObject::CObject() :
	mScene(nullptr),
	mLayer(nullptr),
	mRootComponent(nullptr)
{
	mRootComponent = new CComponent;

	mRootComponent->SetName("RootComponent");
	mRootComponent->mObject = this;
}

CObject::~CObject()
{
	SAFE_DELETE(mRootComponent);
}

bool CObject::Init()
{
	return mRootComponent->Init();
}

void CObject::Update(float deltaTime)
{
	mRootComponent->Update(deltaTime);
}

void CObject::LateUpdate(float deltaTime)
{
	mRootComponent->LateUpdate(deltaTime);
}

void CObject::Render(SDL_Renderer* renderer)
{
	mRootComponent->Render(renderer);
}

void CObject::Enable()
{
	SetEnable(true);
	mRootComponent->Enable();
}

void CObject::Disable()
{
	SetEnable(false);
	mRootComponent->Disable();
}

void CObject::Destroy()
{
	SetActive(false);
	mRootComponent->Destroy();
}
