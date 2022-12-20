#include "../iltasatu.hpp"
#include <stdexcept>

Iltasatu::Iltasatu(IltasatuOptions options) :
	_options(options),
	_data(new char[options.Size])
{
	_context = fopen("/dev/urandom", "r");

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

	if (_data)
	{
		delete[] data;
	}
}

char* Iltasatu::Generate()
{
	if (!_context || !_data)
	{
		throw std::logic_error("Iltasatu is not initialized");
	}

	size_t bytesRead = fread(
		_data, 
		sizeof(char), 
		_options.Size,
		reinterpret_cast<FILE*>(_context));

	if (bytesRead != _options.Size)
	{
		throw std::runtime_error("fread failed");
	}

	return _data;
}
