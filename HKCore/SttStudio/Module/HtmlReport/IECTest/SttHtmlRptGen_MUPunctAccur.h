#ifndef _CSttHtmlRptGen_MUPunctAccur_H
#define _CSttHtmlRptGen_MUPunctAccur_H

#include "../SttXmacroHtmlRptGenBase.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../Module/HtmlReport/SttXHtmlRptGenFactoryBase.h"

class CSttHtmlRptGen_MUPunctAccur : public CSttXmacroHtmlRptGenBase
{
public:
	CSttHtmlRptGen_MUPunctAccur();
	virtual ~CSttHtmlRptGen_MUPunctAccur();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_MUPunctAccur();
	}
	virtual void GenHtml();			 					//生成测试报告HTML文本
	virtual void GenRootDiv_H1();

	void GenRootDiv();				
	void GenRootDiv_End();
	virtual void GenTestMUPunctAccur();	

	void GenMUPunctAccur_Table_th();
	void GenMUPunctAccur_Table_Point();
	void ShowData_td_MUPunctAccur( CString strAttrID);
	void ShowData_td_MUTimeResult( CString strAttrID);

public:
	bool m_bIsHasUsingTime;//20250325 suyang 增加是为了小于1分钟时不填报告

};


#endif // _CSttHtmlRptGen_MUPunctAccur_H

