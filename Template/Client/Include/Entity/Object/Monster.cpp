#include "Monster.h"
#include "../Component/Collider/BoxCollider.h"
#include "../../Entity/Component/SpriteComponent.h"
#include "../../Resource/Animation.h"
#include "../../Entity/Component/Rigidbody.h"
#include "../../Entity/Component/VFXComponent.h"

CMonster::CMonster() :
    mCollider(nullptr),
    mVFX(nullptr)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	// 스프라이트 컴포넌트 설정
	CSpriteComponent* sprite = AllocateComponent<CSpriteComponent>("sprite");
	sprite->SetTexture("Imelda");
	sprite->SetAnimation("Imelda");
	sprite->GetAnimation()->SetState(EAnimationState::WALK);
	sprite->GetTransform()->SetWorldScale(75.f, 75.f);
	sprite->GetTransform()->SetPivot(0.5f, 0.5f);

	// 충돌체 컴포넌트 설정
	mCollider = AllocateComponent<CBoxCollider>("collider");
	mCollider->SetProfile("Monster");
	mCollider->GetTransform()->SetWorldScale(50.f, 75.f);
	mCollider->GetTransform()->SetPivot(0.5f, 0.5f);
	mCollider->AddCallbackFunc(ECollider::OnCollision::ENTER, this, &CMonster::OnHit);

	// 리지드바디 컴포넌트 설정
	CRigidbody* rb = AllocateComponent<CRigidbody>("rigidbody");

	// VFX 컴포넌트 설정
	mVFX = AllocateComponent<CVFXComponent>("vfx");
	mVFX->SetTexture("NumberVFX");
	mVFX->SetAnimation("NumberVFX");
	mVFX->GetAnimation()->SetState(EAnimationState::VFX);
	mVFX->GetTransform()->SetWorldScale(25.f, 35.7f);
	mVFX->GetTransform()->SetPivot(0.5f, 0.5f);


	// 컴포넌트들 계층 구조에 추가
	GetComponent()->AddChild(sprite);
	GetComponent()->AddChild(rb);
	GetComponent()->AddChild(mCollider);
	GetComponent()->AddChild(mVFX);

	// 오브젝트 초기 위치 설정
	GetTransform()->SetWorldPos(800.f, 200.f);

	// 부모 클래스 초기화
	return CObject::Init();
}

void CMonster::Update(float deltaTime)
{
	CObject::Update(deltaTime);
}

void CMonster::LateUpdate(float deltaTime)
{
	CObject::LateUpdate(deltaTime);
}

void CMonster::Render(SDL_Renderer* renderer)
{
	CObject::Render(renderer);
}

void CMonster::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CMonster>(this);
}

void CMonster::OnHit(CCollider* self, CCollider* other)
{
    mVFX->PlayVFX(mCollider->GetHitPoint());
}