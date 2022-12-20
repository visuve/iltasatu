#include "../iltasatu.hpp"

#include <stdexcept>
#define NOMINMAX
#include <Windows.h>
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

Iltasatu::Iltasatu()
{
	NTSTATUS status = BCryptOpenAlgorithmProvider(
		reinterpret_cast<BCRYPT_ALG_HANDLE*>(&_context),
		BCRYPT_RNG_ALGORITHM,
		MS_PRIMITIVE_PROVIDER,
		0);

	if (FAILED(status))
	{
		throw std::runtime_error("BCryptOpenAlgorithmProvider failed");
	}
}

Iltasatu::~Iltasatu()
{
	if (_context)
	{
		BCryptCloseAlgorithmProvider(_context, 0);
	}
}

char* Iltasatu::Generate()
{
	if (!_context)
	{
		throw std::logic_error("Iltasatu is not initialized");
	}

	NTSTATUS status = BCryptGenRandom(
		_context,
		reinterpret_cast<PUCHAR>(_random.data()),
		static_cast<ULONG>(_random.size()),
		0);

	if (FAILED(status))
	{
		throw std::runtime_error("BCryptOpenAlgorithmProvider failed");
	}

	return _random.data();
}
