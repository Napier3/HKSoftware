#include "StdAfx.h"
#include "GbWzdAiScript.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
CGbAiParaScript::CGbAiParaScript(void)
{
	m_strName = _T("Script");
	m_strID = _T("Script");
}

CGbAiParaScript::~CGbAiParaScript(void)
{
}

long CGbAiParaScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);

	return 0;
}

long CGbAiParaScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGbSmartGenWzdXmlRWKeys *pXmlKeys = (CGbSmartGenWzdXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);

	return 0;
}

long CGbAiParaScript::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);


	return 0;
}

CExBaseObject* CGbAiParaScript::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return CGbAiOptrBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);;
}

CExBaseObject* CGbAiParaScript::CreateNewChild(long nClassID)
{
	return CGbAiOptrBase::CreateNewChild(nClassID);
}

CBaseObject* CGbAiParaScript::Clone()
{
	CGbAiParaScript* pScript = new CGbAiParaScript();
	Copy(pScript);

	return pScript;
}

DWORD CGbAiParaScript::ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook)
{
	return CGbAiOptrAnd::ScptCal(pXMatchObj, TRUE, pSttGuideBook);
}

/*
//中的初始化接口
void CGbAiParaScript::InitGbAiDataKey(CXKeyDB *pKeyDB *pKeyDB)
{
	InitGbAiDataKey(this, pKeyDB);
}

//集合对象的初始化接口，例如Key、OptrInterface等对象
void CGbAiParaScript::InitGbAiDataKey(CExBaseList *pList, CXKeyDB *pKeyDB *pKeyDB)
{
	//遍历pList的每个子对象，根据ClassID进行处理
	
}
*/
