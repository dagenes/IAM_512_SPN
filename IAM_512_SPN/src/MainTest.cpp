#include "MainTest.h"
#include "Utility.h"
#include "SPN.h"
#include "LinearCryptanalysis.h"

namespace main
{

	void MainTest::main(std::vector<std::wstring> &args)
	{

		Utility *utility = new Utility();

		//random key
		std::wstring key = utility->generateRandomKey();
		std::wcout << L"Random key is " << key << std::endl;
		std::wcout << key.length() << std::endl;
		SPN *spn = new SPN(false);


		LinearCryptanalysis *linear = new LinearCryptanalysis(spn, 10000, true);
		linear->attack(key);


		//		String pt = "1000";
		//		String ct = spn.encrypt(pt, key);
		//		System.out.println("\nciphertext is " + ct);

		delete linear;
//JAVA TO C++ CONVERTER TODO TASK: A 'delete spn' statement was not added since spn was passed to a method or constructor. Handle memory management manually.
		delete utility;
	}
}
