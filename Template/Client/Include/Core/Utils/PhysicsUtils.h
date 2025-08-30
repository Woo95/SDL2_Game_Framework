#pragma once

#include "../Vector2D.h"

namespace PhysicsConfig
{
	inline const FVector2D GravityDir = FVector2D(0.0f, 9.8f);
	inline const float LinearDrag = 0.995f;
	inline const float PixelsPerMeter = 10.0f;
}

//////////////////////////////////////////////////////////////

enum class ERigidbodyType : unsigned char
{
	STATIC,
	DYNAMIC
};