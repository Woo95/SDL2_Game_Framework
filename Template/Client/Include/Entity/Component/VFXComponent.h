#pragma once

#include "Component.h"

class CTexture;
class CAnimation;

class CVFXComponent : public CComponent
{
public:
	CVFXComponent();
	virtual ~CVFXComponent();

private:
	std::shared_ptr<CTexture> mTexture;
	CAnimation* mAnimation;

	bool mPlayVFX;

private:
	virtual void Update(float deltaTime)        final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release()                      final;

public:
	std::shared_ptr<CTexture> GetTexture() const { return mTexture; }
	CAnimation* GetAnimation() const { return mAnimation; }

	void SetTexture(const std::string& key);
	void SetAnimation(const std::string& key);

	void PlayVFX(const FVector2D& pos);

private:
	SDL_Rect GetDest() const;

	// 카메라 관련 함수
	bool IsVisibleToCamera() const;
	SDL_Rect GetCameraSpaceRect() const;
};
