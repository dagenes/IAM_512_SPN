#include "LinearCryptanalysis.h"
#include "SPN.h"
#include "Utility.h"

namespace main
{

//JAVA TO C++ CONVERTER TODO TASK: No base class can be determined:
	LinearCryptanalysis::LinearCryptanalysis(SPN *spn, int iterNumber, bool verbose)
	{
		this->spn = spn;
		this->iterNumber = iterNumber;
		this->verbose = verbose;
	}

	void LinearCryptanalysis::attack(const std::wstring &key)
	{

		Utility *utility = new Utility();
		std::unordered_map<int, int> sBox = spn->getsBox();
		std::unordered_map<int, int> sBoxInverse = spn->getsBoxInverse();

		// TODO iyile�tirilebilir
		std::wstring key_5 = key.substr(key.length() - 4);
		int key_5_5_8 = key_5[1];
		int key_5_13_16 = key_5[3];

		if (verbose)
		{
			std::wcout << L"key is " << key << std::endl;
		}
		if (verbose)
		{
			std::wcout << L"key_5 is " << key_5 << std::endl;
		}
		if (verbose)
		{
			std::wcout << L"key_5_5_8 is " << key_5_5_8 << std::endl;
		}
		if (verbose)
		{
			std::wcout << L"key_5_13_16 is " << key_5_13_16 << std::endl;
		}

		// init prob bias matrix via sbox
		std::vector<std::vector<int>> probBias = initProbBias(sBox);

		// initialize with all zeros
		std::vector<int> countTargetBias(256);
		for (int i = 0; i <= 0 + iterNumber; i++)
		{

			std::wstring plain = utility->intToHex(i);
			std::wstring cipher = spn->encrypt(i, key);
//JAVA TO C++ CONVERTER TODO TASK: Only single-argument parse and valueOf methods are converted:
//ORIGINAL LINE: int cipher_5_8 = Integer.parseInt(cipher.substring(1, 1), 16);
			int cipher_5_8 = Integer::valueOf(cipher.substr(1, 1), 16);
//JAVA TO C++ CONVERTER TODO TASK: Only single-argument parse and valueOf methods are converted:
//ORIGINAL LINE: int cipher_13_16 = Integer.parseInt(cipher.substring(3, 1), 16);
			int cipher_13_16 = Integer::valueOf(cipher.substr(3, 1), 16); // utilityintToHex(cipher.charAt(3));

		//			if (verbose)
		//				System.out.println(
		//						"###### " + i + " " + utility.hexToInt(cipher) + " " + cipher_5_8 + " " + cipher_13_16);

			for (int j = 0; j < 256; j++)
			{

				std::wstring target = std::wstring::format(L"%02X", j);
//JAVA TO C++ CONVERTER TODO TASK: Only single-argument parse and valueOf methods are converted:
//ORIGINAL LINE: int target_5_8 = Integer.parseInt(target.substring(0, 1), 16);
				int target_5_8 = Integer::valueOf(target.substr(0, 1), 16);
//JAVA TO C++ CONVERTER TODO TASK: Only single-argument parse and valueOf methods are converted:
//ORIGINAL LINE: int target_13_16 = Integer.parseInt(target.substring(1, 1), 16);
				int target_13_16 = Integer::valueOf(target.substr(1, 1), 16);

				int v_5_8 = cipher_5_8 ^ target_5_8;
				int v_13_16 = cipher_13_16 ^ target_13_16;

				int u_5_8 = sBoxInverse[v_5_8];
				int u_13_16 = sBoxInverse[v_13_16];

				int lApprox = ((u_5_8 >> 2) & 0b1) ^ (u_5_8 & 0b1) ^ ((u_13_16 >> 2) & 0b1) ^ (u_13_16 & 0b1) ^ ((i >> 11) & 0b1) ^ ((i >> 9) & 0b1) ^ ((i >> 8) & 0b1);
				if (lApprox == 0)
				{
					countTargetBias[j] += 1;
				}
		//				if (verbose)
		//					System.out.println("       ******* " + j + " " + target_5_8 + " " + target_13_16 + " " + v_5_8 + " "
		//							+ v_13_16 + " " + u_5_8 + " " + u_13_16 + " " + lApprox);
			}
		}

		std::vector<double> bias(countTargetBias.size());
		for (int i = 0; i < countTargetBias.size(); i++)
		{
			int lAprx = countTargetBias[i];
			bias [i] = std::abs((lAprx - iterNumber / 2.0) / iterNumber);
		}

		double maxResult = 0;
		int maxIndex = 0;
		for (int i = 0; i < bias.size(); i++)
		{
			if (bias[i] > maxResult)
			{
				maxResult = bias[i];
				maxIndex = i;
			}
		}

		if (verbose)
		{
			std::wcout << L"Highest bias is " << maxResult << L", subkey is " << utility->intToHex(maxIndex) << std::endl;
		}

		if ((((maxIndex >> 4) & 0b1111) == key_5_5_8) && ((maxIndex & 0b1111) == key_5_13_16))
		{
			std::wcout << L"Success!" << std::endl;
		}
		else
		{
			std::wcout << L"Failure" << std::endl;
		}

		delete utility;
	}

	std::vector<std::vector<int>> LinearCryptanalysis::initProbBias(std::unordered_map<int, int> &sBox)
	{
		Utility *utility = new Utility();
//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: int[][] probBias = new int[16][16];
		std::vector<std::vector<int>> probBias = RectangularVectors::RectangularİntVector(16, 16);

		for (auto entry : sBox)
		{

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

			std::vector<int> eq_in = {0, x4, x3, x3 ^ x4, x2, x2 ^ x4, x2 ^ x3, x2 ^ x3 ^ x4, x1, x1 ^ x4, x1 ^ x3, x1 ^ x3 ^ x4, x1 ^ x2, x1 ^ x2 ^ x4, x1 ^ x2 ^ x3, x1 ^ x2 ^ x3 ^ x4};

			std::vector<int> eq_out = {0, y4, y3, y3 ^ y4, y2, y2 ^ y4, y2 ^ y3, y2 ^ y3 ^ y4, y1, y1 ^ y4, y1 ^ y3, y1 ^ y3 ^ y4, y1 ^ y2, y1 ^ y2 ^ y4, y1 ^ y2 ^ y3, y1 ^ y2 ^ y3 ^ y4};

			if (verbose)
			{
				std::wcout << x1 << L" " << x2 << L" " << x3 << L" " << x4 << std::endl;
				std::wcout << y1 << L" " << y2 << L" " << y3 << L" " << y4 << std::endl;
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
				std::wcout << Arrays->toString(eq_in) << std::endl;
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
				std::wcout << Arrays->toString(eq_out) << std::endl;
				std::wcout << std::endl;
			}
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					if (eq_in[i] == eq_out[j])
					{
						probBias[i][j]++;
					}
				}
			}
		}

		if (verbose)
		{
			// clone this array for print.
			std::vector<std::vector<int>> clone = probBias.clone();
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					clone[i][j] -= 8;
				}
			}
			for (auto is : clone)
			{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
				std::wcout << Arrays->toString(is) << std::endl;
			}
		}

		delete utility;
		return probBias;
	}
}
