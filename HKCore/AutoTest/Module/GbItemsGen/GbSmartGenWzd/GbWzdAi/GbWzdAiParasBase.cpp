#include "stdafx.h"
#include "GbWzdAiParasBase.h"
#include "../../../../../IotProtoServer/Module/SttPxCommCmdDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CGbWzdAiParasBase::CGbWzdAiParasBase()
{

}

CGbWzdAiParasBase::~CGbWzdAiParasBase()
{

}

long CGbWzdAiParasBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbAiOptrInterface::XmlReadOwn(oNode, pXmlRWKeys);

	//CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbWzdAiParasBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CGbAiOptrInterface::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	//CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbWzdAiParasBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CGbAiOptrInterface::SerializeOwn(oBinaryBuffer);


	return 0;
}


CExBaseObject* CGbWzdAiParasBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if (strClassID == CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiMacroParatKey)
	{
		return new CGbWzdAiMacroPara();
	}

	return NULL;
}

CExBaseObject* CGbWzdAiParasBase::CreateNewChild(long nClassID)
{
	if (nClassID == GBCLASSID_GbWzdAiMacroPara)
	{
		return new CGbWzdAiMacroPara();
	}

	return NULL;
}

DWORD CGbWzdAiParasBase::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	POS pos = GetHeadPosition();
	CGbAiOptrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiOptrBase *)GetNext(pos);
		p->ScptCal(pXMatchObj, bAllMatchMode, pSttGuideBook);
	}

	return 0;
}

void CGbWzdAiParasBase::InitMacroPara(CDataGroup *pMacroParas)
{
	POS pos = GetHeadPosition();
	CGbAiOptrInterface *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiOptrInterface *)GetNext(pos);
		p->InitMacroPara(pMacroParas);
	}
}

void CGbWzdAiParasBase::SetMacroParasValueByAI(CXMatchList *pDvmMatchListFilter, CSttGuideBook *pSttGuideBook)
{
	POS pos = pDvmMatchListFilter->GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)pDvmMatchListFilter->GetNext(pos);
		SetMacroParasValueByAI(p, pSttGuideBook);
	}
}

void CGbWzdAiParasBase::SetMacroParasValueByAI(CXMatchObject *pObjMatch, CSttGuideBook *pSttGuideBook)
{
	//子对象为CGbWzdAiMacroPara和
	POS pos = GetHeadPosition();
	CGbAiOptrBase *p = NULL;

	while (pos != NULL)
	{
		p = (CGbAiOptrBase *)GetNext(pos);
		p->ScptCal(pObjMatch, TRUE, pSttGuideBook);
	}
}
