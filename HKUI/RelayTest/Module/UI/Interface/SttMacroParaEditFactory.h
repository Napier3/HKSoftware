#ifndef _SttMacroParaEditFactory_h_
#define _SttMacroParaEditFactory_h_

#include "SttMacroParaEditInterface.h"


typedef CSttMacroParaEditInterface* (STTMACROPARAEDIT_PFNCREATE)(const CString &strGridFile);

class CSttMacroParaEditCreator : public CExBaseObject
{
public:
    CSttMacroParaEditCreator();
    virtual ~CSttMacroParaEditCreator();

    STTMACROPARAEDIT_PFNCREATE  *m_pFuncCreate;
};

class CSttMacroParaEditFactory : public CExBaseList
{
public:
	CSttMacroParaEditFactory();
	virtual ~CSttMacroParaEditFactory();

        CSttMacroParaEditCreator* Register(const CString &strMacroID, STTMACROPARAEDIT_PFNCREATE *pFunc);

	virtual CSttMacroParaEditInterface* CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist=TRUE);
};


#endif // _SttMacroParaEditFactory_h_
