#pragma once

namespace ECollider
{
	enum Type : unsigned char
	{
		NONE,
		BOX,
		CIRCLE
	};

	enum OnCollision : unsigned char
	{
		ENTER,
		STAY,
		EXIT,
		MAX
	};
}