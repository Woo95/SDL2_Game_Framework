#pragma once

#include <string>

class CEntityBase abstract
{
	friend class CScene;
	friend class CObject;
	friend class CComponent;

protected:
	CEntityBase() = default;
	virtual ~CEntityBase() = default;

protected:
	std::string mName;
	size_t mID   = -1;
	bool mActive = true;	// handle object/component to be deleted
	bool mEnable = true;	// handle object/component to be rendered

public:
	const std::string& GetName() const { return mName; }
	size_t   GetID() const { return mID; }
	bool GetActive() const { return mActive; }
	bool GetEnable() const { return mEnable; }

private:
	void SetName(const std::string& name)
	{
		mName = name;
		mID = std::hash<std::string>()(name);
	}
	void SetActive(bool active)
	{
		mActive = active;
	}
	void SetEnable(bool enable) 
	{ 
		mEnable = enable; 
	}
};