#include "stdafx.h"
#include "GbDevItemFile.h"
#include "GbDevItemFileMngr.h"

CGbDevItemFile::CGbDevItemFile()
{
	m_strName = _T("GbDevItemFile");
	m_strItemName = _T("ItemName");
	m_strItemID = _T("ItemID");
}

CGbDevItemFile::~CGbDevItemFile()
{

}
// 
// long CGbDevItemFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	return 0;
// }
// 
// long CGbDevItemFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CFileBase::XmlReadOwn(oNode,CFileMngrXMLKeys::g_pFileMngrXMLKeys);
// 	m_strID = m_strName;
// 
// 	return 0;
// }
// 
// long CGbDevItemFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CFileBase::XmlWriteOwn(oXMLDoc,oElement,CFileMngrXMLKeys::g_pFileMngrXMLKeys);
// 	
// 	return 0;
// }