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
	virtual void GenHtml();			 					//���ɲ��Ա���HTML�ı�
	virtual void GenRootDiv_H1();

	void GenRootDiv();				
	void GenRootDiv_End();
	virtual void GenTestMUPunctAccur();	

	void GenMUPunctAccur_Table_th();
	void GenMUPunctAccur_Table_Point();
	void ShowData_td_MUPunctAccur( CString strAttrID);
	void ShowData_td_MUTimeResult( CString strAttrID);

public:
	bool m_bIsHasUsingTime;//20250325 suyang ������Ϊ��С��1����ʱ�����

};


#endif // _CSttHtmlRptGen_MUPunctAccur_H

