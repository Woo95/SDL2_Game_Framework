#pragma once

// for the CWidget class
namespace EWidgetInput
{
	enum Event : unsigned char
	{
		UNHOVER,
		HOVER,
		CLICK,
		HOLD,
		RELEASE,
		MAX
	};
}

// for the CButton class
namespace EButton
{
	enum State : unsigned char
	{
		NORMAL,
		HOVER,
		HOLD,
		MAX
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
		MAX
	};
}