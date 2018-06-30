#include "stdafx.h"
#include "Inputter.h"
#include "QuoteDetecter.h"
#include <cstring>
using std::pair;
using std::tuple;

void senVec_delete(SenVector* sv)
{
	sv->erase(sv->begin(), sv->end());
	delete sv;
}


SenVector* Inputter::get_sentence_vector() const
{
	SenVector* sen_vector = new SenVector;
	QuoteDetecter quote_detecter;
	
	string temp;
	int row_cnt = 0;
	while (getline(fin_, temp))
	{
		int spaceCnt = 0;
		for (int i = 0; i < temp.length() - 4; i++)
		{
			if (temp[i] != ' ') break;
			else spaceCnt++;
		}
		string temp2 = "";
		for (int i = 0; i < spaceCnt / 4; i++)
			temp2 = temp2 + '\t';
		temp2 = temp2 + temp.substr(4*temp2.length(), temp.length() - temp2.length() * 4);
		temp = temp2;

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

	vector<int> endIf;
	vector<int> endLoop;
	vector<int> endDef;

	vector< tuple<string, int, int, int> > endMark;
	int n[100000];
	memset(n, 0, 100000);

	SenVector* tail = new SenVector;
	for (auto it = sen_vector->begin(); it != sen_vector->end(); it++)
	{
		if ((*it)->getOrder().substr(0, 2) == "if")
		{
			bool flag = 1;
			int r = (*it)->getTab();
			auto itr = it + 1;
			while (itr != sen_vector->end())
			{
				if ((*itr)->getTab() <= r && ((*itr)->getOrder().substr(0, 4) != "else" || (*itr)->getTab() != r) && ((*itr)->getOrder().substr(0, 4) != "elif" || (*itr)->getTab() != r))
				{
					const int temp_row = (*itr)->getRow();
					n[temp_row]++;

					const tuple< string, int, int, int > local_temp = std::make_tuple("endIf", (*itr)->getRow(), n[temp_row]-1, r);
					endMark.push_back(local_temp);
					flag = 0;
					break;
				}
				++itr;
			}
			if (flag)
			{
				string str = "endIf";
				tail->push_back(new Sentence(str, r, 0));
			}
		}
		if ((*it)->getOrder().substr(0, 3) == "for" || (*it)->getOrder().substr(0, 5) == "while")
		{
			bool flag = true;
			int r = (*it)->getTab();
			auto itr = it + 1;
			while (itr != sen_vector->end())
			{
				if ((*itr)->getTab() <= r)
				{
					const int temp_row = (*itr)->getRow();
					n[temp_row]++;

					const tuple< string, int, int, int > local_temp = std::make_tuple("endLoop", (*itr)->getRow(), n[temp_row] - 1, r);
					endMark.push_back(local_temp);
					flag = 0;
					break;
				}
				++itr;
			}
			if (flag)
			{
				string str = "endLoop";
				tail->push_back(new Sentence(str, r, 0));
			}
		}
		if ((*it)->getOrder().substr(0, 3) == "def")
		{
			bool flag = 1;
			int r = (*it)->getTab();
			auto itr = it + 1;
			while (itr != sen_vector->end())
			{
				if ((*itr)->getTab() <= r)
				{
					const int temp_row = (*itr)->getRow();
					n[temp_row]++;

					const tuple< string, int, int, int > local_temp = std::make_tuple("endDef", (*itr)->getRow(), n[temp_row] - 1, r);
					endMark.push_back(local_temp);
					flag = 0;
					break;
				}
				itr++;
			}
			if (flag)
			{
				string str = "endDef";
				tail->push_back(new Sentence(str, r, 0));
			}
		}
	}
	
	int endmarklen = endMark.size();

	for (int i = 0; i < endmarklen; ++i) {
		for (int j = i; j < endmarklen; ++j) {
			if (std::get<1>(endMark[i]) > std::get<1>(endMark[j])) {
				swap(endMark[i], endMark[j]);
			}
		}
	}
	for (int i = 0; i < endmarklen; ++i) {
		for (int j = i; (j < endmarklen) && (std::get<1>(endMark[i]) == std::get<1>(endMark[j])); ++j) {
			if (std::get<2>(endMark[i]) < std::get<2>(endMark[j])) {
				swap(endMark[i], endMark[j]);
			}
		}
	}
	SenVector* new_sv = new SenVector;
	int row = row_cnt + endMark.size() + tail->size();

	for (auto it = tail->begin(); it != tail->end(); ++it)
	{
		new_sv->push_back(*it);
		row--;
	}
	auto it = sen_vector->end();
	--it;

	int cnt = endMark.size();
	--cnt;

	for ( ; ; --it)
	{	
		new_sv->push_back((*it));
		row--;
		while ( cnt >= 0 && (*it)->getRow() == std::get<1>(endMark[cnt])) {
			string tmp = std::get<0>(endMark[cnt]);
			new_sv->push_back(new Sentence(tmp, std::get<3>(endMark[cnt]), row));
			--cnt;
			--row;
		}
		if (it == sen_vector->begin())
			break;
		
	}

	SenVector *new_new_sv = new SenVector;
	it = new_sv->end();
	--it;
	for (; ; --it) {
		new_new_sv->push_back((*it));
		if (it == new_sv->begin())
			break;
	}

	int new_row = 0;
	for (auto i : *new_new_sv) {
		i->setRow(new_row++);
	}
	
	/*
	for (auto i : *new_new_sv) {
		const int tab_cnt = i->getTab();
		for (auto in_it = 0; in_it < tab_cnt; ++in_it) {
			cout << "  ";
		}
		cout << i->getOrder() << endl;
	}*/
	senVec_delete(tail);
	senVec_delete(sen_vector);
	senVec_delete(new_sv);
	return new_new_sv;
}
