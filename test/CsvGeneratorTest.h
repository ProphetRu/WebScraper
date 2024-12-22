#ifndef CsvGeneratorTest_h__
#define CsvGeneratorTest_h__

#include "CsvGenerator.h"
#include "CsvGenerator.cpp" // the linking error without this #include

namespace CsvGeneratorTest
{
	constexpr auto USER_AGENT{ "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36" };

	TEST(CsvGeneratorTest, EmptyFileName)
	{
		DataSet ds
		{
			{ "date1", "open1", "high1", "low1", "close1", "adj_close1" },
			{ "date2", "open2", "high2", "low2", "close2", "adj_close2" },
			{ "date3", "open3", "high3", "low3", "close3", "adj_close3" },
		};

		EXPECT_THROW({ CsvGenerator::Generate("", std::move(ds)); }, std::invalid_argument);
	}

	TEST(CsvGeneratorTest, EmptyDataSet)
	{
		EXPECT_THROW({ CsvGenerator::Generate("out.csv", {}); }, std::invalid_argument);
	}

	TEST(CsvGeneratorTest, InvalidFilePath)
	{
		DataSet ds
		{
			{ "date1", "open1", "high1", "low1", "close1", "adj_close1" },
			{ "date2", "open2", "high2", "low2", "close2", "adj_close2" },
			{ "date3", "open3", "high3", "low3", "close3", "adj_close3" },
		};

#ifdef _WIN32
		EXPECT_THROW({ CsvGenerator::Generate("Z:\\invalid\\path\\out.csv", std::move(ds)); }, std::runtime_error);
#else
		EXPECT_THROW({ CsvGenerator::Generate("/invalid/path/out.csv", std::move(ds)); }, std::runtime_error);
#endif
	}

	TEST(CsvGeneratorTest, TestOK)
	{
		DataSet ds
		{
			{ "date1", "open1", "high1", "low1", "close1", "adj_close1" },
			{ "date2", "open2", "high2", "low2", "close2", "adj_close2" },
			{ "date3", "open3", "high3", "low3", "close3", "adj_close3" },
		};

		EXPECT_NO_THROW({ CsvGenerator::Generate("out.csv", std::move(ds)); });
	}
}

#endif // CsvGeneratorTest_h__
