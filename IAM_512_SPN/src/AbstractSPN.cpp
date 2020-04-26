/*
 * Created by HardCore on 18/04/2020.
 */
#include "AbstractSPN.h"

namespace main
{

	void AbstractSPN::initpBox()
	{
		sBox = std::unordered_map<int, int>();
		sBoxInverse = std::unordered_map<int, int>();

		sBox.emplace(0, 0xE);
		sBox.emplace(1, 0x4);
		sBox.emplace(2, 0xD);
		sBox.emplace(3, 0x1);
		sBox.emplace(4, 0x2);
		sBox.emplace(5, 0xF);
		sBox.emplace(6, 0xB);
		sBox.emplace(7, 0x8);
		sBox.emplace(8, 0x3);
		sBox.emplace(9, 0xA);
		sBox.emplace(0xA, 0x6);
		sBox.emplace(0xB, 0xC);
		sBox.emplace(0xC, 0x5);
		sBox.emplace(0xD, 0x9);
		sBox.emplace(0xE, 0x0);
		sBox.emplace(0xF, 0x7);
		for (auto entry : sBox)
		{
			sBoxInverse.emplace(entry.second, entry.first);
		}


	}

	void AbstractSPN::initsBox()
	{
		pBox = std::unordered_map<int, int>();
		pBox.emplace(0, 0);
		pBox.emplace(1, 4);
		pBox.emplace(2, 8);
		pBox.emplace(3, 12);
		pBox.emplace(4, 1);
		pBox.emplace(5, 5);
		pBox.emplace(6, 9);
		pBox.emplace(7, 13);
		pBox.emplace(8, 2);
		pBox.emplace(9, 6);
		pBox.emplace(0xA, 10);
		pBox.emplace(0xB, 14);
		pBox.emplace(0xC, 3);
		pBox.emplace(0xD, 7);
		pBox.emplace(0xE, 11);
		pBox.emplace(0xF, 15);
	}

	std::unordered_map<int, int> AbstractSPN::getsBox()
	{
		return sBox;
	}

	std::unordered_map<int, int> AbstractSPN::getsBoxInverse()
	{
		return sBoxInverse;
	}

	std::unordered_map<int, int> AbstractSPN::getpBox()
	{
		return pBox;
	}
}
