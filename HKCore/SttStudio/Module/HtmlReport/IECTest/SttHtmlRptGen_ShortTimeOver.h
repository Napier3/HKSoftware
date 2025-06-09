#ifndef _CSttHtmlRptGen_ShortTimeOver_H
#define _CSttHtmlRptGen_ShortTimeOver_H

#include "../SttXmacroHtmlRptGenBase.h"


class CSttHtmlRptGen_ShortTimeOver : public CSttXmacroHtmlRptGenBase
{
public:
	CSttHtmlRptGen_ShortTimeOver();
	virtual ~CSttHtmlRptGen_ShortTimeOver();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_ShortTimeOver();
	}

	virtual void GenHtml();			 					//���ɲ��Ա���HTML�ı�
	virtual void GenRootDiv_H1();
	void GenRootDiv();				
	void GenRootDiv_End();
	virtual void GenShortTimeOver();	
	virtual void GenShortTimeOver_Table_th(const CString &strTypeID);	
	virtual void GenShortTimeOver_Table_th_Data();	
};

#endif