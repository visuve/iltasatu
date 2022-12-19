/*
	Iltasatu C-API implemetation
*/

#include "iltasatu.h"
#include "iltasatu.hpp"

IltasatuHandle* IltasatuInitialize(size_t size)
{
	try
	{
		return reinterpret_cast<IltasatuHandle*>(new Iltasatu(size));
	}
	catch (...)
	{
		return nullptr;
	}
}

char* IltasatuGenerate(IltasatuHandle* handle)
{
	if (!handle)
	{
		return nullptr;
	}

	return reinterpret_cast<Iltasatu*>(handle)->Generate();
}

void IltasatuDelete(IltasatuHandle* handle)
{
	if (handle)
	{
		delete reinterpret_cast<Iltasatu*>(handle);
	}
}
