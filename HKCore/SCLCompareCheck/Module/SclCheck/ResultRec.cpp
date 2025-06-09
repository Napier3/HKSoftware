#include "stdafx.h"
#include "ResultRec.h"
CResultRec::CResultRec()
{
	//³õÊ¼»¯ÊôÐÔ
	m_nTipIndex = 0;
	m_nWarningIndex = 0;
	m_nErrorIndex = 0;
	m_nFatalErrorIndex = 0;
}

CResultRec::~CResultRec()
{
}

// #ifdef XML_USE_TINYXML
// 
// long CResultRec::XmlReadOwn(TiXmlElement *oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
// 	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCDatSetKey, oNode, m_strDatSet);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCIntgPdKey, oNode, m_nIntgPd);
// 	
// 	xml_GetAttibuteValue(pXmlKeys->m_strCLogNameKey, oNode, m_strLogName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCLogEnaKey, oNode, m_nLogEna);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCReasonCodeKey, oNode, m_nReasonCode);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCTrgOpsKey, oNode, m_nTrgOps);
// 
// 	return 0;
// }
// 
// long CResultRec::XmlWriteOwn(TiXmlElement* oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
// 	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
// 	xml_SetAttributeValue(pXmlKeys->m_strCDatSetKey, oElement, m_strDatSet);
// 	xml_SetAttributeValue(pXmlKeys->m_strCIntgPdKey, oElement, m_nIntgPd);
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strCLogNameKey, oElement, m_strLogName);
// 	xml_SetAttributeValue(pXmlKeys->m_strCLogEnaKey, oElement, m_nLogEna);
// 	xml_SetAttributeValue(pXmlKeys->m_strCReasonCodeKey, oElement, m_nReasonCode);
// 	xml_SetAttributeValue(pXmlKeys->m_strCTrgOpsKey, oElement, m_nTrgOps);
// 
// 	return 0;
// }
// 
// #else
// 
// long CResultRec::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strID);
// 	xml_GetAttibuteValue(pXmlKeys->m_strDescKey, oNode, m_strName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCDatSetKey, oNode, m_strDatSet);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCIntgPdKey, oNode, m_nIntgPd);
// 
// 	xml_GetAttibuteValue(pXmlKeys->m_strCLogNameKey, oNode, m_strLogName);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCLogEnaKey, oNode, m_nLogEna);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCReasonCodeKey, oNode, m_nReasonCode);
// 	xml_GetAttibuteValue(pXmlKeys->m_strCTrgOpsKey, oNode, m_nTrgOps);
// 
// 	return 0;
// }
// 
// long CResultRec::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strID);
// 	xml_SetAttributeValue(pXmlKeys->m_strDescKey, oElement, m_strName);
// 	xml_SetAttributeValue(pXmlKeys->m_strCDatSetKey, oElement, m_strDatSet);
// 	xml_SetAttributeValue(pXmlKeys->m_strCIntgPdKey, oElement, m_nIntgPd);
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strCLogNameKey, oElement, m_strLogName);
// 	xml_SetAttributeValue(pXmlKeys->m_strCLogEnaKey, oElement, m_nLogEna);
// 	xml_SetAttributeValue(pXmlKeys->m_strCReasonCodeKey, oElement, m_nReasonCode);
// 	xml_SetAttributeValue(pXmlKeys->m_strCTrgOpsKey, oElement, m_nTrgOps);
// 
// 	return 0;
// }
// 
// #endif
