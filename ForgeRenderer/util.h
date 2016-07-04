/********************************************************************
	created:	2016/07/04
	created:	2016/7/4   23:53
	filename: 	util.h
	author:		Sivan
	purpose:	¹¤¾ß
*********************************************************************/

#ifndef Forge_util_hpp__
#define Forge_util_hpp__

#pragma once

#pragma warning (push)
// macro redefinition
#pragma warning(disable : 4005)

namespace Forge
{
	template<typename T>
	inline std::shared_ptr<T>
		MakeCOMPtr(T* p)
	{
		return std::shared_ptr<T>(p, std::mem_fn(&T::Release));
	}

	std::string &  StringConvert(std::wstring const & src, std::string  & dest);
	std::wstring & StringConvert(std::string  const & src, std::wstring & dest);
}

#endif // Forge_util_hpp__