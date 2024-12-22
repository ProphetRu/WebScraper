#include "WebRequest.h"
#include <stdexcept>
#include "cpr/cpr.h"

std::string WebRequest::Send(const std::string&& request_url, const std::string&& user_agent)
{
	if (request_url.empty() || user_agent.empty())
	{
		throw std::invalid_argument{ "Invalid argument" };
	}
	
	const cpr::Header headers{ { "User-Agent", user_agent.c_str() } };

	const auto response{ cpr::Get(cpr::Url{ request_url }, headers) };
	if (response.status_code == 0 || response.status_code >= 400)
	{
		throw std::runtime_error{ response.error.message };
	}

	if (response.text.empty())
	{
		throw std::runtime_error{ "Response is empty" };
	}

	return response.text;
}
