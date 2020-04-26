/*
 * Created by HardCore on 18/04/2020.
 */
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include "stringhelper.h"
#include "rectangularvectors.h"

/**
* COPYRIGHT : yesterday is yesterday, today is today.
*/
namespace main
{


	class Utility
	{

	private:
		static const std::vector<wchar_t> HEX_ARRAY;

	public:
		Utility();

		virtual std::wstring generateRandomKey();

		virtual std::wstring XOR(const std::wstring &s1, const std::wstring &s2);

		virtual int XOR(std::optional<int> &int1, std::optional<int> &int2);

		virtual std::wstring OR(const std::wstring &s1, const std::wstring &s2);

		virtual std::optional<int> OR(std::optional<int> &int1, std::optional<int> &int2);

		virtual std::wstring bytesToHex(std::vector<char> &bytes);

		virtual int hexToInt(const std::wstring &string);

		virtual std::wstring intToHex(int num);

		virtual std::wstring strToHex(const std::wstring &str);

		virtual std::vector<int> intToBit(int num);


	};

}
