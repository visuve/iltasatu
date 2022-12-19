/*
	Iltasatu C-API implemetation
*/

#include "iltasatu.h"
#include "iltasatu.hpp"

#include <algorithm>
#include <random>
#include <set>

namespace
{
	template <typename T>
	static T RandomNumber(
		T max = std::numeric_limits<T>::max(),
		T min = std::numeric_limits<T>::min())
	{
		thread_local std::random_device device;
		thread_local std::mt19937 engine(device());
		thread_local std::uniform_int_distribution<T> distribution(min, max);

		return distribution(engine);
	}
}

namespace Alphabet
{
	const std::set<char> Punctuation =
	{
		' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
		':', ';', '<', '=', '>', '?', '@',
		'[', '\\', ']', '^', '_', '`',
		'{', '|', '}', '~'
	};

	const std::set<char> Number =
	{
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
	};

	const std::set<char> Uppercase =
	{
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	const std::set<char> Lowercase =
	{
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	std::set<char> Allowed(uint32_t mask)
	{
		std::set<char> result;

		for (uint32_t bit = 1; mask; mask &= ~bit, bit <<= 1)
		{
			switch (mask & bit)
			{
				case IltasatuMask::Punctuation:
					result.insert(
						Alphabet::Punctuation.cbegin(),
						Alphabet::Punctuation.cend());
					break;
				case IltasatuMask::Number:
					result.insert(
						Alphabet::Number.cbegin(),
						Alphabet::Number.cend());
					break;
				case IltasatuMask::Uppercase:
					result.insert(
						Alphabet::Uppercase.cbegin(),
						Alphabet::Uppercase.cend());
					break;
				case IltasatuMask::Lowercase:
					result.insert(
						Alphabet::Lowercase.cbegin(),
						Alphabet::Lowercase.cend());
					break;
			}
		}

		return result;
	}
}

void Iltasatu::Filter()
{
	if (!_options.Mask)
	{
		return; // Nothing to filter
	}

	std::set<char> allowed = Alphabet::Allowed(_options.Mask);
	size_t lastAllowedIndex = allowed.size() - 1;

	for (size_t i = 0; i < _options.Size; ++i)
	{
		char& x = _data[i];

		auto iter = allowed.find(x);

		if (iter == allowed.end())
		{
			iter = allowed.begin();
			size_t randomIndex = RandomNumber(lastAllowedIndex);
			std::advance(iter, randomIndex);
			x = *iter;
		}
	}
}

IltasatuHandle IltasatuInitialize(IltasatuOptions options)
{
	try
	{
		return reinterpret_cast<IltasatuHandle>(new Iltasatu(options));
	}
	catch (...)
	{
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

	char* result = iltasatu->Generate();

	iltasatu->Filter();

	return result;
}

void IltasatuDelete(IltasatuHandle handle)
{
	if (handle)
	{
		delete reinterpret_cast<Iltasatu*>(handle);
	}
}
