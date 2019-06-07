#include"stdafx.h"
#include <iostream>
#include "Automat.h"

int main()
{
	std::cout << "Automat1:\n";
	Automat Automat1;
	Automat1.insertState(true);
	Automat1.insertTransition(0, 'a', 1);
	Automat1.insertTransition(0, 'b', 1);
	Automat1.insertTransition(1, 'a', 0);
	Automat1.insertTransition(1, 'b', 0);
	Automat1.insertTransition(1, 'c', 1);
	std::cout << Automat1;
	std::cout << Automat1.member("abba") << std::endl;
	std::cout << Automat1.member("acccccccba") << std::endl;
	std::cout << std::endl;
	Automat Automat2(2, 0, { 0 });
	Automat2.insertTransition(0, 'a', 0);
	Automat2.insertTransition(0, 'b', 1);
	Automat2.insertTransition(1, 'a', 1);
	Automat2.insertTransition(1, 'b', 0);

	std::cout << "UNION of Automat1 and Automat2:\n";
	Automat Automat3 = Automat1 + Automat2;
	std::cout << Automat3;
	std::cout<< Automat3.member("abbaba") << std::endl;
	std::cout << Automat3.member("aabbaa") << std::endl;
	std::cout << std::endl;
	std::cout << "INTERSECTION of Automat1 and Automat2\n";
	Automat Automat4 = Automat1 * Automat2;
	std::cout << Automat4;
	std::cout << Automat4.member("abb") << std::endl;
	std::cout << Automat4.member("aab") << std::endl;
	std::cout << std::endl;
	
	return 0;
}