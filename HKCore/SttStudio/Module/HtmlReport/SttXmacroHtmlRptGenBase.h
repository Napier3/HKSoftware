#ifndef _CSttXmacroHtmlRptGenBase_H
#define _CSttXmacroHtmlRptGenBase_H

#include "SttModuleHtmlRptGenBase.h"
#include "../SttCmd/GuideBook/SttGuideBook.h"
#include "../../../Module/DataMngr/DvmDevice.h"

class CSttXmacroHtmlRptGenBase : public CSttXHtmlRptGenInterface
{
public:
    CSttXmacroHtmlRptGenBase();
    virtual ~CSttXmacroHtmlRptGenBase();

	CDvmDevice *m_pDvmDevice;
	CSttItems* m_pSttItems;

public:
	void GetHtml(CString &strHtmlData);
};


#endif // _CSttXmacroHtmlRptGenBase_H
