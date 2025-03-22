#include "Slider.h"
#include "UserWidget.h"
#include "../Scene/UI/SceneUI.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/UIManager.h"
#include "../Manager/Resource/TextureManager.h"
#include "../Resource/Texture.h"
#include "../Manager/MemoryPoolManager.h"
#include "../Manager/CollisionManager.h"

CSlider::CSlider()
{
    mIsInteractable = true;

    mColors[ESlider::State::TRACK] = { 255, 255, 255, 255 };
    mColors[ESlider::State::THUMB] = { 255, 255, 255, 255 };
}

CSlider::~CSlider()
{
    mTexture = nullptr;
}

void CSlider::Update(float DeltaTime)
{
    CWidget::Update(DeltaTime);

    UpdateTrackRect();
    UpdateThumbRect();
}

void CSlider::Render(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
    SDL_Rect renderRect = mRect;

    renderRect.x += (int)topLeft.x;
    renderRect.y += (int)topLeft.y;

    RenderTrack(Renderer, topLeft);
    RenderThumb(Renderer, topLeft);

    CWidget::Render(Renderer, topLeft);
}

void CSlider::Release()
{
    CMemoryPoolManager::GetInst()->Deallocate<CSlider>(this);
}

void CSlider::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    // 위젯 호버 상태에서 "마우스 입력" 처리 //

    if (isPressed && !mWidgetHeld)
    {
        mWidgetHeld = true;

        mUserWidget->GetSceneUI()->SetHeldWidget(this);
        mUserWidget->GetSceneUI()->BringUserWidgetToTop(mUserWidget);

        // Thumb 클릭
        if (CCollisionManager::GetInst()->AABBPointCollision(mThumbRect, mousePos))
        {
            // Thumb을 클릭한 상태의 오프셋 저장
            mThumbOffsetX = mousePos.x - mThumbRect.x;
        }
        // Track 클릭
        else if (CCollisionManager::GetInst()->AABBPointCollision(mTrackRect, mousePos))
        {
            // Track을 클릭한 상태의 오프셋 저장
            mThumbOffsetX = mThumbRect.w * 0.5f;
        }
        ComputePercent(mousePos);

        ExecuteCallback(ESlider::InputEvent::CLICK);
    }
    else if (isHeld && mWidgetHeld)
    {
        ComputePercent(mousePos);

        ExecuteCallback(ESlider::InputEvent::HOLD);
    }
    else if (isReleased && mWidgetHeld)
    {
        mWidgetHeld = false;

        mUserWidget->GetSceneUI()->SetHeldWidget(nullptr);

        ExecuteCallback(ESlider::InputEvent::RELEASE);
    }
}

void CSlider::HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased)
{	
    // 마우스 좌클릭을 위젯 안에서 홀드 하다가 밖일 때 실행
    if (isHeld && mWidgetHeld)
    {
        ComputePercent(mousePos);

        ExecuteCallback(ESlider::InputEvent::HOLD);
    }
    // 마우스 좌클릭을 위젯 밖에서 홀드 하다가 떼었을 때 실행
    else if (isReleased)
    {
        mWidgetHeld = false;

        mUserWidget->GetSceneUI()->SetHeldWidget(nullptr);
    }
}

void CSlider::SetTexture(const std::string& key)
{
    mTexture = CAssetManager::GetInst()->GetTextureManager()->GetTexture(key);
}

void CSlider::SetFrame(const std::string& key)
{
    const std::vector<SDL_Rect>* const framesPtr = CAssetManager::GetInst()->GetUIManager()->GetUIFrames(key);

    if (framesPtr)
    {
        for (size_t i = 0; i < ESlider::State::STATE_MAX; i++)
            mFrames[i] = (*framesPtr)[i];
    }
}

void CSlider::SetColor(ESlider::State state, Uint8 r, Uint8 g, Uint8 b)
{
    mColors[state].r = r;
    mColors[state].g = g;
    mColors[state].b = b;
}

void CSlider::SetAlpha(Uint8 alpha)
{
    for (size_t i = 0; i < ESlider::State::STATE_MAX; i++)
        mColors[i].a = alpha;

    // 투명도를 고려한 블렌드로 설정
    SDL_SetTextureBlendMode(mTexture.get()->GetTexture(), SDL_BLENDMODE_BLEND);
}

void CSlider::ComputePercent(const FVector2D& mousePos)
{
    float thumbPos   = mousePos.x - mRect.x - mThumbOffsetX;
    float trackRange = (float)(mRect.w - mThumbRect.w);

    mPercent = std::clamp(thumbPos / trackRange, 0.0f, 1.0f);
}

void CSlider::UpdateTrackRect()
{
    if (mTrackRect.h > mRect.h)
        mTrackRect.h = mRect.h;

    int trackPosY = (int)(mRect.y + (mRect.h - mTrackRect.h) * 0.5f);

    mTrackRect = { mRect.x, trackPosY, mRect.w, mTrackRect.h };
}

void CSlider::UpdateThumbRect()
{
    if (mThumbRect.w > mRect.w)
        mThumbRect.w = mRect.w;

    int trackPosX = (int)(mRect.x + (mRect.w - mThumbRect.w) * mPercent);
    trackPosX = std::clamp(trackPosX, mRect.x, (mRect.x + mRect.w) - mThumbRect.w);

    mThumbRect = { trackPosX, mRect.y, mThumbRect.w, mRect.h };
}

void CSlider::RenderTrack(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
    SDL_Rect trackRenderRect = mTrackRect;

    trackRenderRect.x += (int)topLeft.x;
    trackRenderRect.y += (int)topLeft.y;

    const SDL_Color& color = mColors[ESlider::State::TRACK];
    SDL_SetTextureColorMod(mTexture.get()->GetTexture(), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), color.a);

    SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[ESlider::State::TRACK], &trackRenderRect);
}

void CSlider::RenderThumb(SDL_Renderer* Renderer, const FVector2D& topLeft)
{
    SDL_Rect thumbRenderRect = mThumbRect;

    thumbRenderRect.x += (int)topLeft.x;
    thumbRenderRect.y += (int)topLeft.y;

    const SDL_Color& color = mColors[ESlider::State::THUMB];
    SDL_SetTextureColorMod(mTexture.get()->GetTexture(), color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(mTexture.get()->GetTexture(), color.a);

    SDL_RenderCopy(Renderer, mTexture.get()->GetTexture(), &mFrames[ESlider::State::THUMB], &thumbRenderRect);
}