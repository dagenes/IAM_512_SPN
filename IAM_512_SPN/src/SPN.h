#pragma once

#include "AbstractSPN.h"
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include "rectangularvectors.h"

/**
* COPYRIGHT : yesterday is yesterday, today is today.
*/
namespace main
{


	/**
	 * A class containing simple substituiton-permutation network cipher.
	 * 
	 * @author HC
	 * @date 18 Nis 2020
	 * @project_name IAM_512_SPN
	 */
	class SPN : public AbstractSPN
	{

	private:
		bool verbose = false;

	public:
		SPN(bool verbose);

		/**
		 * @param plainText
		 * @param key
		 * @return
		 */
		virtual std::wstring encrypt(int plainText, const std::wstring &key);

		virtual void decrypt();

	private:
		std::vector<std::wstring> subKeys(const std::wstring &key);

		/**
		 * @param plainText
		 * @param isInverse
		 * @return
		 */
		int performSbox(std::optional<int> &pt, bool isInverse);

		/**
		 * @param pt
		 * @return
		 */
		int performPbox(std::optional<int> &pt);
	};

}
