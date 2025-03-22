#include "MenuUI.h"
#include "../../Widget/UserWidget.h"
#include "../../Widget/Image.h"
#include "../../Widget/Button.h"
#include "../../Widget/ProgressBar.h"
#include "../../Widget/TextBlock.h"
#include "../../Widget/Slider.h"
#include "../../Manager/SceneManager.h"

CMenuUI::CMenuUI()
{
}

CMenuUI::~CMenuUI()
{
}

bool CMenuUI::Init()
{
	CSceneUI::Init();

	//////////////////////////////////////////////////////////

	CUserWidget* userWidget = nullptr;

	//////////////////////////////////////////////////////////

	userWidget = CreateUserWidget<CUserWidget>("BGUserWidget");
	userWidget->GetTransform()->SetWorldScale(1280.f, 800.f);
	
	CImage* image = CreateWidget<CImage>("BGImage");
	image->GetTransform()->SetWorldScale(1280.f, 800.f);

	image->SetTexture("IntroBG");
	image->SetFrame("IntroBG");

	userWidget->AddWidget(image);
	userWidget->GetTransform()->SetWorldPos(0.f, 0.f);

	//////////////////////////////////////////////////////////

	// 유저위젯 생성 및 설정
	userWidget = CreateUserWidget<CUserWidget>("UserWidget1");
	userWidget->SetMovable(true);
	userWidget->GetTransform()->SetWorldScale(500.f, 500.f);
	userWidget->GetTransform()->SetPivot(0.5f, 0.5f);

	//// 버튼 생성 및 설정
	CButton* button = CreateWidget<CButton>("Button1");
	button->GetTransform()->SetWorldScale(109.f, 60.f);
	button->GetTransform()->SetPivot(0.5f, 0.5f);

	// 버튼 텍스쳐 및 프레임 설정
	button->SetTexture("UI");
	button->SetFrame("BlueButton");
	button->AddCallback(EButton::InputEvent::RELEASE, [](){CSceneManager::GetInst()->PendingChange(EScene::State::PLAY);});

	// 유저위젯 자식으로 버튼 추가
	userWidget->AddWidget(button);

	//////////////////////////////////////////////////////////

	// 텍스트 생성 및 설정
	CTextBlock* textBlock = CreateWidget<CTextBlock>("textBlock1");
	textBlock->GetTransform()->SetWorldScale(80.f, 50.f);
	textBlock->GetTransform()->SetPivot(0.5f, 0.5f);

	// 텍스트 폰트 설정
	textBlock->SetFont("Cormorant");
	textBlock->SetText("SAMPLE");

	// 유저위젯 자식으로 텍스트 추가 및 유저위젯 설정
	button->AddChild(textBlock);

	//////////////////////////////////////////////////////////

	// 프로그레스 바 생성 및 설정
	CProgressBar* progressBar = CreateWidget<CProgressBar>("progressBar1");
	progressBar->GetTransform()->SetWorldScale(200.f, 25.f);
	progressBar->GetTransform()->SetPivot(0.5f, 0.5f);
	progressBar->SetColor(EProgBar::State::BACK, 0, 0, 0);
	progressBar->SetPercent(0.5f);

	// 프로그레스 바 텍스쳐 및 프레임 설정
	progressBar->SetTexture("UI");
	progressBar->SetFrame("HpBar");

	// 유저위젯 자식으로 프로그레스 바 추가 및 유저위젯 설정
	userWidget->AddWidget(progressBar);
	progressBar->GetTransform()->SetRelativePos(0.f, -100.f);

	//////////////////////////////////////////////////////////

	// 슬라이더 생성 및 설정
	CSlider* slider = CreateWidget<CSlider>("Slider1");
	slider->GetTransform()->SetWorldScale(200.f, 25.f);
	slider->GetTransform()->SetPivot(0.5f, 0.5f);

	// 슬라이더 텍스쳐 및 프레임 설정
	slider->SetTexture("UI");
	slider->SetFrame("Slider");

	// 유저위젯 자식으로 슬라이더 추가 및 유저위젯 설정
	userWidget->AddWidget(slider);
	slider->GetTransform()->SetRelativePos(0.f, 100.f);

	//////////////////////////////////////////////////////////
	userWidget->GetTransform()->SetWorldPos(640.f, 400.f);
	
	return true;
}

void CMenuUI::Update(float DeltaTime)
{
	CSceneUI::Update(DeltaTime);
}

void CMenuUI::LateUpdate(float DeltaTime)
{
	CSceneUI::LateUpdate(DeltaTime);
}

void CMenuUI::Render(SDL_Renderer* Renderer)
{
	CSceneUI::Render(Renderer);
}