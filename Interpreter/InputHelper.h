#include<string>
#include<map>
#include<fstream>

usingnamespacestd;

//####
classInputHelper{
public:
	staticconstintA='A';
	staticconstintZ='Z';
	staticmap<string,char>Map;
	staticboolisUp(charc)
	{
		return((c>=A)&&(c<=Z))||((c>=A-64)&&(c<=Z-64));
	}
	staticboolisRealUp(charc)
	{
		return(c>=A)&&(c<=Z);
	}
	staticvoidhelp_input(){
		ifstreamfin;
		ofstreamfout;
		intnextUp='A';
		intnextDown='a';
		fin.open("InputHelp.txt");
		fout.open("NewTable.txt");
		stringword;
		while(true)
		{
			fin>>word;
			if(word=="END")
				return;
			if(word==";"){
				fout<<endl;
				continue;
			}
			elseif(word=="~"){
				fout<<"~";
				continue;
			}
			elseif(word=="->"){
				fout<<word;
				continue;
			}
			elseif(Map[word]==0){
				if(isUp(word[0]))
				{
					Map[word]=nextUp;
					++nextUp;
					if(nextUp>'Z')
						nextUp=1;
				}
				else{
					Map[word]=nextDown;
					++nextDown;
					if(nextDown>'z')
						nextDown=33;
					if(nextDown=='\'')
						nextDown++;
					if(nextDown=='#')
						nextDown++;
				}
			}
			if(isUp(word[0])&&!isRealUp(char(Map[word])))
				fout<<char(Map[word]+64)<<'\'';
			else
				fout<<Map[word];
		}
		fin.close();
		fout.close();
	}
};

map<string,char>InputHelper::Map;
