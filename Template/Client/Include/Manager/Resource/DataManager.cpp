#include "DataManager.h"
#include "PathManager.h"
#include "AssetManager.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "UIManager.h"
#include "../../Resource/Animation.h"
#include <fstream> // for file input/output
#include <sstream> // for stringstream

CDataManager::CDataManager()
{
}

CDataManager::~CDataManager()
{
}

bool CDataManager::Init()
{
	LoadAllSpriteData();
	LoadAllAnimationData();
	LoadAllButtonData();
	LoadAllImageData();

	return true;
}

std::vector<std::string> CDataManager::Split(const std::string& line, char delimiter)
{
	std::stringstream stream(line);

	std::vector<std::string> row;
	std::string cell;

	while (std::getline(stream, cell, delimiter))
	{
		row.push_back(cell);
	}
	return row;
}

void CDataManager::LoadAllSpriteData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Entity\\Sprite.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CSpriteManager* SM = CAssetManager::GetInst()->GetSpriteManager();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[0];

		{
			int x = std::stoi(row[1].substr(1));
			int y = std::stoi(row[2]);
			int w = std::stoi(row[3]);
			int h = std::stoi(row[4].substr(0, row[4].length() - 1));

			SM->mSprites[key] = SDL_Rect{ x,y,w,h };
		}
		row.clear();
	}
	file.close();
}

void CDataManager::LoadAllAnimationData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Entity\\Animation.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CAnimationManager* AM = CAssetManager::GetInst()->GetAnimationManager();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::vector<std::string> row = Split(line, ',');

		const std::string& key   = row[0];
		EAnimationType     type  = static_cast<EAnimationType>(std::stoi(row[1]));
		EAnimationState    state = static_cast<EAnimationState>(std::stoi(row[2]));

		// 애니메이션이 없을 경우, 애니메이션 생성
		AM->CreateAnimation(key);

		CAnimation* animation = AM->GetAnimation(key);

		if (animation)
		{
			std::shared_ptr<FAnimationData> data = std::make_shared<FAnimationData>();

			data->type             = type;
			data->isLoop           = std::stoi(row[3]) != 0;
			data->intervalPerFrame = std::stof(row[4]);

			int frameCount = std::stoi(row[5]) * 4;
			for (int i = 0; i < frameCount; i += 4)
			{
				int x = std::stoi(row[6 + i].substr(1));
				int y = std::stoi(row[7 + i]);
				int w = std::stoi(row[8 + i]);
				int h = std::stoi(row[9 + i].substr(0, row[9 + i].length() - 1));

				data->frames.emplace_back(SDL_Rect{ x, y, w, h });
			}
			animation->AddAnimationState(state, data);
		}
		row.clear();
	}
	file.close();
}

void CDataManager::LoadAllButtonData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Widget\\Button.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CUIManager* UIM = CAssetManager::GetInst()->GetUIManager();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[0];

		for (int i = 0; i < 12; i+=4)
		{
			int x = std::stoi(row[1 + i].substr(1));
			int y = std::stoi(row[2 + i]);
			int w = std::stoi(row[3 + i]);
			int h = std::stoi(row[4 + i].substr(0, row[4 + i].length() - 1));

			UIM->mUIs[key].emplace_back(SDL_Rect{ x,y,w,h });
		}
		row.clear();
	}
	file.close();
}

void CDataManager::LoadAllImageData()
{
	std::string filePath = CPathManager::GetInst()->FindPath(DATA_PATH);
	filePath += "Widget\\Image.csv";

	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file at: " << filePath << "\n";
		return;
	}

	CUIManager* UIM = CAssetManager::GetInst()->GetUIManager();

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::vector<std::string> row = Split(line, ',');

		const std::string& key = row[0];

		int frameCount = std::stoi(row[1]) * 4;
		for (int i = 0; i < frameCount; i += 4)
		{
			int x = std::stoi(row[2 + i].substr(1));
			int y = std::stoi(row[3 + i]);
			int w = std::stoi(row[4 + i]);
			int h = std::stoi(row[5 + i].substr(0, row[5 + i].length() - 1));

			UIM->mUIs[key].emplace_back(SDL_Rect{ x,y,w,h });
		}
		row.clear();
	}
	file.close();
}