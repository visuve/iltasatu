#include "../iltasatu.hpp"
#include <stdexcept>

Iltasatu::Iltasatu() :
	_context(fopen("/dev/urandom", "r"))
{
	if (!_context)
	{
		throw std::runtime_error("fopen failed");
	}
}

Iltasatu::~Iltasatu()
{
	if (_context)
	{
		fclose(reinterpret_cast<FILE*>(_context));
	}
}

char* Iltasatu::Generate()
{
	if (!_context)
	{
		throw std::logic_error("Iltasatu is not initialized");
	}

	size_t bytesRead = fread(
		_random.data(),
		sizeof(char), 
		_random.size(),
		reinterpret_cast<FILE*>(_context));

	if (bytesRead != _random.size())
	{
		throw std::runtime_error("fread failed");
	}

	return _random.data();
}
