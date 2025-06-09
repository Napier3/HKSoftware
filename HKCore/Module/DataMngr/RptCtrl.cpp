//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmData.cpp  CRptCtrl


#include "stdafx.h"
#include "RptCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CRptCtrl
CRptCtrl::CRptCtrl()
{
	//初始化属性
	m_nIntgPd = 0;
	m_nConfRev = 0;
	m_nBuffered = 0;
	m_nBufTime = 0;
	m_nTrgOps = 0;
	m_nOptFields = 0;
	m_nRptEnabled = 0;
}

CRptCtrl::~CRptCtrl()
{
}

long CRptCtrl::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strCDatSetKey, oNode, m_strDatSet);
	xml_GetAttibuteValue(pXmlKeys->m_strCIntgPdKey, oNode, m_nIntgPd);
	xml_GetAttibuteValue(pXmlKeys->m_strCRptIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strConfRevKey, oNode, m_nConfRev);
	xml_GetAttibuteValue(pXmlKeys->m_strCBufferedKey, oNode, m_nBuffered);
	xml_GetAttibuteValue(pXmlKeys->m_strCBufTimeKey, oNode, m_nBufTime);
	xml_GetAttibuteValue(pXmlKeys->m_strCTrgOpsKey, oNode, m_nTrgOps);
	xml_GetAttibuteValue(pXmlKeys->m_strCOptFieldsKey, oNode, m_nOptFields);
	xml_GetAttibuteValue(pXmlKeys->m_strCRptEnabledKey, oNode, m_nRptEnabled);


	return 0;
}

long CRptCtrl::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strCDatSetKey, oElement, m_strDatSet);
	xml_SetAttributeValue(pXmlKeys->m_strCIntgPdKey, oElement, m_nIntgPd);
	xml_SetAttributeValue(pXmlKeys->m_strCRptIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strConfRevKey, oElement, m_nConfRev);
	xml_SetAttributeValue(pXmlKeys->m_strCBufferedKey, oElement, m_nBuffered);
	xml_SetAttributeValue(pXmlKeys->m_strCBufTimeKey, oElement, m_nBufTime);
	xml_SetAttributeValue(pXmlKeys->m_strCTrgOpsKey, oElement, m_nTrgOps);
	xml_SetAttributeValue(pXmlKeys->m_strCOptFieldsKey, oElement, m_nOptFields);
	xml_SetAttributeValue(pXmlKeys->m_strCRptEnabledKey, oElement, m_nRptEnabled);


	return 0;
}


