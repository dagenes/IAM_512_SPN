/*
 * Created by HardCore on 18/04/2020.
 */

#include "DifferentialCryptanalysis.h"

#include <cstdint>
#include <utility>
#include <iomanip>

#include "SPN.h"
#include "Utility.h"

//namespace crypto
//{

DifferentialCryptanalysis::DifferentialCryptanalysis(SPN *spn, int iterNumber,
		bool verbose) {
	this->spn = spn;
	this->iterNumber = iterNumber;
	this->verbose = verbose;
}

int DifferentialCryptanalysis::attack(const std::vector<uint64_t> key) {

	//start timer
	std::clock_t start;
	start = std::clock();

	if (verbose)
		std::cout << "# of plaintext that will be used in attack is "
				<< iterNumber << std::endl;

	// get s-box inverse from SPN object
	std::unordered_map<int, int> sBoxInverse = spn->getsBoxInverse();

	// initialize with all zeros
	std::vector<int> counterBias(256);

	// iterate with given number
	for (int i = 0; i < iterNumber; i++) {

		// get random plaintext
		uint64_t p1 = i;
		uint64_t p2 = i ^ 0xb00;

		//encryption
		uint64_t c1 = spn->encrypt(p1, key);
		uint64_t c2 = spn->encrypt(p2, key);

//		if (verbose)
//			std::cout << std::hex << p1 << "->" << c1 << "   " << p2 << "->"
//					<< c2 << std::endl;

		if ((c1 & 0xF0F0) == (c2 & 0xF0F0)) { // S41 and S43 must be zero in the paper
			for (uint64_t j = 0; j < 16; j++) {
				for (uint64_t k = 0; k < 16; k++) {
					int u42_c1 = sBoxInverse[j ^ ((c1 & 0xF00) >> 8)];
					int u44_c1 = sBoxInverse[k ^ ((c1 & 0xF))];
					int u42_c2 = sBoxInverse[j ^ ((c2 & 0xF00) >> 8)];
					int u44_c2 = sBoxInverse[k ^ ((c2 & 0xF))];

					// equation 6 (delta U= [0000 0110 0000 0110] )
					if ((u42_c1 ^ u42_c2) == 0x6 && (u44_c1 ^ u44_c2) == 0x6) {
						int subkey = j * 16 + k;
						counterBias[subkey] += 1;
					}
				}
			}
		}
	}

	// find max index
	double max = 0;
	int index = 0;
	int length = 256;
	for (int i = 0; i < length; i++) {
//		if ((double) counterBias[i] / iterNumber > 0.001)
//			std::wcout << std::hex << i << std::dec << " "
//					<< ((double) counterBias[i] / iterNumber) << std::endl;
		if (counterBias[i] > max) {
			max = counterBias[i];
			index = i;
		}
	}

	if (verbose)
		std::wcout << "max index is 0x" << std::hex << index << std::dec
				<< " with probability " << (max / iterNumber) << std::endl;

	if (verbose) {
		//end timer
		double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
		std::cout << "~~~~~~~~~Differential attack takes " << duration << " sec"
				<< std::endl;
	}

	return index;

}

//}
