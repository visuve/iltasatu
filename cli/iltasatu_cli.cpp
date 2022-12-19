#include "../lib/iltasatu.h"

#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << argv[0] << " <number of bytes> <mask[optional]> <hex[optional]>" << std::endl;
		return -1;
	}

	const size_t bytes = std::stoul(argv[1]);
	const uint32_t mask = argc >= 3 ? std::stoul(argv[2]) : IltasatuMask::None;
	const bool hex = argc >= 4 && std::string(argv[3]) == "hex";

	// TODO: read the mask from command line
	IltasatuOptions options;
	options.Size = bytes;
	options.Mask = mask;

	IltasatuHandle iltasatu = IltasatuInitialize(options);

	char* data = IltasatuGenerate(iltasatu);

	if (!data)
	{
		std::cerr << "SNAFU!" << std::endl;
		return -2;
	}

	if (hex)
	{
		std::cout.setf(std::ios::hex, std::ios::basefield);
		std::cout.setf(std::ios::uppercase);
		std::cout.fill('0');

		char separator[2] = "";

		for (size_t i = 0; i < bytes; ++i)
		{
			std::cout << separator << std::setw(2) << +static_cast<uint8_t>(data[i]);
			separator[0] = ' ';
		}
	}
	else
	{
		std::cout << std::string(data, bytes) << std::endl;
	}

	IltasatuDelete(iltasatu);

	return 0;
}
