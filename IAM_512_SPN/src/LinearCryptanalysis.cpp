/*
 * Created by HardCore on 18/04/2020.
 */

#include "LinearCryptanalysis.h"

#include <cstdint>
#include <utility>
#include <iomanip>

#include "SPN.h"
#include "Utility.h"

//namespace crypto
//{

LinearCryptanalysis::LinearCryptanalysis(SPN *spn, int iterNumber,
		bool verbose) {
	this->spn = spn;
	this->iterNumber = iterNumber;
	this->verbose = verbose;
}

int LinearCryptanalysis::attack(const std::vector<uint64_t> key) {

	// get s-box and its inverse from SPN object
	std::unordered_map<int, int> sBox = spn->getsBox();
	std::unordered_map<int, int> sBoxInverse = spn->getsBoxInverse();

	// init prob bias matrix via sbox
	std::vector<std::vector<int>> probBias = initProbBias(sBox);

// initialize with all zeros
	std::vector<int> countTargetBias(256);
	for (int i = 0; i <= iterNumber; i++) {

		// get random plaintext
		uint64_t plain = i;
		uint64_t cipher = spn->encrypt(plain, key);
		uint64_t cipher_5_8 = (cipher >> 8) & 0xf;
		uint64_t cipher_13_16 = cipher & 0xf;

//		std::cout << "###### " << std::hex << plain << " -> " << cipher << " "
//				<< cipher_5_8 << " " << cipher_13_16 << std::endl;

		for (int j = 0; j < 256; j++) {
			uint64_t target = j;
			uint64_t target_5_8 = (target >> 4) & 0xf;
			uint64_t target_13_16 = target & 0xf;

			int v_5_8 = cipher_5_8 ^ target_5_8;
			int v_13_16 = cipher_13_16 ^ target_13_16;

			int u_5_8 = sBoxInverse[v_5_8];
			int u_13_16 = sBoxInverse[v_13_16];

			// equation 5 in the paper
			int lApprox = ((u_5_8 >> 2) & 0b1) ^ (u_5_8 & 0b1)
					^ ((u_13_16 >> 2) & 0b1) ^ (u_13_16 & 0b1)
					^ ((i >> 11) & 0b1) ^ ((i >> 9) & 0b1) ^ ((i >> 8) & 0b1);
			if (lApprox == 0)
				countTargetBias[j] += 1;
//			if (verbose)
//				std::cout << "     ****** " << std::dec << j << " "
//						<< target_5_8 << " " << target_13_16 << " " << v_5_8
//						<< " " << v_13_16 << " " << u_5_8 << " " << u_13_16
//						<< " " << lApprox << std::endl;
		}
	}

	std::vector<double> bias(256);
	for (int i = 0; i < (int) countTargetBias.size(); i++) {
		int lAprx = countTargetBias[i];
		bias[i] = std::abs((lAprx - iterNumber / 2.0) / iterNumber);
	}

	double max = 0;
	int index = 0;
	for (int i = 0; i < bias.size(); i++) {
		if (bias[i] > max) {
			max = bias[i];
			index = i;
		}
	}

	if (verbose)
		std::wcout << L"Highest bias is " << max << L", subkey is 0x"
				<< std::hex << index << std::endl;

	return index;
}

std::vector<std::vector<int>> LinearCryptanalysis::initProbBias(
		std::unordered_map<int, int> &sBox) {

	Utility *utility = new Utility();

	// 16x16 bias matrix
	std::vector<std::vector<int>> probBias(16, std::vector<int> (16, 0));

	for (auto entry : sBox) {

		std::vector<int> key = utility->intToBit(entry.first);
		int x1 = key[3];
		int x2 = key[2];
		int x3 = key[1];
		int x4 = key[0];
		std::vector<int> value = utility->intToBit(entry.second);
		int y1 = value[3];
		int y2 = value[2];
		int y3 = value[1];
		int y4 = value[0];

		std::vector<int> eq_in = { 0, x4, x3, x3 ^ x4, x2, x2 ^ x4, x2 ^ x3, x2
				^ x3 ^ x4, x1, x1 ^ x4, x1 ^ x3, x1 ^ x3 ^ x4, x1 ^ x2, x1 ^ x2
				^ x4, x1 ^ x2 ^ x3, x1 ^ x2 ^ x3 ^ x4 };

		std::vector<int> eq_out = { 0, y4, y3, y3 ^ y4, y2, y2 ^ y4, y2 ^ y3, y2
				^ y3 ^ y4, y1, y1 ^ y4, y1 ^ y3, y1 ^ y3 ^ y4, y1 ^ y2, y1 ^ y2
				^ y4, y1 ^ y2 ^ y3, y1 ^ y2 ^ y3 ^ y4 };

		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				if (eq_in[i] == eq_out[j]) {
					probBias[i][j]++;
				}
			}
		}
	}

	if (verbose) {
		// clone this array for print.
		std::vector<std::vector<int>> clone(16, std::vector<int> (16, 0));
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				clone[i][j] = probBias[i][j] - 8;
			}
		}

		std::cout << "Linear Approximation Table is: \n";
		for (int i = 0; i < clone.size(); i++) {
			for (int j = 0; j < clone[i].size(); j++) {
				std::cout << std::dec << std::setfill('0') << std::setw(2)<< clone[i][j] << " ";
			}
			std::cout << std::endl;
		}
			std::cout << std::endl;
	}

	delete utility;
//		return std::vector<std::vector<int>> ;
	return probBias;
}
//}
