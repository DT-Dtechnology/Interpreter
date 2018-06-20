#pragma once
#include <string>
#include <set>
#include "OperatorSet.h"
#include "SentenceDivider.h"

using std::string;

WordType DetectType(const string &word) {
	if ((word[0] == '\'' && word[word.length() - 1] == '\'')
		|| (word[0] == '\"' && word[word.length() - 1] == '\"')) {
		//begin with quotation marks
		return value;
	}
	else if ((word[0] >= '0' && word[0] <= '9') || word[0] == '.') {
		//begin with number or dot
		bool dotexist = false;
		int num_cnt = 0;

		for (auto i : word) {
			if (i >= '0' && i <= '9')
				++num_cnt;
			if (i == '.' && dotexist) {
				//;;####
				//12.12.12
				return word_type_error;
			}
			if (i == '.' && !dotexist)
				dotexist = true;
		}

		if (num_cnt + dotexist == word.length())
			return value;
		else
			return word_type_error;
	}
	else {
		//find keyword in the set
		auto it = KeyWordSet.find(word);
		if (it != KeyWordSet.end()) {
			return keyword;
		}
		else {
			if ((word[0] == '_') || (word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z')) {
				//begin with _ or a-z or A-Z
				int var_len = 0;
				for (auto i : word) {
					if ((i == '_') || (i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i >= '0' && i <= '9')) {
						++var_len;
					}
				}
				if (var_len == word.length()) {
					return variable;
				}
				else {
					//;;####
					//begin with _ or a-z or A-Z but contain other character
					return word_type_error;
				}
			}
			else {
				auto it = operatorSet.find(word);
				if (it != operatorSet.end()) {
					return operate;
				}
				else {
					return word_type_error;
				}
			}
		}
	}
}