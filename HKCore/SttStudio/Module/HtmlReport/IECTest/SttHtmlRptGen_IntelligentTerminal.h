#ifndef _CSttHtmlRptGen_IntelligentTerminal_H
#define _CSttHtmlRptGen_IntelligentTerminal_H

#include "../SttXmacroHtmlRptGenBase.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"

class CSttHtmlRptGen_IntelligentTerminal : public CSttXmacroHtmlRptGenBase
{
public:
    CSttHtmlRptGen_IntelligentTerminal();
    virtual ~CSttHtmlRptGen_IntelligentTerminal();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_IntelligentTerminal();
	}

	virtual void GenHtml();			 					//生成测试报告HTML文本
	virtual void GenRootDiv_H1();

	void GenRootDiv();				
	void GenRootDiv_End();
	virtual void GenIntelTerminal_h2(const CString &strName);	             //生成子表标题
	virtual void GenIntelTerminal_h3(const CString &strName);	             //生成子表标题
	virtual void GenIntelTerminal_Table_th_Gout(const CString &strTypeID);
	virtual void GenIntelTerminal_Table_th_Gin(const CString &strTypeID);
	void GenIntelTerminal_Table_Point_GoutPubs(int nGoutCount);
	void GenIntelTerminal_Table_Point_GinPubs(int nGinCount);
	virtual void GenTestIntelTerminal();	

	void GetGooseSignal(int nGooseType,char* m_pszGoose);

};


#endif // _CSttHtmlRptGen_IntelligentTerminal_H
