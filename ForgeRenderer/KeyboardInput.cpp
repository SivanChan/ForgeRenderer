
#include "stdafx.h"
#include "KeyboardInput.h"

namespace Forge
{
	KeyboardInput::KeyboardInput()
	{
		keys_ = {};
	}

	KeyboardInput::~KeyboardInput()
	{

	}

	void KeyboardInput::KeyDown(uint32_t key)
	{
		keys_[key] = true;
	}

	void KeyboardInput::KeyUp(uint32_t key)
	{
		keys_[key] = false;
	}

	bool KeyboardInput::IsKeyDown(uint32_t key)
	{
		return keys_[key];
	}
}