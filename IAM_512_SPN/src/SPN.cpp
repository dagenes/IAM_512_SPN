#include "SPN.h"
#include "Utility.h"

namespace main
{

	SPN::SPN(bool verbose)
	{
		initsBox();
		initpBox();
		this->verbose = verbose;
		if (verbose)
		{
			std::wcout << L"\n-------------------PBOX-------------" << std::endl;
			for (auto entry : pBox)
			{
				std::wcout << entry.first << L" " << entry.second << std::endl;
			}
			std::wcout << L"--------------------------------" << std::endl;
		}
	}

	std::wstring SPN::encrypt(int plainText, const std::wstring &key)
	{
		int cipherText = plainText;

		if (verbose)
		{
			std::wcout << L"plaint text is " << plainText << std::endl;
		}

		std::vector<std::wstring> subKeys = subKeys(key);
		Utility *utility = new Utility();
		// first 3 key-mixing s-box and p-box
		for (int i = 0; i < 3; i++)
		{

			if (verbose)
			{
				std::wcout << L"Round " << (i + 1) << L" and subkey is " << utility->hexToInt(subKeys[i]) << std::endl;
			}
			cipherText = utility->XOR(cipherText, utility->hexToInt(subKeys[i]));
			if (verbose)
			{
				std::wcout << L"XOR " << cipherText << L" " << utility->intToHex(cipherText) << std::endl;
			}
			cipherText = performSbox(cipherText, false);
			if (verbose)
			{
				std::wcout << L"SBOX " << cipherText << L" " << utility->intToHex(cipherText) << std::endl;
			}
			cipherText = performPbox(cipherText);
			if (verbose)
			{
				std::wcout << L"PBOX " << cipherText << L" " << utility->intToHex(cipherText) << std::endl;
			}
			if (verbose)
			{
				std::wcout << std::endl;
			}
		}

		// fourth key-mixing and last s-box
		cipherText = utility->XOR(cipherText, utility->hexToInt(subKeys[3]));
		if (verbose)
		{
			std::wcout << L"4th XOR " << cipherText << L" " << utility->intToHex(cipherText) << std::endl;
		}
		cipherText = performSbox(cipherText, false);
		if (verbose)
		{
			std::wcout << L"Last SBOX " << cipherText << L" " << utility->intToHex(cipherText) << std::endl;
		}
		// last key mixing
		cipherText = utility->XOR(cipherText, utility->hexToInt(subKeys[4]));
		if (verbose)
		{
			std::wcout << L"Last XOR " << cipherText << L" " << utility->intToHex(cipherText) << std::endl;
		}

		delete utility;
		return utility->intToHex(cipherText);
	}

	void SPN::decrypt()
	{
		// TODO implement if needed
	}

	std::vector<std::wstring> SPN::subKeys(const std::wstring &key)
	{

		std::vector<std::wstring> subKeys;
		for (int i = 0; i < key.length(); i += 4)
		{
			subKeys.push_back(key.substr(i, 4));
		}
		return subKeys;
	}

	int SPN::performSbox(std::optional<int> &pt, bool isInverse)
	{
		std::vector<int> subPlaintTxt = Arrays::asList(pt & 0x000f, (pt & 0x00f0) >> 4, (pt & 0x0f00) >> 8, (pt & 0xf000) >> 12);
		for (int i = 0; i < subPlaintTxt.size(); i++)
		{
			subPlaintTxt[i] = sBox[subPlaintTxt[i]];
		}
		return subPlaintTxt[0] | subPlaintTxt[1] << 4 | subPlaintTxt[2] << 8 | subPlaintTxt[3] << 12;
	}

	int SPN::performPbox(std::optional<int> &pt)
	{
		Utility *utility = new Utility();
		int tmpCipher = 0;
		for (int j = 0; j < 16; j++)
		{
			if ((pt & (1 << j)) > 0)
			{
				tmpCipher = utility->OR(tmpCipher, 1 << pBox[j]);
			}
		}

		delete utility;
		return tmpCipher;
	}
}
