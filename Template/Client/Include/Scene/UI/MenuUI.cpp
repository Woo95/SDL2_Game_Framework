#include "MenuUI.h"
#include "../../Widget/UserWidget.h"
#include "../../Widget/Image.h"
#include "../../Widget/Button.h"

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
	CImage*  image  = nullptr;
	CButton* button = nullptr;

	//////////////////////////////////////////////////////////

	userWidget = CreateUserWidget<CUserWidget>("BGUserWidget");
	userWidget->GetTransform()->SetWorldScale(1280.f, 800.f);
	
	image = CreateWidget<CImage>("BGImage");
	image->GetTransform()->SetWorldScale(1280.f, 800.f);

	image->SetTexture("IntroBG");
	image->SetFrame("IntroBG");

	userWidget->AddWidget(image);
	userWidget->GetTransform()->SetWorldPos(0.f, 0.f);

	//////////////////////////////////////////////////////////

	// 유저위젯 생성 및 설정
	userWidget = CreateUserWidget<CUserWidget>("UserWidget1");
	userWidget->SetMovable(true);
	userWidget->GetTransform()->SetWorldScale(200.f, 200.f);
	userWidget->GetTransform()->SetPivot(0.5f, 0.5f);

	// 버튼 생성 및 설정
	button = CreateWidget<CButton>("Button1");
	button->GetTransform()->SetWorldScale(100, 100);
	button->GetTransform()->SetPivot(0.5f, 0.5f);

	// 버튼 텍스쳐 및 프레임 설정
	button->SetTexture("UI");
	button->SetFrames("BlueButton");

	// 유저위젯 자식으로 버튼 추가 및 유저위젯 위치 설정
	userWidget->AddWidget(button);
	userWidget->GetTransform()->SetWorldPos(500.f, 200.f);

	//////////////////////////////////////////////////////////

	// 유저위젯 생성 및 설정
	userWidget = CreateUserWidget<CUserWidget>("UserWidget2");
	userWidget->SetMovable(true);
	userWidget->GetTransform()->SetWorldScale(200.f, 200.f);
	userWidget->GetTransform()->SetPivot(0.5f, 0.5f);

	// 버튼 생성 및 설정
	button = CreateWidget<CButton>("Button2");
	button->GetTransform()->SetWorldScale(100, 100);
	button->GetTransform()->SetPivot(0.5f, 0.5f);

	// 버튼 텍스쳐 및 프레임 설정
	button->SetTexture("UI");
	button->SetFrames("GreenButton");

	// 유저위젯 자식으로 버튼 추가 및 유저위젯 위치 설정
	userWidget->AddWidget(button);
	userWidget->GetTransform()->SetWorldPos(250.f, 200.f);
	//////////////////////////////////////////////////////////

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