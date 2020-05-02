/*
 * Created by HardCore on 18/04/2020.
 */
#pragma once

#include "AbstractSPN.h"
#include <string>
#include <vector>
#include <iostream>
//#include <optional>
#include "rectangularvectors.h"
//#include <experimental/optional>


/**
* COPYRIGHT : yesterday is yesterday, today is today.
*/
//namespace crypto
//{


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
		virtual uint64_t encrypt(uint64_t plainText, std::vector<uint64_t> key);

		virtual void decrypt();

	private:

		uint64_t encryptBlock(uint64_t plainText, std::vector<uint64_t> key);
		std::vector<uint64_t> subKeys(const std::vector<uint64_t> key);

		/**
		 * @param plainText
		 * @param isInverse
		 * @return
		 */
		int performSbox(int pt, bool isInverse);

		/**
		 * @param pt
		 * @return
		 */
		int performPbox(int pt);
	};

//}
