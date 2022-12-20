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
	Iltasatu(IltasatuOptions);

	void* _context = nullptr;
	IltasatuOptions _options;
	std::string _allowed;
	char* _data = nullptr;
};