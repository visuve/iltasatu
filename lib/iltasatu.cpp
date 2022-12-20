/*
	Iltasatu C-API implemetation
*/

#include "iltasatu.h"
#include "iltasatu.hpp"

#include <set>

#ifdef _DEBUG
#include <iostream>
#endif

namespace Alphabet
{
	constexpr char Punctuation[] =
	{
		' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
		':', ';', '<', '=', '>', '?', '@',
		'[', '\\', ']', '^', '_', '`',
		'{', '|', '}', '~'
	};

	constexpr char Number[] =
	{
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
	};

	constexpr char Uppercase[] =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	constexpr char Lowercase[] =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	std::string Allowed(uint32_t mask)
	{
		std::string result;

		for (uint32_t bit = 1; mask; mask &= ~bit, bit <<= 1)
		{
			switch (mask & bit)
			{
				case IltasatuMask::Punctuation:
					result += Alphabet::Punctuation;
					break;
				case IltasatuMask::Number:
					result += Alphabet::Number;
					break;
				case IltasatuMask::Uppercase:
					result += Alphabet::Uppercase;
					break;
				case IltasatuMask::Lowercase:
					result += Alphabet::Lowercase;
					break;
			}
		}

		return result;
	}
}


IltasatuHandle Iltasatu::Initialize(IltasatuOptions options)
{
	auto iltasatu = new Iltasatu();

	iltasatu->_mask = options.Mask;
	iltasatu->_random = std::string(options.Size, '\0');
	iltasatu->_allowed = Alphabet::Allowed(options.Mask);

	return reinterpret_cast<IltasatuHandle>(iltasatu);
}

void Iltasatu::Mutate()
{
	if (!_mask)
	{
		return;
	}

	const size_t lastAllowedIndex = _allowed.size() - 1;

	for (char& c : _random)
	{
		size_t randomAllowedIndex = c % lastAllowedIndex;
		c = _allowed[randomAllowedIndex];
	}
}

IltasatuHandle IltasatuInitialize(IltasatuOptions options)
{
	try
	{
		return Iltasatu::Initialize(options);
	}
	catch ([[maybe_unused]] const std::exception& e)
	{
#ifdef _DEBUG
		std::cerr << e.what() << std::endl;
#endif
		return nullptr;
	}
}

char* IltasatuGenerate(IltasatuHandle handle)
{
	if (!handle)
	{
		return nullptr;
	}

	auto iltasatu = reinterpret_cast<Iltasatu*>(handle);

	if (!iltasatu)
	{
		return nullptr;
	}

	try
	{
		char* result = iltasatu->Generate();
		
		iltasatu->Mutate();

		return result;
	}
	catch ([[maybe_unused]] const std::exception& e)
	{
#ifdef _DEBUG
		std::cerr << e.what() << std::endl;
#endif
		return nullptr;
	}
}

void IltasatuDelete(IltasatuHandle handle)
{
	if (!handle)
	{
		return;
	}

	auto iltasatu =  reinterpret_cast<Iltasatu*>(handle);

	if (!iltasatu)
	{
		return;
	}

	delete iltasatu;
}
