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
	SDL_Rect mFrame;
	CAnimation* mAnimation;

	SDL_RendererFlip mFlip;

public:
	virtual bool Init() final;

private:
	virtual void Update(float DeltaTime)        final;
	virtual void LateUpdate(float DeltaTime)    final;
	virtual void Render(SDL_Renderer* Renderer) final;
	virtual void Release()                      final;

public:
	std::shared_ptr<CTexture> GetTexture() const { return mTexture; }
	CAnimation* GetAnimation() const { return mAnimation; }

	void SetTexture(const std::string& key);
	void SetSprite(const std::string& key);
	void SetAnimation(const std::string& key);

	void SetFlip(SDL_RendererFlip flip) { mFlip = flip; }

private:
	const SDL_Rect& GetFrame() const;
	const SDL_Rect GetDest() const;
};