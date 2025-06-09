#include "stdafx.h"
#include "GbCommCmd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
CGbCommCmdPara::CGbCommCmdPara()
{
	
}

CGbCommCmdPara::~CGbCommCmdPara()
{

}

long CGbCommCmdPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strValueKey,oNode,m_strValue);
	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strDataTypeKey,oNode,m_strType);

	return 0;
}

long CGbCommCmdPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);

	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strValueKey,oElemen,m_strValue);
	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strDataTypeKey,oElemen,m_strType);

	return 0;
}

//////////////////////////////////////////////////////////////////////////
CGbCommCmdMms::CGbCommCmdMms()
{
	m_nGbRwOptr = COMMCMD_RW_OPTR_NONE;
//	m_strDataType = _T()
	m_nUseConnect = 1;
}

CGbCommCmdMms::~CGbCommCmdMms()
{

}

long CGbCommCmdMms::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strDatasetKey,oNode,m_strGbDataID);
	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strGbRwOptrKeyKey,oNode,m_strGbRwOptr);
	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strDataTypeKey,oNode,m_strDataType);
	
	m_strGbRwOptr.MakeLower();

	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strUseConnectKey,oNode,m_nUseConnect);
	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strWzdEditModeKey,oNode,m_strWzdEditMode);

	return 0;
}

long CGbCommCmdMms::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);

	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strDatasetKey,oElemen,m_strGbDataID);
	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strGbRwOptrKeyKey,oElemen,m_strGbRwOptr);
	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strDataTypeKey,oElemen,m_strDataType);

	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strUseConnectKey,oElemen,m_nUseConnect);
	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strWzdEditModeKey,oElemen,m_strWzdEditMode);

	return 0;
}

CExBaseObject* CGbCommCmdMms::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strCmdParaKey)
	{
		return new CGbCommCmdPara();
	}

	return NULL;
}

void CGbCommCmdMms::GetValues(CValues *pValues)
{
	POS pos = GetHeadPosition();
	CGbCommCmdPara *pPara = NULL;

	while (pos != NULL)
	{
		pPara = (CGbCommCmdPara *)GetNext(pos);
		CValue *pValue = pValues->AddValue(pPara->m_strID, pPara->m_strValue);
		pValue->m_strName = pPara->m_strName;
	}
}

BOOL CGbCommCmdMms::IsWrite()
{
	return (m_strGbRwOptr == _T("write"));
}

BOOL CGbCommCmdMms::IsRead()
{
	return (m_strGbRwOptr == _T("read"));
}

BOOL CGbCommCmdMms::IsRegister()
{
	return (m_strGbRwOptr == _T("register"));
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CGbCommCmd::CGbCommCmd()
{

}

CGbCommCmd::~CGbCommCmd()
{

}

long CGbCommCmd::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CGbCommCmdMms::XmlReadOwn(oNode,pXmlRWKeys);

	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strGbDataIDKey,oNode,m_strGbDataID);
	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strPpDvNodeIDKey,oNode,m_strPpDvNodeID);
	xml_GetAttibuteValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strPpProcedureIDKey,oNode,m_strPpProcedureID);

	return 0;
}

long CGbCommCmd::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys)
{
	CGbCommCmdMms::XmlWriteOwn(oXMLDoc, oElemen, pXmlRWKeys);

	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strGbDataIDKey,oElemen,m_strGbDataID);
	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strPpDvNodeIDKey,oElemen,m_strPpDvNodeID);
	xml_SetAttributeValue(CCommCmdConfigXMLKeys::g_pConfigXMLKeys->m_strPpProcedureIDKey,oElemen,m_strPpProcedureID);

	return 0;
}

CExBaseObject* CGbCommCmd::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	return NULL;
}

