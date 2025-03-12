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
		UNHOVER,
		HOVER,
		CLICK,
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