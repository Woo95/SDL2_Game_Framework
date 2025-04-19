#include "SampleUserWidget.h"
#include "AllWidgets.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Resource/AssetManager.h"
#include "../Manager/Resource/SoundManager.h"

CSampleUserWidget::CSampleUserWidget()
{
    Construct();
}

CSampleUserWidget::~CSampleUserWidget()
{
}

void CSampleUserWidget::Construct()
{    
    // 패널 생성 및 설정
    GetTransform()->SetWorldScale(500.f, 500.f);
    GetTransform()->SetPivot(0.5f, 0.5f);

    // 버튼 생성
    CButton* button = CWidgetUtils::AllocateWidget<CButton>("Button");
    button->GetTransform()->SetWorldScale(109.f, 60.f);
    button->GetTransform()->SetPivot(0.5f, 0.5f);
    button->SetTexture("UI");
    button->SetFrame("BlueButton");
    button->AddCallback(EButton::InputEvent::RELEASE, []() {CSceneManager::GetInst()->PendingChange(EScene::State::PLAY); });
    AddChild(button); // 버튼을 패널에 추가

    // 텍스트 블록 생성
    CTextBlock* textBlock = CWidgetUtils::AllocateWidget<CTextBlock>("textBlock");
    textBlock->GetTransform()->SetWorldScale(80.f, 50.f);
    textBlock->GetTransform()->SetPivot(0.5f, 0.5f);
    textBlock->SetFont("Cormorant");
    textBlock->SetText("SAMPLE");
    button->AddChild(textBlock); // 텍스트를 버튼에 추가

    // 프로그레스 바 생성
    CProgressBar* progressBar = CWidgetUtils::AllocateWidget<CProgressBar>("progressBar");
    progressBar->GetTransform()->SetWorldScale(200.f, 25.f);
    progressBar->GetTransform()->SetPivot(0.5f, 0.5f);
    progressBar->SetColor(EProgBar::State::BACK, 0, 0, 0);
    progressBar->SetPercent(0.5f);
    progressBar->SetTexture("UI");
    progressBar->SetFrame("HpBar");
    progressBar->GetTransform()->SetRelativePos(0.f, -100.f);
    AddChild(progressBar);

    // 슬라이더 생성
    CSlider* slider = CWidgetUtils::AllocateWidget<CSlider>("Slider");
    slider->GetTransform()->SetWorldScale(200.f, 25.f);
    slider->GetTransform()->SetPivot(0.5f, 0.5f);
    slider->SetTexture("UI");
    slider->SetFrame("Slider");
    slider->SetPercent(0.1f);
    slider->AddCallback(ESlider::InputEvent::HOLD, [](float percent) {CAssetManager::GetInst()->GetSoundManager()->SetVolume<CSFX>(percent);});
    slider->GetTransform()->SetRelativePos(0.f, 100.f);
    AddChild(slider);
}

void CSampleUserWidget::Release()
{
	CMemoryPoolManager::GetInst()->Deallocate<CSampleUserWidget>(this);
}

void CSampleUserWidget::HandleHovered(const FVector2D& mousePos, bool isPressed, bool isHeld, bool isReleased)
{
    HandleDragging(mousePos, isPressed, isHeld, isReleased);
}

void CSampleUserWidget::HandleUnhovered(const FVector2D& mousePos, bool isHeld, bool isReleased)
{
}