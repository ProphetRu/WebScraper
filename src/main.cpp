#include <iostream>
#include "WebRequest.h"
#include "HtmlParser.h"
#include "CsvGenerator.h"

constexpr auto URL{ "https://finance.yahoo.com/quote/BTC-USD/history/" };
constexpr auto USER_AGENT{ "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36" };

int main() noexcept
{
	std::cout << "WebScraper\n\n";
	std::cout << "Target URL: " << URL << std::endl;
	std::cout << "User agent: " << USER_AGENT << std::endl;


	try
	{
		std::cout << "Send web request\n";
		auto html_content{ WebRequest::Send(URL, USER_AGENT) };

		std::cout << "Parse HTML-response\n";
		auto data_set{ HtmlParser::Parse(std::move(html_content)) };

		std::cout << "Generate CSV file\n";
		CsvGenerator::Generate("out.csv", std::move(data_set));
	}
	catch (const std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}

	return 0;
}
