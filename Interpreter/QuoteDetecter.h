#pragma once

//Only Used for Detecting the Quote Status
//

//This class is using for detecting the Status of the quote Status
//When read a Charater c, you should setQuoteStatus
//When you want the Status, just getQuoteStatus
class QuoteDetecter
{
	bool single_quote = false;
	bool double_quote = false;
public:
	QuoteDetecter() = default;
	~QuoteDetecter() = default;
	bool getQuoteStatus() const { return single_quote || double_quote; }
	void setQuoteStatus(const char c)
	{
		if (c == 34 && single_quote == 0)
			double_quote = 1 - double_quote;
		if (c == 39 && double_quote == 0)
			single_quote = 1 - single_quote;
	}
};

