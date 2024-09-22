#pragma once

#include <string>

class DataContainer abstract
{
protected:
	DataContainer() = default;
	~DataContainer() = default;

protected:
	std::string mName;
	bool mActive = true;	// handle object/component to be deleted
	bool mEnable = true;	// handle object/component to be rendered

public:
	const std::string& GetName() const { return mName; }
	bool GetActive() const { return mActive; }
	bool GetEnable() const { return mEnable; }

	void SetName(const std::string& name) 
	{ 
		mName = name; 
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