#include "PathManager.h"

CPathManager* CPathManager::mInst = nullptr;

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
}

bool CPathManager::Init()
{
	// 실행 파일 경로 문자열을 동적으로 할당하여 시작 주소를 반환
	char* basePath = SDL_GetBasePath();

	// basePath 문자열을 std::string으로 복사하여 키 값으로 저장
	mPaths[BASE_PATH] = basePath;

	// 동적으로 할당된 basePath 메모리를 해제
	SDL_free(basePath);

	// BASE_PATH를 기준으로 새로운 경로 추가
	AddPath(TEXTURE_PATH, "Texture\\", BASE_PATH);
	AddPath(SOUND_PATH, "Sound\\", BASE_PATH);

	return true;
}

bool CPathManager::AddPath(const std::string& newPathKey, const char* newPathSegment, const std::string& basePathKey)
{
	if (FindPath(newPathKey))
		return false;

	std::string newPath = FindPath(basePathKey);

	if (!newPath.empty())
		newPath += newPathSegment;

	mPaths[newPathKey] = newPath;

	return true;
}

const char* CPathManager::FindPath(const std::string& key)
{
	std::unordered_map<std::string, std::string>::iterator iter = mPaths.find(key);

	if (iter == mPaths.end())
		return nullptr;

	// c_str(): std::string을 const char*로 반환
	return iter->second.c_str();
}
