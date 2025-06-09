#ifndef _CSttHtmlRptGen__MUZeroDrift_H
#define _CSttHtmlRptGen__MUZeroDrift_H

#include "../SttXmacroHtmlRptGenBase.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"

class CSttHtmlRptGen_MUZeroDrift : public CSttXmacroHtmlRptGenBase
{
public:
    CSttHtmlRptGen_MUZeroDrift();
    virtual ~CSttHtmlRptGen_MUZeroDrift();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_MUZeroDrift();
	}

public:

	virtual void GenHtml();			 					//生成测试报告HTML文本
	virtual void GenRootDiv_H1();

	void GenRootDiv();				
	void GenRootDiv_End();
	void GenTestMUZeroDrift();
	void GenMUZeroDrift_Table_th();
	void GenMUZeroDrift_Table_td(const CString &strTypeID);
	void ShowData_td(CDvmData *pData,CString strTypeID,CString strAttrID);
	void GenMUZeroDrift_Data_td_Curr(int nIndex, CDvmData *pData,  CString strTypeID);
	void GenMUZeroDrift_Data_td_Vol(int nIndex, CDvmData *pData,  CString strTypeID);
	
};


#endif // _CSttHtmlRptGen__MUZeroDrift_H
