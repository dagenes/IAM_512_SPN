/*
 * Created by HardCore on 18/04/2020.
 */
#pragma once

#include <string>
#include <vector>
#include <iostream>
//#include <optional>
#include "stringhelper.h"
#include "rectangularvectors.h"
#include <experimental/optional>

/**
 * COPYRIGHT : yesterday is yesterday, today is today.
 */
//namespace crypto {

class Utility {

private:
	static const std::vector<wchar_t> HEX_ARRAY;

public:
	Utility();

	virtual std::vector<uint64_t> generateRandomKey();

	virtual std::wstring XOR(const std::wstring &s1, const std::wstring &s2);

	virtual int XOR(int int1, int int2);

	virtual std::wstring OR(const std::wstring &s1, const std::wstring &s2);

	virtual int OR(int int1, int int2);

	virtual std::wstring bytesToHex(std::vector<char> &bytes);

	virtual int hexToInt(const std::wstring &string);

	virtual std::wstring intToHex(int num);

	virtual std::wstring strToHex(const std::wstring &str);

	virtual std::vector<int> intToBit(int num);

};

//}
