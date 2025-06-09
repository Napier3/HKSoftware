#include "stdafx.h"
#include "GuideBookFile.h"

CGuideBookFile::CGuideBookFile()
{

}

CGuideBookFile::~CGuideBookFile()
{

}


CXFileMngr* CGuideBookFile::GetXFileMngr()
{
	return (CXFileMngr*)GetAncestor(GB_DEV_GUIDEBOOK_FILE_MNGR);
}

//long CGuideBookFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
//{
//	return 0;
//}

//long CGuideBookFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
//{
//	CXFile::XmlReadOwn(oNode,CFileMngrXMLKeys::g_pFileMngrXMLKeys);
//	xml_GetAttibuteValue(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strGbNameKey,oNode,m_strGbName);
//	xml_GetAttibuteValue(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strGbFactoryKey,oNode,m_strFactory);
//	m_strID = m_strName;
//
//	return 0;
//}
//
//long CGuideBookFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
//{
//	CXFile::XmlWriteOwn(oXMLDoc,oElement,CFileMngrXMLKeys::g_pFileMngrXMLKeys);
//	oElement->setAttribute(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strGbNameKey,(_bstr_t)m_strGbName);
//	oElement->setAttribute(CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strGbFactoryKey,(_bstr_t)m_strFactory);
//
//	return 0;
//}