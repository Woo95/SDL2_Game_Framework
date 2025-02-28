#pragma once

namespace ELayer
{
	enum Type : signed char
	{
		NONE = -1,
		BACKGROUND,
		OBJECT,
		PROJECTILE,
		EFFECT,
		MAX
	};
}

namespace ESort
{
	enum Type : signed char
	{
		NONE,
		Y
	};
}