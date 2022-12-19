#include "../iltasatu.hpp"

#include <stdexcept>

#include <Windows.h>
#include <bcrypt.h>

#pragma comment(lib, "bcrypt.lib")

Iltasatu::Iltasatu(size_t size) :
	_size(size),
	_data(new char[size])
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
	BCryptCloseAlgorithmProvider(_context, 0);

	delete[] _data;
}

char* Iltasatu::Generate()
{
	if (!_context || !_data)
	{
		return nullptr;
	}

	NTSTATUS status = BCryptGenRandom(
		_context,
		reinterpret_cast<PUCHAR>(_data),
		static_cast<ULONG>(_size),
		0);

	return SUCCEEDED(status) ? _data : nullptr;
}
