/********************************************************************
	created  :	2016/6/19
	author   :	Sivan
	source   :  º¸≈Ã ‰»Î
*********************************************************************/

#ifndef Forge_KeyboardInput_hpp__
#define Forge_KeyboardInput_hpp__

#pragma once

#include "PreDeclare.h"
#include <array>

namespace Forge
{
	class KeyboardInput
	{
	public:
		KeyboardInput();
		~KeyboardInput();
		
		void KeyDown(uint32_t key);
		void KeyUp(uint32_t key);
		bool IsKeyDown(uint32_t key);

	private:
		std::array<bool, 256> keys_;
	};
}

#endif // Forge_KeyboardInput_hpp__