#ifndef _CSttHtmlRptGen_MUTimingAccur_H
#define _CSttHtmlRptGen_MUTimingAccur_H

#include "../SttXmacroHtmlRptGenBase.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"

class CSttHtmlRptGen_MUTimingAccur : public CSttXmacroHtmlRptGenBase
{
public:
    CSttHtmlRptGen_MUTimingAccur();
    virtual ~CSttHtmlRptGen_MUTimingAccur();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_MUTimingAccur();
	}

	virtual void GenHtml();			 					//生成测试报告HTML文本
	virtual void GenRootDiv_H1();

	void GenRootDiv();				
	void GenRootDiv_End();

	virtual void GenTestMUTimingAccur();	

	void GenMUTimingAccur_Table_th();
	void GenMUTimingAccur_Table_Point();
	void ShowData_td_MUTimingAccur( CString strAttrID);
    void ShowData_td_MUTimeResult( CString strAttrID);
	
	bool m_bIsHasUsingTime;//20250325 suyang 增加是为了小于1分钟时不填报告
};


#endif // _CSttHtmlRptGen_MUTimingAccur_H
