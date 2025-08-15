#pragma once

#include "Component.h"

class CTexture;
class CAnimation;

class CSpriteComponent : public CComponent
{
public:
	CSpriteComponent();
	virtual ~CSpriteComponent();

private:
	std::shared_ptr<CTexture> mTexture;
	CAnimation* mAnimation;
	SDL_Rect mFrame;

	SDL_RendererFlip mFlip;

private:
	virtual void Update(float deltaTime)        final;
	virtual void Render(SDL_Renderer* renderer) final;
	virtual void Release()                      final;

public:
	std::shared_ptr<CTexture> GetTexture() const { return mTexture; }
	CAnimation* GetAnimation() const { return mAnimation; }

	void SetTexture(const std::string& key);
	void SetAnimation(const std::string& key);
	void SetFrame(const std::string& key);

	void SetFlip(SDL_RendererFlip flip) { mFlip = flip; }

private:
	const SDL_Rect& GetFrame() const;
	SDL_Rect GetDest() const;

	// 카메라 관련 함수
	bool IsVisibleToCamera() const;
	SDL_Rect GetCameraSpaceRect() const;
};