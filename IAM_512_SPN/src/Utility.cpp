#include "Utility.h"

namespace main
{

const std::vector<wchar_t> Utility::HEX_ARRAY = (std::wstring(L"0123456789ABCDEF")).toCharArray();

	Utility::Utility()
	{
	}

	std::wstring Utility::generateRandomKey()
	{
		Random *r = new Random();
		//		return Long.toHexString(r.nextLong()) + Integer.toHexString(r.nextInt()).substring(0, 4);

		delete r;
		return L"81cfb457f1101c3b06f6";
	}

	std::wstring Utility::XOR(const std::wstring &s1, const std::wstring &s2)
	{
//JAVA TO C++ CONVERTER TODO TASK: Only single-argument parse and valueOf methods are converted:
//ORIGINAL LINE: s2 = Integer.toString(Integer.parseInt(s2, 16));
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
		s2 = Integer::toString(Integer::valueOf(s2, 16));
		std::vector<char> a = s1.getBytes();
		std::vector<char> b = s2.getBytes();
		std::vector<char> out(a.size());
		for (int i = 0; i < a.size(); i++)
		{
			out[i] = static_cast<char>(a[i] ^ b[i % b.size()]);
		}
		std::wcout << bytesToHex(out) << std::endl;
		return std::wstring(out);
	}

	int Utility::XOR(std::optional<int> &int1, std::optional<int> &int2)
	{
		int xored = int2 ^ int1;
		return xored;
	}

	std::wstring Utility::OR(const std::wstring &s1, const std::wstring &s2)
	{
		std::vector<char> a = s1.getBytes();
		std::vector<char> b = s2.getBytes();
		std::vector<char> out(a.size());
		for (int i = 0; i < a.size(); i++)
		{
			out[i] = static_cast<char>(a[i] | b[i % b.size()]);
		}
		return std::wstring(out);
	}

	std::optional<int> Utility::OR(std::optional<int> &int1, std::optional<int> &int2)
	{
		int xored = int2 | int1;
		return xored;
	}

	std::wstring Utility::bytesToHex(std::vector<char> &bytes)
	{
		std::vector<wchar_t> hexChars(bytes.size() * 2);
		for (int j = 0; j < bytes.size(); j++)
		{
			int v = bytes[j] & 0xFF;
			hexChars[j * 2] = HEX_ARRAY[static_cast<int>(static_cast<unsigned int>(v) >> 4)];
			hexChars[j * 2 + 1] = HEX_ARRAY[v & 0x0F];
		}
		return std::wstring(hexChars);
	}

	int Utility::hexToInt(const std::wstring &string)
	{
//JAVA TO C++ CONVERTER TODO TASK: Only single-argument parse and valueOf methods are converted:
//ORIGINAL LINE: return Integer.parseInt(string, 16);
		return Integer::valueOf(string, 16);
	}

	std::wstring Utility::intToHex(int num)
	{
		std::wstring str = Integer::toHexString(num);
		while (str.length() < 4)
		{
			str = StringHelper::toString(L'0') + str;
		}
		return str;
	}

	std::wstring Utility::strToHex(const std::wstring &str)
	{
		return bytesToHex(str.getBytes());
	}

	std::vector<int> Utility::intToBit(int num)
	{
		std::vector<int> bits(4);
		for (int i = 3; i >= 0; i--)
		{
			bits[i] = ((num & (1 << i)) != 0) ? 1 : 0;
		}

		 return bits;
	}
}