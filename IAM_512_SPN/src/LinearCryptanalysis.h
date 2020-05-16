/*
 * Created by HardCore on 18/04/2020.
 */
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
//namespace crypto {
class SPN;
//}

/**
* COPYRIGHT : yesterday is yesterday, today is today.
*/
//namespace crypto
//{


	/**
	 * @author HC
	 * @date 19 Nis 2020
	 * @project_name IAM_512_SPN
	 */
	class LinearCryptanalysis
	{

	private:
		SPN *spn;

		bool verbose = false;

	public:
		virtual ~LinearCryptanalysis()
		{
			delete spn;
		}

		LinearCryptanalysis(SPN *spn, bool verbose);

		virtual int attack(const std::vector<uint64_t> key);

		/**
		 * @param sBox
		 * @return
		 */
	private:
		std::vector<std::vector<int>> initLAT(std::unordered_map<int, int> &sBox);

	};

//}
