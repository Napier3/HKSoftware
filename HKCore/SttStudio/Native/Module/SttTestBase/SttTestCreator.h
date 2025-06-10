#pragma once

#include "SttTestBase.h"
typedef CSttTestBase* (PFNCREATE)();

class CSttTestCreator : public CExBaseObject
{
public:
    CSttTestCreator(const CString &strPxAppName, const CString &strName,const CString &strID, PFNCREATE* pFunCreate);
	virtual ~CSttTestCreator(void);

	CSttTestBase* Create(BOOL bBuildTrans);

public:
	CString m_strPxAppID;
	CString m_strFilePostFix;

private:
	PFNCREATE* m_pFunCreate;

private:
	CSttTestCreator(void ) {	}
};
