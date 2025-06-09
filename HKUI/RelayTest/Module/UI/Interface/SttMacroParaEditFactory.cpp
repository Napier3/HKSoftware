#include "SttMacroParaEditFactory.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CSttMacroParaEditCreator
CSttMacroParaEditCreator::CSttMacroParaEditCreator()
{

}

CSttMacroParaEditCreator::~CSttMacroParaEditCreator()
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CSttMacroParaEditFactory
CSttMacroParaEditFactory::CSttMacroParaEditFactory()
{
	
}

CSttMacroParaEditFactory::~CSttMacroParaEditFactory()
{

}

 CSttMacroParaEditCreator* CSttMacroParaEditFactory::Register(const CString &strMacroID, STTMACROPARAEDIT_PFNCREATE *pFunc)
{
    CSttMacroParaEditCreator *pNew = new CSttMacroParaEditCreator();
    AddNewChild(pNew);
    pNew->m_strID = strMacroID;
    pNew->m_pFuncCreate = pFunc;

    return pNew;
}

CSttMacroParaEditInterface* CSttMacroParaEditFactory::CreateSttMacroParaEditView(const CString &strMacroID, const CString &strGridFile,BOOL bUseExist)
{
    CSttMacroParaEditCreator *pCreator = (CSttMacroParaEditCreator*)FindByID(strMacroID);

    if (pCreator == 0)
    {
        return 0;
    }

    return pCreator->m_pFuncCreate(strGridFile);
}
