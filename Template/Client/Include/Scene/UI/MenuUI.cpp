#include "MenuUI.h"
#include "../../Widget/AllWidgets.h"

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

	CImage* image = CWidgetUtils::AllocateWidget<CImage>("BGImage");
	image->GetTransform()->SetWorldPos(0.f, 0.f);
	image->GetTransform()->SetWorldScale(1280.f, 800.f);

	image->SetTexture("IntroBG");
	image->SetFrame("IntroBG");

	AddWidget(image);

	//////////////////////////////////////////////////////////

	CSampleUserWidget* panel1 = CWidgetUtils::AllocateWidget<CSampleUserWidget>("panel");
	panel1->GetTransform()->SetWorldPos(340.f, 400.f);
	panel1->GetTransform()->SetWorldScale(500.f, 500.f);
	panel1->GetTransform()->SetPivot(0.5f, 0.5f);
	panel1->SetMovable(true);
	AddWidget(panel1);

	CSampleUserWidget* panel2 = CWidgetUtils::AllocateWidget<CSampleUserWidget>("panel2");
	panel2->GetTransform()->SetWorldPos(940.f, 400.f);
	panel2->GetTransform()->SetWorldScale(500.f, 500.f);
	panel2->GetTransform()->SetPivot(0.5f, 0.5f);
	panel2->SetMovable(true);
	AddWidget(panel2);
	
	return true;
}

void CMenuUI::Update(float deltaTime)
{
	CSceneUI::Update(deltaTime);
}

void CMenuUI::LateUpdate(float deltaTime)
{
	CSceneUI::LateUpdate(deltaTime);
}

void CMenuUI::Render(SDL_Renderer* renderer)
{
	CSceneUI::Render(renderer);
}