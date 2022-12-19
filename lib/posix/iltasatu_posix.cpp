#include "../iltasatu.hpp"

#include <stdexcept>

Iltasatu::Iltasatu(size_t size) :
	_size(size),
	_data(new char[size])
{
	_context = fopen("/dev/random", "r");

	if (!_context)
	{
		throw std::runtime_error("fopen failed!");
	}
}

Iltasatu::~Iltasatu()
{
	fclose(reinterpret_cast<FILE*>(_context));
}

char* Iltasatu::Generate()
{
	if (!_context || !_data)
	{
		return nullptr;
	}

	size_t bytesRead = fread(_data, sizeof(char), _size, reinterpret_cast<FILE*>(_context));

	return bytesRead == _size ? _data : nullptr;
}
