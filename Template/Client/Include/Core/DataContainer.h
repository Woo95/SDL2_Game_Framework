#pragma once

#include <string>

class DataContainer abstract
{
protected:
	DataContainer() = default;
	virtual ~DataContainer() = default;

protected:
	std::string mName;
	size_t mID   = -1;
	bool mActive = true;	// handle object/component to be deleted
	bool mEnable = true;	// handle object/component to be rendered

public:
	virtual bool Release() = 0;

public:
	const std::string& GetName() const { return mName; }
	const size_t GetID() const { return mID; }
	bool GetActive() const { return mActive; }
	bool GetEnable() const { return mEnable; }

public:
	void SetName(const std::string& name) 
	{ 
		mName = name;
		mID = std::hash<std::string>()(name);
	}
	void SetEnable(bool enable) 
	{ 
		mEnable = enable; 
	}
	void SetActive(bool active) 
	{ 
		mActive = active; 
	}
};