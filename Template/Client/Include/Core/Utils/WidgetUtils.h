#pragma once

#include "../../Manager/MemoryPoolManager.h"

class CWidgetUtils
{
public:
	template <typename T, int initialCapacity = 5>
	static T* AllocateWidget(const std::string& name)
	{
		if (!CMemoryPoolManager::GetInst()->HasPool<T>())
		{
			CMemoryPoolManager::GetInst()->CreatePool<T>(initialCapacity);
		}

		T* widget = CMemoryPoolManager::GetInst()->Allocate<T>();
		widget->SetName(name);

		return widget;
	}
};

// for the CButton class
namespace EButton
{
	enum State : unsigned char
	{
		NORMAL,
		HOVER,
		PRESSED,
		STATE_MAX
	};

	enum InputEvent : unsigned char
	{
		CLICK,
		HOLD,
		RELEASE,
		INPUT_EVENT_MAX
	};
}

// for the CProgressBar class
namespace EProgBar
{
	enum Method : unsigned char
	{
		LeftToRight,
		BottomToTop
	};

	enum State : unsigned char
	{
		BACK,
		FILL,
		MAX
	};
}

// for the CSlider class
namespace ESlider
{
	enum State : unsigned char
	{
		TRACK,
		THUMB,
		STATE_MAX
	};

	enum InputEvent : unsigned char
	{
		CLICK,
		HOLD,
		RELEASE,
		INPUT_EVENT_MAX
	};
}

// for CTextBlock class
namespace ETextBlock
{
	enum Alignment : unsigned char
	{
		FILL,
		LEFT,
		CENTER,
		RIGHT
	};
}