#pragma once
#include "..\HtmlReport\SttXmacroHtmlRptGenBase.h"

class CSttHtmlRptGen_MUFirstWave : public CSttXmacroHtmlRptGenBase
{
public:
	CSttHtmlRptGen_MUFirstWave();
	virtual ~CSttHtmlRptGen_MUFirstWave();

	static CSttXmacroHtmlRptGenBase* New()
	{
		return new CSttHtmlRptGen_MUFirstWave();
	}

	virtual void GenHtml();	//生成报告
	virtual void GenRootDiv_H1();

	void GenRootDiv();
	void GenRootDiv_End();

	virtual void GenMUFirstWave();
	void GenMUFirstWave_Table_th();
	void GenPicture(QImage *pImage);
};
