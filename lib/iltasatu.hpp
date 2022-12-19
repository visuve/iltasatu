/*
	Iltasatu C++ class definition
*/

#pragma once

#include "iltasatu.h"

class Iltasatu
{
public:
	Iltasatu(IltasatuOptions);

	virtual ~Iltasatu();

	char* Generate();
	void Filter();

private:
	void* _context = nullptr;
	IltasatuOptions _options;
	char* _data = nullptr;
};