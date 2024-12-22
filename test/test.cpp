#include <gtest/gtest.h>
#include "WebRequestTest.h"
#include "CsvGeneratorTest.h"
#include "HtmlParserTest.h"

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
