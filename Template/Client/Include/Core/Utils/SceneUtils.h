#pragma once

enum class ESceneState : unsigned char
{
	NONE,
	MENU,
	PLAY
};

enum class ETransition : unsigned char
{
	NONE,
	PUSH,
	POP,
	SWAP,
	CLEAR,
	CLEAR_THEN_PUSH
};