//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmData.cpp  CLogCtrl


#include "stdafx.h"
#include "LogCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CLogCtrl
CLogCtrl::CLogCtrl()
{
	//初始化属性
	m_nIntgPd = 0;
	m_nLogEna = 0;
	m_nReasonCode = 0;
	m_nTrgOps = 0;
	m_nTrgOps = 0;
}

CLogCtrl::~CLogCtrl()
{
}

long CLogCtrl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strCDatSetKey, oNode, m_strDatSet);
	xml_GetAttibuteValue(pXmlKeys->m_strCIntgPdKey, oNode, m_nIntgPd);

	xml_GetAttibuteValue(pXmlKeys->m_strCLogNameKey, oNode, m_strLogName);
	xml_GetAttibuteValue(pXmlKeys->m_strCLogEnaKey, oNode, m_nLogEna);
	xml_GetAttibuteValue(pXmlKeys->m_strCReasonCodeKey, oNode, m_nReasonCode);
	xml_GetAttibuteValue(pXmlKeys->m_strCTrgOpsKey, oNode, m_nTrgOps);


	return 0;
}

long CLogCtrl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strCDatSetKey, oElement, m_strDatSet);
	xml_SetAttributeValue(pXmlKeys->m_strCIntgPdKey, oElement, m_nIntgPd);

	xml_SetAttributeValue(pXmlKeys->m_strCLogNameKey, oElement, m_strLogName);
	xml_SetAttributeValue(pXmlKeys->m_strCLogEnaKey, oElement, m_nLogEna);
	xml_SetAttributeValue(pXmlKeys->m_strCReasonCodeKey, oElement, m_nReasonCode);
	xml_SetAttributeValue(pXmlKeys->m_strCTrgOpsKey, oElement, m_nTrgOps);


	return 0;
}

