#ifndef CsvGenerator_h__
#define CsvGenerator_h__

#include "Data.h"

class CsvGenerator final
{
public:
	static void Generate(const std::string&& out_file_name, const DataSet&& data_set);
};

#endif // CsvGenerator_h__
