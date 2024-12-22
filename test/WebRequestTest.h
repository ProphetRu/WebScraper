#ifndef WebRequestTest_h__
#define WebRequestTest_h__

#include "WebRequest.h"
#include "WebRequest.cpp" // the linking error without this #include

namespace WebRequestTest
{
	constexpr auto USER_AGENT{ "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36" };

	TEST(WebRequestTest, TestNoRequestURL)
	{
		EXPECT_THROW({ WebRequest::Send("", "ua"); }, std::invalid_argument);
	}

	TEST(WebRequestTest, TestNoUserAgent)
	{
		EXPECT_THROW({ WebRequest::Send("url", ""); }, std::invalid_argument);
	}

	TEST(WebRequestTest, TestSendLocalhost)
	{
		EXPECT_THROW(WebRequest::Send("https://localhost", USER_AGENT), std::runtime_error);
	}

	TEST(WebRequestTest, TestSendIncorrectSite)
	{
		const auto html_content{ WebRequest::Send("https://www.microsoft.com/", USER_AGENT) };

		const auto is_find{ html_content.contains("google") };

		EXPECT_EQ(is_find, false);
	}

	TEST(WebRequestTest, TestSendOKSite)
	{
		const auto html_content{ WebRequest::Send("https://www.google.com/", USER_AGENT) };

		const auto is_find{ html_content.contains("google") };

		EXPECT_EQ(is_find, true);
	}
}

#endif // WebRequestTest_h__
