/*
	Iltasatu C++ class definition
*/

#include "stddef.h"

class Iltasatu
{
public:
	Iltasatu(size_t size);

	virtual ~Iltasatu();

	char* Generate();

private:
	void* _context = nullptr;

	size_t _size = 0;
	char* _data = nullptr;
};