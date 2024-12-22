#ifndef HtmlParserTest_h__
#define HtmlParserTest_h__

#include "HtmlParser.h"
#include "HtmlParser.cpp" // the linking error without this #include

namespace HtmlParserTest
{
	TEST(HtmlParserTest, TestEmptyHtmlContent)
	{
		EXPECT_THROW({ HtmlParser::Parse(""); }, std::invalid_argument);
	}
	
	TEST(HtmlParserTest, TestParseFailed)
	{
		EXPECT_THROW({ HtmlParser::Parse("invalid data"); }, std::runtime_error);
	}
	
	TEST(HtmlParserTest, TestParseOKException)
	{
		std::string content = R"(
        <table>
            <tr class="yf-j5d1ld">
                <td class="yf-j5d1ld">Dec 22, 2024</td>
                <td class="yf-j5d1ld">97,225.84</td>
                <td class="yf-j5d1ld">97,331.20</td>
                <td class="yf-j5d1ld">95,901.09</td>
                <td class="yf-j5d1ld">97,133.11</td>
                <td class="yf-j5d1ld">97,135.12</td>
            </tr>
        </table>
		)";

		EXPECT_NO_THROW(HtmlParser::Parse(std::move(content)));
	}

	TEST(HtmlParserTest, TestParseOKResult)
	{
		std::string content = R"(
        <table>
            <tr class="yf-j5d1ld">
                <td class="yf-j5d1ld">Dec 22, 2024</td>
                <td class="yf-j5d1ld">97,225.84</td>
                <td class="yf-j5d1ld">97,331.20</td>
                <td class="yf-j5d1ld">95,901.09</td>
                <td class="yf-j5d1ld">97,133.11</td>
                <td class="yf-j5d1ld">97,135.12</td>
            </tr>
        </table>
		)";

		const auto data{ HtmlParser::Parse(std::move(content)) };

		EXPECT_EQ(data.size(), 1);
		EXPECT_EQ(data[0].Date,     "Dec");
		EXPECT_EQ(data[0].Open,     "97,225.84");
		EXPECT_EQ(data[0].High,     "97,331.20");
		EXPECT_EQ(data[0].Low,      "95,901.09");
		EXPECT_EQ(data[0].Close,    "97,133.11");
		EXPECT_EQ(data[0].AdjClose, "97,135.12");
	}
}

#endif // HtmlParserTest_h__
