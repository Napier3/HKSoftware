#ifndef _CSttXHtmlRptGenFactoryBase_H
#define _CSttXHtmlRptGenFactoryBase_H

#include "SttXmacroHtmlRptGenBase.h"
#include "../../../Module/BaseClass/FactoryBase.h"

class CSttXHtmlRptGenFactoryBase : public CFactoryBase<CSttXmacroHtmlRptGenBase>
{
public:
    CSttXHtmlRptGenFactoryBase();
    virtual ~CSttXHtmlRptGenFactoryBase();

public:
	CDvmDevice *m_pDvmDevice;
	CDataTypes *m_pDataTypes;
	CSttGuideBook *m_pGuideBook;

	CExpandMemBuf  m_oHtmlBuffer;

public:
	CSttXmacroHtmlRptGenBase* CreateHtmlRptGen(const CString &strMacroID, 	CSttItems* pSttItems);
	CSttXmacroHtmlRptGenBase* CreateHtmlRptGen(const CString &strMacroID);

public:
	CSttXmacroHtmlRptGenBase *m_pCurrHtmRptGen;
	CString m_strMacroID;

};

extern CSttXHtmlRptGenFactoryBase *g_theHtmlRptGenFactory;

#endif // _CSttXHtmlRptGenFactoryBase_H
