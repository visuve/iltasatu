#include "../iltasatu.hpp"
#include <stdexcept>

Iltasatu::Iltasatu(IltasatuOptions options) :
	_options(options),
	_data(new char[options.Size])
{
	_context = fopen("/dev/urandom", "r");

	if (!_context)
	{
		throw std::runtime_error("fopen failed!");
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
	if (!_context || !_data)
	{
		return nullptr;
	}

	size_t bytesRead = fread(
		_data, 
		sizeof(char), 
		_options.Size,
		reinterpret_cast<FILE*>(_context));

	return bytesRead == _options.Size ? _data : nullptr;
}
