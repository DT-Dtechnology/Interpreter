#include "stdafx.h"
#include "Inputter.h"
#include "QuoteDetecter.h"

SenVector* Inputter::get_sentence_vector() const
{
	SenVector* sen_vector = new SenVector;
	QuoteDetecter quote_detecter;
	
	string temp;
	int row_cnt = 0;
	while (getline(fin_, temp))
	{
		string line = "";
		int tab_cnt = 0;
		int space_cnt = 0;
		while (tab_cnt < temp.length())
		{
			if (temp[tab_cnt] == '\t')
				tab_cnt++;
			else
				break;
		}
		while (tab_cnt + space_cnt < temp.length())
		{
			if (temp[tab_cnt + space_cnt] == ' ')
				space_cnt++;
			else
				break;
		}
		for (int i = tab_cnt + space_cnt; i < temp.length(); i++)
		{
			quote_detecter.setQuoteStatus(temp[i]);
			if (temp[i] == '#' && !quote_detecter.getQuoteStatus())
				break;
			line = line + temp[i];
		}
		if (line == "")
			continue;
		else
		{
			row_cnt++;
			sen_vector->push_back(new Sentence(line, tab_cnt, row_cnt));
		}
	}
	return sen_vector;
}
