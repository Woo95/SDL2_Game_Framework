#pragma once

#include "../Component.h"

class CTexture;
class CAnimation;

class CSpriteComponent : public CComponent
{
public:
	CSpriteComponent();
	virtual ~CSpriteComponent();

private:
	std::shared_ptr<CTexture>   mTexture;
	std::shared_ptr<CAnimation> mAnimation;

	SDL_RendererFlip mFlip;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Render(SDL_Renderer* Renderer);

private:
	virtual void Release() final;

public:
	const SDL_Rect GetFrame() const;
	SDL_Rect GetDest() const;

	std::shared_ptr<CTexture>   GetTexture()   const { return mTexture; }
	std::shared_ptr<CAnimation> GetAnimation() const { return mAnimation; }

	void SetTexture(const std::string& key);
	void SetAnimation(const std::string& key);
	void SetFlip(SDL_RendererFlip flip) { mFlip = flip; }
};