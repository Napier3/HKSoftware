#pragma once

#include "GbWzdAiMacroPara.h"

//////////////////////////////////////////////////////////////////////////
class CGbWzdAiParasBase : public CGbAiOptrBase
{
public:
	CGbWzdAiParasBase();
	virtual ~CGbWzdAiParasBase();

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
	virtual void InitMacroPara(CDataGroup *pMacroParas);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiParas;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiParasKey ;	}

public:
	void SetMacroParasValueByAI(CXMatchList *pDvmMatchListFilter, CSttGuideBook *pSttGuideBook);
	void SetMacroParasValueByAI(CXMatchObject *pObjMatch, CSttGuideBook *pSttGuideBook);
};
