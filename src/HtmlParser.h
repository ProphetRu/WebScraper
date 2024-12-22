#ifndef HtmlParser_h__
#define HtmlParser_h__

#include "Data.h"

class HtmlParser final
{
public:
	static DataSet Parse(const std::string&& html_content);
};

#endif // HtmlParser_h__
