#include <print>
#include "WebRequest.h"
#include "HtmlParser.h"
#include "CsvGenerator.h"

constexpr auto URL{ "https://finance.yahoo.com/quote/BTC-USD/history/" };
constexpr auto USER_AGENT{ "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36" };

int main() noexcept
{
	std::println("WebScraper\n\nTarget URL: {}\nUser agent: {}\n", URL, USER_AGENT);

	try
	{
		std::println("Send web request");
		auto html_content{ WebRequest::Send(URL, USER_AGENT) };

		std::println("Parse HTML-response");
		auto data_set{ HtmlParser::Parse(std::move(html_content)) };

		std::println("Generate CSV file");
		CsvGenerator::Generate("out.csv", std::move(data_set));
	}
	catch (const std::exception& ex)
	{
		std::println("Error: {}", ex.what());
	}

	return 0;
}
