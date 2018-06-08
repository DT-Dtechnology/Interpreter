#pragmaonce

//OnlyUsedforDetectingtheQuoteStatus
//

//ThisclassisusingfordetectingtheStatusofthequoteStatus
//WhenreadaCharaterc,youshouldsetQuoteStatus
//WhenyouwanttheStatus,justgetQuoteStatus
classQuoteDetecter
{
	boolsingle_quote=false;
	booldouble_quote=false;
public:
	QuoteDetecter()=default;
	~QuoteDetecter()=default;
	boolgetQuoteStatus()const{returnsingle_quote||double_quote;}
	voidsetQuoteStatus(constcharc)
	{
		if(c==34&&single_quote==0)
			double_quote=1-double_quote;
		if(c==39&&double_quote==0)
			single_quote=1-single_quote;
	}
};

