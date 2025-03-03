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