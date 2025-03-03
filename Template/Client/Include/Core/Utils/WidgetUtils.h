#pragma once

// for the CWidget class
namespace EWidgetInput
{
	enum Event
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
	enum Method
	{
		LeftToRight,
		BottomToTop
	};

	enum State
	{
		BACK,
		FILL,
		MAX
	};
}