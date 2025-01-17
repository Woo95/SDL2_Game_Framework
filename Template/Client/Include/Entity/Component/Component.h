#pragma once

#include "../EntityBase.h"
#include "../../Core/GameInfo.h"
#include "../../Manager/MemoryPoolManager.h"
#include "../../Core/Vector2D.h"
#include "Transform.h"

/*
	"Game Object"는 게임 내에서 나타나는 모든 요소를 지칭한다.
	독자적으로 많은 것을 하기보다는 실질적 기능을 수행하는 컴포넌트(Components)의 컨테이너 역할이다.
*/

class CComponent : public CEntityBase
{
	friend class CObject;

protected:
	CComponent();
	virtual ~CComponent();

protected:
	class CObject* mObject = nullptr;
	CTransform* mTransform;

	CComponent* mParent = nullptr;
	std::vector<CComponent*> mChilds;
	
protected:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void LateUpdate(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer); 

private:
	// mRootComponent는 메모리 풀을 사용하지 않고 new로 할당되므로 Release할 필요가 없음.
	virtual void Release() { return; }	// Object.h에서 component memoryPool usage 위하여

public:
	CTransform* GetTransform() const { return mTransform; }
	CObject* GetObject() const { return mObject; }

	void AddChild(CComponent* child);
	bool DeleteChild(CComponent* child);
	CComponent* FindComponent(size_t id);

public:
	void Enable();
	void Disable();
	void Destroy();
};