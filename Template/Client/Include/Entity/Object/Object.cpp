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

void CObject::Update(float DeltaTime)
{
	mRootComponent->Update(DeltaTime);
}

void CObject::LateUpdate(float DeltaTime)
{
	mRootComponent->LateUpdate(DeltaTime);
}

void CObject::Render(SDL_Renderer* Renderer)
{
	mRootComponent->Render(Renderer);
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
