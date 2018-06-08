#pragmaonce
#include<set>
#include<string>

usingstd::set;
usingstd::string;

stringpython_operator[]=
{
	"+","-","*","/","%","&","|","=",
	"**","^","~","//","[","]",":",
	"<<",">>","<=","==","!=",">=",
	"<",">","%=","<>","/=","-=",
	"+=","*=","++","(",")",",","--"
};

set<string>operatorSet(python_operator,python_operator+34);


stringpython_keyword[]=
{"def","if","raise","None","del","import",
"return","elif","in","try","and","else",
"is","while","as","except","lambda","with","assert",
"finally","nonlocal","yield","break","for","class","from",
"or","continue","global","pass","not","print"
};



set<string>KeyWordSet(python_keyword,python_keyword+32);
