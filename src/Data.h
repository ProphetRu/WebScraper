#ifndef Data_h__
#define Data_h__

#include <string>
#include <vector>

struct Data final
{
	std::string Date;
	std::string Open;
	std::string High;
	std::string Low;
	std::string Close;
	std::string AdjClose;

	[[nodiscard]] bool IsValid() const noexcept
	{
		return !Date.empty() && !Open.empty() && !High.empty() && !Low.empty() && !Close.empty() && !AdjClose.empty();
	}
};

enum class DataFields
{
	Date,
	Open,
	High,
	Low,
	Close,
	AdjClose,
};

using DataSet = std::vector<Data>;

#endif // Data_h__
