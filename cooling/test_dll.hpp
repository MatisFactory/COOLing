#include "export/cooling_dll.hpp"

#include <iostream>

class COOLING_DLL Test
{
public:
	void foo() {
		std::cout << "it's test\n";
	}

	void foo1();
};