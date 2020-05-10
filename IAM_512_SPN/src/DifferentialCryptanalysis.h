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
class DifferentialCryptanalysis {

	unsigned long diff_input = 1;
	unsigned long _diff_target = 1;

private:
	SPN *spn;
	int iterNumber;
	bool verbose = false;

public:
	virtual ~DifferentialCryptanalysis() {
		delete spn;
	}

	DifferentialCryptanalysis(SPN *spn, int iterNumber, bool verbose);

	virtual int attack(const std::vector<uint64_t> key);

};

//}
