#include "CsvGenerator.h"
#include <stdexcept>
#include <fstream>

constexpr auto SEPARATOR{ ';' };

void CsvGenerator::Generate(const std::string&& out_file_name, const DataSet&& data_set)
{
	if (out_file_name.empty() || data_set.empty())
	{
		throw std::invalid_argument{ "Invalid argument" };
	}

	std::ofstream out_file{ out_file_name };
	if (!out_file.is_open())
	{
		throw std::runtime_error{ "Can't create output csv-file" };
	}

	for (const auto& [date, open, high, low, close, adj_close] : data_set)
	{
		out_file << date << SEPARATOR
			<< open  << SEPARATOR
			<< high  << SEPARATOR
			<< low   << SEPARATOR
			<< close << SEPARATOR
			<< adj_close << std::endl;
	}

	out_file.close();
}
