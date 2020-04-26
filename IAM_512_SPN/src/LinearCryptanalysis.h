#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>
#include "rectangularvectors.h"

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace main { class SPN; }

/**
* COPYRIGHT : yesterday is yesterday, today is today.
*/
namespace main
{


	/**
	 * @author HC
	 * @date 19 Nis 2020
	 * @project_name IAM_512_SPN
	 */
	class LinearCryptanalysis
	{

	private:
		SPN *spn;

		int iterNumber = 0;

		bool verbose = false;

	public:
		virtual ~LinearCryptanalysis()
		{
			delete spn;
		}

//JAVA TO C++ CONVERTER TODO TASK: No base class can be determined:
		LinearCryptanalysis(SPN *spn, int iterNumber, bool verbose); //super();

		virtual void attack(const std::wstring &key);

		/**
		 * @param sBox
		 * @return
		 */
	private:
		std::vector<std::vector<int>> initProbBias(std::unordered_map<int, int> &sBox);

	};

}
