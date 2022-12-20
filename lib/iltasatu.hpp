/*
	Iltasatu C++ class definition
*/

#pragma once

#include "iltasatu.h"

#include <string>

class Iltasatu
{
public:
	static IltasatuHandle Initialize(IltasatuOptions);

	virtual ~Iltasatu();

	char* Generate();
	void Mutate();

private:
	Iltasatu();

	uint32_t _mask = 0;
	void* _context = nullptr;
	std::string _allowed;
	std::string _random;
};