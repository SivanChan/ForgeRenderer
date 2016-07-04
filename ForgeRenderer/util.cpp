
#include <stdafx.h>
#include <util.h>
#include <cstdlib>
#include <vector>

namespace Forge
{
	std::string & StringConvert(std::wstring const & src, std::string & dest)
	{
		int const mbs_len = WideCharToMultiByte(CP_ACP, 0, src.c_str(), static_cast<int>(src.size()), NULL, 0, NULL, NULL);
		std::vector<char> tmp(mbs_len + 1);
		WideCharToMultiByte(CP_ACP, 0, src.c_str(), static_cast<int>(src.size()), &tmp[0], mbs_len, NULL, NULL);
		dest.assign(tmp.begin(), tmp.end() - 1);
		return dest;
	}

	std::wstring & StringConvert(std::string const & src, std::wstring & dest)
	{
		int const wcs_len = MultiByteToWideChar(CP_ACP, 0, src.c_str(), static_cast<int>(src.size()), NULL, 0);
		std::vector<wchar_t> tmp(wcs_len + 1);
		MultiByteToWideChar(CP_ACP, 0, src.c_str(), static_cast<int>(src.size()), &tmp[0], wcs_len);
		dest.assign(tmp.begin(), tmp.end() - 1);
		return dest;
	}
}