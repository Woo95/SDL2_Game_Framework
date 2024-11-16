#pragma once

#include "Object.h"
#include "../../Core/Timer.h"

class CPlayer : public CObject
{
public:
	CPlayer() = default;
	virtual ~CPlayer() = default;

private:
	float mSpeed = 200.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual bool Release() final;

private:
	void SetupInput();

	void MOVE(const FVector2D& direction)
	{
		CTransform* transform = GetTransform();

		FVector2D movement = direction * mSpeed * CTimer::GetDeltaTime();
		transform->SetWorldPos(transform->GetWorldPos() + movement);
	}
	void MOVE_UP() 
	{ 
		MOVE(FVector2D(0, -1)); 
	}
	void MOVE_DOWN() 
	{ 
		MOVE(FVector2D(0, 1)); 
	}
	void MOVE_LEFT() 
	{ 
		MOVE(FVector2D(-1, 0)); 
	}
	void MOVE_RIGHT() 
	{ 
		MOVE(FVector2D(1, 0)); 
	}
};