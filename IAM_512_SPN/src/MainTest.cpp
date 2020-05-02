/*
 * Created by HardCore on 18/04/2020.
 */
//#include "MainTest.h"
#include "Utility.h"
#include "SPN.h"
#include "LinearCryptanalysis.h"
#include <string>
#include <vector>
#include <iostream>

//namespace crypto
//{

void encryptExample(std::vector<uint64_t> key);
void linearAttackExample(std::vector<uint64_t> key);

int main() {

	std::cout << "mahmut is in our heart " << std::endl;

	//generate random key
	Utility *utility = new Utility();
	std::vector<uint64_t> key = utility->generateRandomKey();
	std::wcout << "Random key is " << std::hex << key[0] << key[1] << std::endl;

//	encryptExample(key);
	linearAttackExample(key);

	delete utility;
	std::wcout
			<< "************************** END OF PROGRAM ***********************"
			<< std::endl;
}

void encryptExample(std::vector<uint64_t> key) {

	std::wcout
			<< "\n************************** ENCRYPTION EXAMPLE ***********************"
			<< std::endl;

	SPN *spn = new SPN(false);
	std::wcout << "SPN is constructed.." << std::endl;
	uint64_t pt = 0x3E8;
	uint64_t ct = 0x00;

	std::wcout << "plain text is " << std::dec << pt << "(int) = " << std::hex
			<< pt << "(hex)" << std::endl;
	ct = spn->encrypt(pt, key);
	std::wcout << "cipher text is " << std::dec << ct << "(int) = " << std::hex
			<< ct << "(hex)" << std::endl;

}

void linearAttackExample(std::vector<uint64_t> key) {

	std::wcout
			<< "\n************************** LINEAR ATTACK EXAMPLE ***********************"
			<< std::endl;
	SPN *spn = new SPN(false);
	LinearCryptanalysis *linear = new LinearCryptanalysis(spn, 10000, true);
	int maxIndex = linear->attack(key);

	uint64_t key_4 = key[1] & 0xffff;
	uint64_t key_i3 = (key_4 >> 8) & 0xf;
	uint64_t key_i1 = key_4 & 0xf;

	uint64_t index_i3 = (maxIndex >> 4) & 0xF;
	uint64_t index_i1 = maxIndex & 0xF;

	std::wcout << "key is 0x" << std::hex << key[0] << key[1] << std::endl;
	std::wcout << "key last 4 digit is 0x" << key_4 << std::endl;
	std::wcout << "max index is 0x" << index_i3 << " and 0x" << index_i1 << std::endl;

	if ((index_i3 == key_i3)
			&& (index_i1 == key_i1))
		std::wcout << "Attack is successful!" << std::endl;
	else
		std::wcout << "TRY AGAIN :)" << std::endl;

	delete linear;

}

//}
