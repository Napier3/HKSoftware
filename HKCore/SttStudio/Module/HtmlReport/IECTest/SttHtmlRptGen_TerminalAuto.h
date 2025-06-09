#ifndef _CSttHtmlRptGen_TerminalAuto_H
#define _CSttHtmlRptGen_TerminalAuto_H

#include "../SttXmacroHtmlRptGenBase.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"


class CSttHtmlRptGen_TerminalAuto : public CSttXmacroHtmlRptGenBase
{
public:
    CSttHtmlRptGen_TerminalAuto();
    virtual ~CSttHtmlRptGen_TerminalAuto();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_TerminalAuto();
	}

	virtual void GenHtml();			 					//生成测试报告HTML文本
	virtual void GenRootDiv_H1();

	void GenRootDiv();				
	void GenRootDiv_End();
	virtual void GenIntelTerminal_h2(const CString &strName);	             //生成子表标题
	virtual void GenIntelTerminal_h3(const CString &strName);	             //生成子表标题
	virtual void GenIntelTerminal_Table_th_Gout(const CString &strTypeID);
	virtual void GenIntelTerminal_Table_th_Gin(const CString &strTypeID);
	virtual void GenIntelTerminal_Table_th_SoeGout(const CString &strTypeID);
	virtual void GenIntelTerminal_Table_th_SoeGin(const CString &strTypeID);
	void GenIntelTerminal_Table_Point_GoutPubs();
	void GenIntelTerminal_Table_Point_GinPubs();
	void GenIntelTerminal_Table_Point_SoeGoutPubs();
	void GenIntelTerminal_Table_Point_SoeGinPubs();
	virtual void GenTestIntelTerminal();	
	float CalculateMaxDifference(const QList<float>& list);
	QList<float>m_GooseOutMaxTimeList;
	QList<float>m_GooseInMaxTimeList;

};


#endif 



