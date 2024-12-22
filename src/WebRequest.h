#ifndef WebRequest_h__
#define WebRequest_h__

#include <string>

class WebRequest final
{
public:
	static std::string Send(const std::string&& request_url, const std::string&& user_agent);
};

#endif // WebRequest_h__
