#pragma once

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