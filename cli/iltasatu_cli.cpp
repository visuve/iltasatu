#include "../lib/iltasatu.h"

#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << argv[0] << " <number of bytes>" << std::endl;
		return -1;
	}

	const size_t bytes = std::stoi(argv[1]);

	IltasatuHandle* iltasatu = IltasatuInitialize(bytes);

	char* data = IltasatuGenerate(iltasatu);

	if (!data)
	{
		std::cerr << "SNAFU!" << std::endl;
		return -2;
	}

	std::cout.setf(std::ios::hex, std::ios::basefield);
	std::cout.setf(std::ios::uppercase);
	std::cout.fill('0');

	char separator[2] = "";

	for (size_t i = 0; i < bytes; ++i)
	{
		std::cout << separator << std::setw(2) << +static_cast<uint8_t>(data[i]);
		separator[0] = ' ';
	}

	IltasatuDelete(iltasatu);

	return 0;
}
