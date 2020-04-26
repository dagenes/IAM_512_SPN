/*
 * Created by HardCore on 18/04/2020.
 */
#pragma once

#include <unordered_map>

namespace main
{


	/**
	 * An abstract class containing simple substituiton-permutation network cipher.
	 * 
	 * @author HC
	 * @date 18 Nis 2020
	 * @project_name IAM_512_SPN
	 */
	class AbstractSPN
	{

	protected:
		std::unordered_map<int, int> sBox;
		std::unordered_map<int, int> sBoxInverse;
		std::unordered_map<int, int> pBox;

		virtual void initpBox();

		virtual void initsBox();

	public:
		virtual std::unordered_map<int, int> getsBox();

		virtual std::unordered_map<int, int> getsBoxInverse();

		virtual std::unordered_map<int, int> getpBox();

	};

}
