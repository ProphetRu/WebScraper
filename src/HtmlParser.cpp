#include "HtmlParser.h"
#include <ranges>
#include <stdexcept>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

DataSet HtmlParser::Parse(const std::string&& html_content)
{
    auto parse_content = [](const std::string&& str) noexcept
    {
        if (const auto pos{ str.find(' ') }; pos != std::string::npos)
        {
            return str.substr(0, pos);
        }
        return str;
    };

	if (html_content.empty())
	{
		throw std::invalid_argument{ "HTML content is empty" };
	}
    
	const auto doc{ htmlReadMemory(html_content.c_str(), html_content.size(), nullptr, nullptr, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING) };
    if (!doc) 
    {
        throw std::runtime_error{ "Failed to parse HTML content" };
    }

    const auto path_context{ xmlXPathNewContext(doc) };
    if (!path_context)
    {
        xmlFreeDoc(doc);
        throw std::runtime_error{ "Failed to create XPath context" };
    }

	const auto path_object{ xmlXPathEvalExpression(reinterpret_cast<const xmlChar*>("//tr[@class='yf-j5d1ld']"), path_context) };
    if (!path_object) 
    {
        xmlXPathFreeContext(path_context);
        xmlFreeDoc(doc);
        throw std::runtime_error{ "Failed to evaluate XPath expression" };
    }

    DataSet data_set;
    data_set.reserve(path_object->nodesetval->nodeNr);
    
    for ([[maybe_unused]] auto i : std::ranges::views::iota(0, path_object->nodesetval->nodeNr))
    {
	    if (const auto row_node{ path_object->nodesetval->nodeTab[i] })
        {
            Data data;
            auto data_field{ DataFields::Date };

            for (auto cell_node{ row_node->children }; cell_node; cell_node = cell_node->next) 
            {
                if (cell_node->type == XML_ELEMENT_NODE) 
                {
                    if (data_field == DataFields::Date)
                    {
                        data.Date  = parse_content(reinterpret_cast<const char*>(xmlNodeGetContent(cell_node)));
                        data_field = DataFields::Open;
                    }
                    else if (data_field == DataFields::Open)
                    {
                        data.Open  = parse_content(reinterpret_cast<const char*>(xmlNodeGetContent(cell_node)));
                        data_field = DataFields::High;
                    }
                    else if (data_field == DataFields::High)
                    {
                        data.High  = parse_content(reinterpret_cast<const char*>(xmlNodeGetContent(cell_node)));
                        data_field = DataFields::Low;
                    }
                    else if (data_field == DataFields::Low)
                    {
                        data.Low   = parse_content(reinterpret_cast<const char*>(xmlNodeGetContent(cell_node)));
                        data_field = DataFields::Close;
                    }
                    else if (data_field == DataFields::Close)
                    {
                        data.Close = parse_content(reinterpret_cast<const char*>(xmlNodeGetContent(cell_node)));
                        data_field = DataFields::AdjClose;
                    }
                    else if (data_field == DataFields::AdjClose)
                    {
                        data.AdjClose = parse_content(reinterpret_cast<const char*>(xmlNodeGetContent(cell_node)));
                        break;
                    }
                }
            }

            if (data.IsValid())
            {
                data_set.emplace_back(std::move(data));
            }
        }
    }
    
    xmlXPathFreeObject(path_object);
    xmlXPathFreeContext(path_context);
    xmlFreeDoc(doc);

    if (data_set.empty())
    {
        throw std::runtime_error{ "Parse is failed" };
    }

	return data_set;
}
