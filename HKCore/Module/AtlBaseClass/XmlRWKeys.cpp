// CXmlRWKeys.cpp: implementation of the CXmlRWKeys class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "XmlRWKeys.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const CComBSTR CXmlRWKeys::g_strNameKeyString  = "name";
const CComBSTR CXmlRWKeys::g_strIDKeyString    = "name";

long CXmlRWKeys::ReadFromXmlFile(const CComBSTR &strFile)
{
	return 0;
}

//��XML�ڵ��ж�ȡ�ؼ���
long CXmlRWKeys::ReadXml(MSXML::IXMLDOMNodePtr &oNode)
{
	return 0;
}
