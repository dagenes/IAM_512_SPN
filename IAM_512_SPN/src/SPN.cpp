/*
 * Created by HardCore on 18/04/2020.
 */
#include "SPN.h"
#include "Utility.h"
#include <experimental/optional>

//namespace crypto {

SPN::SPN(bool verbose) {
	initsBox();
	initpBox();
	this->verbose = verbose;
	if (verbose) {
		std::wcout << L"\n-------------------SBOX-------------" << std::endl;
		for (auto entry : sBox) {
			std::wcout << entry.first << L"->" << entry.second << ", ";
		}
		std::wcout << L"\n--------------------------------" << std::endl;
		std::wcout << L"\n-------------------PBOX-------------" << std::endl;
		for (auto entry : pBox) {
			std::wcout << entry.first << L"->" << entry.second << ", ";
		}
		std::wcout << L"\n--------------------------------" << std::endl;
	}
}

uint64_t SPN::encrypt(uint64_t plainText, std::vector<uint64_t> key) {

	uint64_t cipherText = plainText;

	if (verbose) {
		std::wcout << L"plaint text is " << plainText << std::endl;
	}

	std::vector<uint64_t> subKeys = SPN::subKeys(key);
	Utility *utility = new Utility();
	// first 3 key-mixing s-box and p-box
	for (int i = 0; i < 3; i++) {

		if (verbose)
			std::wcout << L"Round " << (i + 1) << L" and subkey is "
					<< subKeys[i] << std::endl;
		cipherText = utility->XOR(cipherText, subKeys[i]);
		if (verbose)
			std::wcout << L"XOR " << cipherText << std::endl;
		cipherText = performSbox(cipherText, false);
		if (verbose)
			std::wcout << L"SBOX " << cipherText << std::endl;
		cipherText = performPbox(cipherText);
		if (verbose)
			std::wcout << L"PBOX " << cipherText << std::endl;
		if (verbose)
			std::wcout << std::endl;
	}

	// fourth key-mixing and last s-box
	cipherText = utility->XOR(cipherText, subKeys[3]);
	if (verbose)
		std::wcout << L"4th XOR " << cipherText << L" "
				<< utility->intToHex(cipherText) << std::endl;
	cipherText = performSbox(cipherText, false);
	if (verbose)
		std::wcout << L"Last SBOX " << cipherText << L" "
				<< utility->intToHex(cipherText) << std::endl;
	// last key mixing
	cipherText = utility->XOR(cipherText, subKeys[4]);
	if (verbose)
		std::wcout << L"Last XOR " << cipherText << L" "
				<< utility->intToHex(cipherText) << std::endl;

	delete utility;
//	return utility->intToHex(cipherText);
	return cipherText;
}

void SPN::decrypt() {
	// TODO implement if needed
}

std::vector<uint64_t> SPN::subKeys(const std::vector<uint64_t> key) {

	std::vector<uint64_t> subKeys;

	subKeys.push_back(key[0] & 0xffff);
	subKeys.push_back((key[1] >> 48) & 0xffff);
	subKeys.push_back((key[1] >> 32) & 0xffff);
	subKeys.push_back((key[1] >> 16) & 0xffff);
	subKeys.push_back(key[1] & 0xffff);

//	for (int i = 0; i < key.length(); i += 4) {
//		subKeys.push_back(key.substr(i, 4));
//	}

	return subKeys;
}

int SPN::performSbox(int pt, bool isInverse) {
	int subPlaintTxt[4] = { pt & 0x000f, (pt & 0x00f0) >> 4, (pt & 0x0f00) >> 8,
			(pt & 0xf000) >> 12 };
	for (int i = 0; i < sizeof(subPlaintTxt) / sizeof(subPlaintTxt[0]); i++) {
		subPlaintTxt[i] = sBox[subPlaintTxt[i]];
	}
	return subPlaintTxt[0] | subPlaintTxt[1] << 4 | subPlaintTxt[2] << 8
			| subPlaintTxt[3] << 12;
}

int SPN::performPbox(int pt) {
	Utility *utility = new Utility();
	int tmpCipher = 0;
	for (int j = 0; j < 16; j++) {
		if ((pt & (1 << j)) > 0) {
			tmpCipher = utility->OR(tmpCipher, 1 << pBox[j]);
		}
	}

	delete utility;
	return tmpCipher;
}
//}
